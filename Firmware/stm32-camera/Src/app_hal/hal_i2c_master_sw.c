/**
 * @file      hal_i2c_master_sw.c
 *
 * @brief     Abstraction interface for I2C interface on STM.
 *            Pure software based I2C operation for read and write operations
 *            using a timer tick or software loop based controlled state
 *            machine.
 *
 *            Requires just access to any I/O lines and a optionally a
 *            timer tick to operate.
 *
 *            Designed to be operationally similar to the STM hardware
 *            variant.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

/* -------------------------------------------------------------------------- */

#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "hal_delay.h"
#include "hal_gpio.h"
#include "hal_i2c_master_sw.h"

/* -------------------------------------------------------------------------- */

DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* ----- Types -------------------------------------------------------------- */

typedef enum
{
    HAL_I2C_STEP_IDLE,                   /*  0 */
    HAL_I2C_STEP_CHECK_BUS_IS_NOT_BUSY,  /*  1 */

    /* ---- Set Start Condition ----- */
    HAL_I2C_STEP_START_CONDITION_SDA,      /*  2 Assert SDA */
    HAL_I2C_STEP_START_CONDITION_SCL,      /*  3 Assert SCL */

    /* ---- Send Address/Bytes ----- */
    HAL_I2C_STEP_ADDR_SETUP,               /*  4 */
    HAL_I2C_STEP_WRITE_SETUP,              /*  5 */
    HAL_I2C_STEP_WRITE_DATA_BIT,           /*  6 Set data * SCL high */
    HAL_I2C_STEP_WRITE_WAIT_CLOCK_BIT,     /*  7 Wait for SCL high - possible clock stretch */
    HAL_I2C_STEP_WRITE_CLOCK_BIT,          /*  8 Finish clock (SCL low) */

    /* ---- Check Acknowledgement ----- */
    HAL_I2C_STEP_WAIT_ACK,                 /*  9 */
    HAL_I2C_STEP_WAIT_ACK_CLK,             /* 10 */
    HAL_I2C_STEP_WRITE_GET_ACK,            /* 11 */
    HAL_I2C_STEP_WRITE_FINISH_ACK,         /* 12 */

    /* ---- Stop Condition ----- */
    HAL_I2C_STEP_STOP_CONDITION,           /* 13 Force SDA, release SCL */
    HAL_I2C_STEP_STOP_1,                   /* 14 Release SDA */
    HAL_I2C_STEP_STOP_CONDITION_WAIT_IDLE, /* 15 Wait release SDA */

    /* ---- Read Data ----- */
    HAL_I2C_STEP_READ_SETUP,               /* 16 */
    HAL_I2C_STEP_READ_CLOCK_BIT,           /* 17 */
    HAL_I2C_STEP_READ_DATA_BIT,            /* 18 */

    /* ---- Generate Read Ack ----- */
    HAL_I2C_STEP_GENERATE_ACK,             /* 19 */
    HAL_I2C_STEP_GENERATE_NAK,             /* 20 */
    HAL_I2C_STEP_GENERATE_ACK_CLOCK,       /* 21 */
    HAL_I2C_STEP_GENERATE_ACK_DONE,        /* 22 */

    /* ---- Error Handling ----- */

    HAL_I2C_STEP_BERR,                     /* 22 */
} HalI2cMasterSwStep_t;

typedef enum
{
    HAL_I2C_MODE_IDLE,
    HAL_I2C_MODE_WRITE,
    HAL_I2C_MODE_READ,
} HalI2cMasterSwMode_t;

typedef struct
{
    uint8_t              id;             /* Address */
    HalI2cMasterSwStep_t step;           /* State machine step */
    bool                 immediate;
    HalI2cState_t        state;
    HalI2cMasterSwMode_t mode;
    HalI2cStatus_t       status;
    HalI2cError_t        error;
    bool                 acked;          /* Transfer ACK status */
    uint8_t              addr;           /* Address */
    uint8_t              data;           /* Data byte being transferred */
    uint8_t              bit_count;      /* Bit counter for data byte transfer */
    uint8_t              index;          /* buffer index */
    uint8_t              tx_len;
    uint8_t             *tx;             /* Application declared buffer */
    uint8_t              rx_len;
    uint8_t             *rx;             /* Application declared buffer */
    uint8_t              half_clock_period;
    uint8_t              timeout;
    HalI2cCallback_t     callback;
    HalGpioPortPin_t     sda;            /* Pin Number for SDA */
    HalGpioPortPin_t     scl;            /* Pin Number for SCL */
} HalI2cMasterSw_t;

/* ----- Defines ------------------------------------------------------------ */

#define HAL_I2C_SLAVE_TIMEOUT               100 /** ticks */

#define NEXT_I2C_STEP(_s_)           me->immediate = false; me->step = (_s_)
#define IMMEDIATE_NEXT_I2C_STEP(_s_) me->immediate = true;  me->step = (_s_)
#define WAIT_NEXT_I2C_STEP(_s_)      me->immediate = false; me->step = (_s_)

#define HIGH true
#define LOW  false

/* ----- Private Function Prototypes ---------------------------------------- */

PRIVATE HalI2cMasterSw_t *
hal_i2c_master_sw_bus_handle( HalI2cBusId_t bus_id );

PRIVATE void
hal_i2c_master_sw_step( HalI2cMasterSw_t *me  );

/* ----- Private Variables -------------------------------------------------- */

PRIVATE HalI2cMasterSw_t       hal_i2c1;
PRIVATE HalI2cMasterSw_t       hal_i2c2;

/* -------------------------------------------------------------------------- */
/* ----- I2C Interface Functions -------------------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_sw_init( HalI2cBusId_t          bus_id,
                        const HalGpioPortPin_t sda,
                        const HalGpioPortPin_t scl )
{
    HalI2cMasterSw_t *hi2c = hal_i2c_master_sw_bus_handle( bus_id );
    memset( hi2c, 0, sizeof( HalI2cMasterSw_t ) );
    hi2c->id = bus_id;
    hi2c->sda = sda;
    hi2c->scl = scl;
    hal_i2c_master_sw_clock_speed( bus_id, 100000 ); /* Default */
    hal_i2c_master_sw_reset( bus_id );

#ifndef HAL_I2C_MASTER_SW_USE_TICKS
    do
    {
        hal_i2c_master_sw_step( hi2c );
        hal_delay_us( hi2c->half_clock_period );
    } while( hi2c->mode != HAL_I2C_MODE_IDLE );
#endif

    return I2C_STATUS_OK;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_i2c_master_sw_clock_speed( HalI2cBusId_t bus_id,  uint32_t clock_speed_Hz )
{
    /* Calculate half bit time in usec */
    HalI2cMasterSw_t *hi2c = hal_i2c_master_sw_bus_handle( bus_id );
    hi2c->half_clock_period = (1000000UL / clock_speed_Hz) / 4;
}

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_sw_reset( HalI2cBusId_t bus_id )
{
    HalI2cMasterSw_t *hi2c = hal_i2c_master_sw_bus_handle( bus_id );

    hal_gpio_init( hi2c->sda, MODE_OUT_OD, 1 );
    hal_gpio_init( hi2c->scl, MODE_OUT_OD, 1 );

    hal_gpio_write_pin( hi2c->sda, HIGH );
    hal_gpio_write_pin( hi2c->scl, HIGH );

    if( hal_gpio_read_pin( hi2c->sda ) == LOW )
    {
        for( uint8_t i = 0; i <= 9; i++ )
        {
            hal_gpio_write_pin( hi2c->scl, LOW );
            hal_delay_us(50);
            hal_gpio_write_pin( hi2c->scl, HIGH );
            hal_delay_us(50);
            if( hal_gpio_read_pin( hi2c->sda ) == HIGH )
            {
                break;
            }
        }
    }

    return I2C_STATUS_OK;
}

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_sw_transmit( HalI2cBusId_t bus_id,
                            uint8_t       address,
                            uint8_t     * buffer,
                            uint8_t       len )
{
    HalI2cMasterSw_t *hi2c = hal_i2c_master_sw_bus_handle( bus_id );

    hi2c->addr   = address << 1;
    hi2c->tx_len = len;
    hi2c->tx     = buffer;
    hi2c->rx_len = 0;
    hi2c->rx     = NULL;
    hi2c->mode   = HAL_I2C_MODE_WRITE;

#ifndef HAL_I2C_MASTER_SW_USE_TICKS
    do
    {
        hal_i2c_master_sw_step( hi2c );
        hal_delay_us( hi2c->half_clock_period );
    } while( hi2c->mode != HAL_I2C_MODE_IDLE );
#endif

    /* For compatibility with the H/W API we return HAL_I2C_STATUS_OK
     * and allow the callback to pick on on the actual status.
     */
    return I2C_STATUS_OK;
}

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_sw_receive( HalI2cBusId_t bus_id,
                           uint8_t       address,
                           uint8_t     * buffer,
                           uint8_t       len )
{
    HalI2cMasterSw_t *hi2c = hal_i2c_master_sw_bus_handle( bus_id );

    hi2c->addr   = address << 1;
    hi2c->tx_len = 0;
    hi2c->tx     = NULL;
    hi2c->rx_len = len;
    hi2c->rx     = buffer;
    hi2c->mode   = HAL_I2C_MODE_READ;

#ifndef HAL_I2C_MASTER_SW_USE_TICKS
    do
    {
        hal_i2c_master_sw_step( hi2c );
        hal_delay_us( hi2c->half_clock_period );
    } while( hi2c->mode != HAL_I2C_MODE_IDLE );
#endif

    /* For compatibility with the H/W API we return HAL_I2C_STATUS_OK
     * and allow the callback to pick on on the actual status.
     */
    return I2C_STATUS_OK;
}

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_sw_abort( HalI2cBusId_t bus_id,
                         uint8_t       address )
{
    return I2C_STATUS_OK;
}

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cState_t
hal_i2c_master_sw_get_state( HalI2cBusId_t bus_id )
{
    HalI2cMasterSw_t *hi2c = hal_i2c_master_sw_bus_handle( bus_id );
    return hi2c->state;
}

/* -------------------------------------------------------------------------- */

/** Return error status of last I2C transfer */

PUBLIC HalI2cError_t
hal_i2c_master_sw_get_error( HalI2cBusId_t bus_id )
{
    HalI2cMasterSw_t *hi2c = hal_i2c_master_sw_bus_handle( bus_id );
    return hi2c->error;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_i2c_master_sw_set_callback( HalI2cBusId_t    bus_id ,
                                HalI2cCallback_t callback_handler )
{
    HalI2cMasterSw_t *hi2c = hal_i2c_master_sw_bus_handle( bus_id );
    hi2c->callback = callback_handler;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_i2c_master_sw_tick( HalI2cBusId_t bus_id )
{
#ifdef HAL_I2C_MASTER_SW_USE_TICKS
    HalI2cMasterSw_t *hi2c = hal_i2c_master_sw_bus_handle( bus_id );
    if( hi2c->mode != HAL_I2C_MODE_IDLE )
    {
        hal_i2c_master_sw_step( hi2c );
    }
#endif
}

/* -------------------------------------------------------------------------- */
/* ----- Private Functions -------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Return the STM I2C handle using the generic Bus ID */

PRIVATE HalI2cMasterSw_t *
hal_i2c_master_sw_bus_handle( HalI2cBusId_t bus_id )
{
    switch( bus_id )
    {
        case I2C_BUS_1:
            return &hal_i2c1;
        case I2C_BUS_2:
            return &hal_i2c2;
        default:
            ASSERT( false );
    }
    return NULL;
}

/* -------------------------------------------------------------------------- */

/** I2C Master State Machine
 *  To be called from a timer or timed loop were the time interval
 *  needs to be half the expected bus clock rate.
 */

PRIVATE void
hal_i2c_master_sw_step( HalI2cMasterSw_t *me )
{
    do
    {
        me->immediate = false;
        //printf("s: %d\r\n", me->step );
        switch( me->step )
        {
            case HAL_I2C_STEP_IDLE:
                hal_gpio_write_pin( me->sda, HIGH );
                hal_gpio_write_pin( me->scl, HIGH );
                if( me->mode != HAL_I2C_MODE_IDLE )
                {
                    me->timeout = 0;
                    me->bit_count = 0;
                    me->index = 0;
                    me->state = I2C_STATE_BUSY;

                    WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_CHECK_BUS_IS_NOT_BUSY );
                }
                break;

                /* ---------------------- */

            case HAL_I2C_STEP_CHECK_BUS_IS_NOT_BUSY:
                if( ( hal_gpio_read_pin( me->sda ) == HIGH )
                    &&
                    ( hal_gpio_read_pin( me->scl ) == HIGH ) )
                {
                    IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_START_CONDITION_SDA );
                }
                else
                {
                    /* Bus seems to be busy */
                    me->status = I2C_STATUS_ERROR;
                    me->error  = I2C_ERROR_ARLO;
                    me->mode   = HAL_I2C_MODE_IDLE;
                    me->state  = I2C_STATE_READY;

                    IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_IDLE );
                }
                break;

                /* ---- Set Start Condition ----- */

            case HAL_I2C_STEP_START_CONDITION_SDA:
                hal_gpio_write_pin( me->sda, LOW );
                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_START_CONDITION_SCL );
                break;

            case HAL_I2C_STEP_START_CONDITION_SCL:
                if( hal_gpio_read_pin( me->scl ) == HIGH )
                {
                    hal_gpio_write_pin( me->scl, LOW );
                    WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_ADDR_SETUP );
                }
                else
                {
                    /* Bus seems to be busy */
                    hal_gpio_write_pin( me->sda, HIGH );
                    me->status = I2C_STATUS_ERROR;
                    me->error  = I2C_ERROR_ARLO;
                    me->mode = HAL_I2C_MODE_IDLE;
                    IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_IDLE );
                }
                break;

                /* ---- Start Send Address & R/W flag ----- */

            case HAL_I2C_STEP_ADDR_SETUP:
                me->data = me->addr; /* Assume address is already shifted up */
                if( me->mode == HAL_I2C_MODE_READ )
                {
                    me->data |= 1;
                }
                else
                {
                    me->data &= ~1;
                }
                me->bit_count = 0;
                IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_WRITE_DATA_BIT );
                break;

                /* ---- Start Send Data ----- */

            case HAL_I2C_STEP_WRITE_SETUP:
                me->data = me->tx[ me->index ];
                me->index++;
                me->bit_count = 0;
                IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_WRITE_DATA_BIT );
                break;

                /* ---- Sending Data ----- */

            case HAL_I2C_STEP_WRITE_DATA_BIT:
                hal_gpio_write_pin( me->sda, me->data & 0x80 ); /* Set SDA before SCK */
                me->data <<= 1;
                me->bit_count++;
                hal_gpio_write_pin( me->scl, HIGH );
                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_WRITE_WAIT_CLOCK_BIT );
                break;

            case HAL_I2C_STEP_WRITE_WAIT_CLOCK_BIT:
                /* Allow for clock stretching by the slave */
                if( hal_gpio_read_pin( me->scl ) == HIGH )
                {
                    IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_WRITE_CLOCK_BIT );
                }
                break;

            case HAL_I2C_STEP_WRITE_CLOCK_BIT:
                hal_gpio_write_pin( me->scl, LOW );
                if( me->bit_count < 8 )
                {
                    WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_WRITE_DATA_BIT );
                }
                else
                {
                    hal_gpio_write_pin( me->sda, HIGH ); /* Release SDA for ACK/NAK */
                    WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_WAIT_ACK );
                }
                break;

                /* ---- Check Acknowledgement ----- */

            case HAL_I2C_STEP_WAIT_ACK:
                me->timeout = 0;
                hal_gpio_write_pin( me->scl, HIGH );
                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_WAIT_ACK_CLK );
                break;

            case HAL_I2C_STEP_WAIT_ACK_CLK:
                /* Check clock stretching from slave */
                if( hal_gpio_read_pin( me->scl ) == HIGH )
                {
                    /* Slave is ready */
                    IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_WRITE_GET_ACK );
                }
                else
                {
                    /* Slave is clock stretching */
                    me->timeout++;
                    if( me->timeout > HAL_I2C_SLAVE_TIMEOUT )
                    {
                        me->status = I2C_STATUS_ERROR;
                        me->error  = I2C_ERROR_TIMEOUT;
                        WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_STOP_CONDITION );
                    }
                }
                break;

            case HAL_I2C_STEP_WRITE_GET_ACK:
                me->acked = hal_gpio_read_pin( me->sda ) == LOW;
                hal_gpio_write_pin( me->scl, LOW );
                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_WRITE_FINISH_ACK );
                break;

            case HAL_I2C_STEP_WRITE_FINISH_ACK:
                if( me->acked )
                {
                    switch( me->mode )
                    {
                        case HAL_I2C_MODE_WRITE:
                            if( ( me->tx_len > 0 )
                                && ( me->index < me->tx_len ) )
                            {
                                /* More to send, setup next data bit before
                                 * releasing CLK
                                 */
                                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_WRITE_SETUP );
                            }
                            else
                            {
                                /* FINISHED TX */
                                IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_STOP_CONDITION );
                            }
                            break;

                        case HAL_I2C_MODE_READ:
                            /* Here we arrived when there was an ACK on the
                             * address that we want to read from
                             */
                            if( ( me->rx_len > 0 )
                                && ( me->index < me->rx_len ) )
                            {
                                /* More to read */
                                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_READ_SETUP );
                            }
                            else
                            {
                                /* FINISHED RX */
                                IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_STOP_CONDITION );
                            }
                            break;
                        default:
                            /* Should never have anything else than READ/WRITE */
                            ASSERT(false);
                            break;
                    }
                }
                else
                {
                    /* SDA High => NACK */
                    IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_STOP_CONDITION );
                }
                break;

                /* ---- Generate Stop Condition ----- */

            case HAL_I2C_STEP_STOP_CONDITION:
                hal_gpio_write_pin( me->sda, LOW );
                hal_gpio_write_pin( me->scl, HIGH );
                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_STOP_1 );
                break;

            case HAL_I2C_STEP_STOP_1:
                hal_gpio_write_pin( me->sda, HIGH );
                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_STOP_CONDITION_WAIT_IDLE );
                break;

            case HAL_I2C_STEP_STOP_CONDITION_WAIT_IDLE:
                me->timeout++;
                if( hal_gpio_read_pin( me->sda ) == HIGH )
                {
                    if( me->acked )
                    {
                        me->status = I2C_STATUS_OK;
                        me->error = I2C_ERROR_NONE;
                        if( me->callback )
                        {
                            if( me->mode == HAL_I2C_MODE_WRITE )
                            {
                                (*me->callback)( me->id,
                                                 I2C_CALLBACK_TX_COMPLETE );
                            }
                            else
                            {
                                (*me->callback)( me->id,
                                                 I2C_CALLBACK_RX_COMPLETE );
                            }
                        }
                    }
                    else
                    {
                        me->status = I2C_STATUS_ERROR;
                        me->error  = I2C_ERROR_AF;
                        if( me->callback )
                        {
                            (*me->callback)( me->id,
                                             I2C_CALLBACK_ERROR );
                        }
                    }
                    me->mode = HAL_I2C_MODE_IDLE;
                    IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_IDLE );
                }
                else
                {
                    if( me->timeout > HAL_I2C_SLAVE_TIMEOUT )
                    {
                        me->status = I2C_STATUS_ERROR;
                        me->error  = I2C_ERROR_TIMEOUT;
                        //ASSERT(false);
                        if( me->callback )
                        {
                            (*me->callback)( me->id,
                                             I2C_CALLBACK_ERROR );
                        }
                        me->mode = HAL_I2C_MODE_IDLE;
                        IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_IDLE );
                    }
                }
                break;

                /* ---- Receive Byte ----- */

            case HAL_I2C_STEP_READ_SETUP:
                me->data = 0;
                me->bit_count = 0;
                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_READ_CLOCK_BIT );
                break;

            case HAL_I2C_STEP_READ_CLOCK_BIT:
                hal_gpio_write_pin( me->scl, HIGH );
                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_READ_DATA_BIT );
                break;

            case HAL_I2C_STEP_READ_DATA_BIT:
                me->data |= hal_gpio_read_pin( me->sda ) ? 1 : 0;
                me->bit_count++;
                hal_gpio_write_pin( me->scl, LOW );

                if( me->bit_count < 8 )
                {
                    me->data <<= 1;
                    WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_READ_CLOCK_BIT );
                }
                else
                {
                    me->rx[ me->index ] = me->data;
                    me->index++;
                    if( me->index < me->rx_len )
                    {
                        /* Signal more to read */
                        WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_GENERATE_ACK );
                    }
                    else
                    {
                        /* Signal end of read sequence */
                        WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_GENERATE_NAK );
                    }
                }
                break;

                /* ---- Generate Read Ack/Nack ----- */

            case HAL_I2C_STEP_GENERATE_ACK:
                hal_gpio_write_pin( me->sda, LOW );
                hal_gpio_write_pin( me->scl, HIGH );
                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_GENERATE_ACK_CLOCK );
                break;

            case HAL_I2C_STEP_GENERATE_NAK:
                hal_gpio_write_pin( me->sda, HIGH );
                hal_gpio_write_pin( me->scl, HIGH );
                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_GENERATE_ACK_CLOCK );
                break;

            case HAL_I2C_STEP_GENERATE_ACK_CLOCK:
                hal_gpio_write_pin( me->scl, LOW );
                WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_GENERATE_ACK_DONE );
                break;

            case HAL_I2C_STEP_GENERATE_ACK_DONE:
                hal_gpio_write_pin( me->scl, LOW );
                hal_gpio_write_pin( me->sda, HIGH );
                if( me->index < me->rx_len )
                {
                    WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_READ_SETUP );
                }
                else
                {
                    hal_gpio_write_pin( me->sda, LOW );
                    WAIT_NEXT_I2C_STEP( HAL_I2C_STEP_STOP_CONDITION );
                }
                break;

                /* ---- Error Handling ----- */

            case HAL_I2C_STEP_BERR:
                hal_gpio_write_pin( me->sda, HIGH );
                hal_gpio_write_pin( me->scl, HIGH );
                me->mode = HAL_I2C_MODE_IDLE;
                me->status = I2C_STATUS_ERROR;
                me->error  = I2C_ERROR_BERR;
                if( me->callback )
                {
                    (*me->callback)( me->id,
                                     I2C_CALLBACK_ERROR );
                }
                IMMEDIATE_NEXT_I2C_STEP( HAL_I2C_STEP_IDLE );
                break;
        }
    } while( me->immediate );
}

/* ----- End ---------------------------------------------------------------- */

