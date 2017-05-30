/* ov2640 - ov2640 camera driver   
 *    
 * Copyrith (c) 2006, OmniVision  
 *    
 * This program is free software; you can redistribute it and/or modify it  
 * under the terms of the GNU General Public License as published by the  
 * Free Software Foundation; either version 2 of the License, or (at your  
 * option) any later version. NO WARRANTY OF ANY KIND is expressed or implied.  
 *  
 *  
 * OmniVision is a trademark of OmniVision Technologies, Inc.   
 *  
 *  Version 1.00   July.04.2006   david zhu  
 *                        david@ovt.com.cn  
 *    
 */    
   
#include <linux/types.h>   
#include <linux/delay.h>   
#include <linux/videodev.h>   
#include <asm/dma.h>   
   
#include "pxaovcamera.h"   
#include "ovcamerachip.h"   
#include "ov2640.h"   
   
#define DEBUG   
   
#ifdef DEBUG   
#define ov2640print(fmt,args...) printk(KERN_WARNING "OV2640:" fmt, ## args)   
#else   
#define ov2640print(fmt,args...)    
#endif   
   
ovcamerachip g_ovcamerachip;   
   
#define REG11A_UXGA 0x02   
#define REG3DA_UXGA 0x2E   
#define REG3DA_SVGA 0x35   
#define QCIF                176   
#define QVGA               320   
#define CIF                   352   
#define VGA                  640   
#define SVGA                800   
#define XGA                  1024   
#define SXGA                1280   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
/********old code by jiahongling*****************************  
const static u8 OV_REGS_INITIALIZE[] =  
{  
    0xff,   0x00,  
    0x2c,   0xff,  
    0x2e,   0xdf,  
    0xff,   0x01,  
    0x12,   0x80,  
    0x3c,   0x35,  
    0x11,   0x02,  
    0x04,   0x28,  
    0x13,   0xe5,  
    0x14,   0x48,  
    0x2c,   0x0c,  
    0x33,   0x78,  
    0x3b,   0xf7,  
    0x36,   0x00,  
    0x37,   0x42,   
    0x3e,   0x00,  
    0x43,   0x11,  
    0x16,   0x10,  
    0x39,   0x82,  
    0x35,   0xc8,  
    0x22,   0x0f,  
    0x23,   0x00,  
    0x34,   0xa0,  
    0x06,   0x08,  
    0x07,   0xc0,  
    0x0d,   0xb7,  
    0x0e,   0x29,   
    0x4c,   0x00,  
    0x4a,   0x81,  
    0x21,   0x99,  
    0x09,   0x02,  
    0x24,   0x3e,   
    0x25,   0x38,   
    0x26,   0x81,   
    0x5c,   0x00,  
    0x63,   0x00,  
    0x7c,   0x00,  
    0x61,   0x70,  
    0x62,   0x80,  
    0x20,   0x80,  
    0x28,   0x30,  
    0x6c,   0x00,  
    0x6e,   0x00,  
    0x70,   0x02,  
    0x71,   0x94,  
    0x73,   0xc1,  
    0x3d,   0x34,  
    0x5a,   0x57,  
    0x4f,   0xbb,  
    0x50,   0x9c,  
    0x6d,   0x80,  
    0x39,   0x02,  
    0x3a,   0x33,  
    0x3b,   0xfb,  
    0x3c,   0x32,  
  
    0xff,   0x00,  
    0xe5,   0x7f,   
    0xf9,   0xc0,   
    0x41,   0x24,   
    0xe0,   0x14,  
    0x76,   0xff,   
    0x33,   0xa0,    
    0x42,   0x20,     
    0x43,   0x18,     
    0x4c,   0x00,     
    0x87,   0xd0,     
    0x88,   0x3f,    
    0xd7,   0x03,     
    0xd9,   0x10,     
    0xd3,   0x82,     
    0xc8,   0x08,     
    0xc9,   0x80,     
    0x7c,   0x00,     
    0x7d,   0x00,     
    0x7c,   0x03,     
    0x7d,   0x48,     
    0x7d,   0x48,     
    0x7c,   0x08,     
    0x7d,   0x20,     
    0x7d,   0x10,     
    0x7d,   0x0e,     
    0x90,   0x00,     
    0x91,   0x0e,     
    0x91,   0x1a,     
    0x91,   0x31,     
    0x91,   0x5a,     
    0x91,   0x69,     
    0x91,   0x75,     
    0x91,   0x7e,     
    0x91,   0x88,     
    0x91,   0x8f,    
    0x91,   0x96,     
    0x91,   0xa3,     
    0x91,   0xaf,    
    0x91,   0xc4,     
    0x91,   0xd7,     
    0x91,   0xe8,     
    0x91,   0x20,     
    0x92,   0x00,     
    0x93,   0x06,     
    0x93,   0xe3,    
    0x93,   0x31,     
    0x93,   0x05,     
    0x93,   0x00,     
    0x93,   0x04,     
    0x93,   0x00,     
    0x93,   0x00,     
    0x93,   0x00,     
    0x93,   0x00,     
    0x93,   0x00,     
    0x93,   0x00,     
    0x93,   0x00,     
    0x96,   0x00,     
    0x97,   0x08,     
    0x97,   0x19,     
    0x97,   0x02,     
    0x97,   0x0c,     
    0x97,   0x24,     
    0x97,   0x30,     
    0x97,   0x28,     
    0x97,   0x26,     
    0x97,   0x02,     
    0x97,   0x98,     
    0x97,   0x80,     
    0x97,   0x00,     
    0x97,   0x00,     
    0xc3,   0xed,     
    0xc4,   0x9a,     
    0xa4,   0x01,     
    0xc5,   0x11,     
    0xc6,   0x51,     
    0xc7,   0x00,     
    0xb6,   0x66,     
    0xb8,   0xA5,     
    0xb7,   0x64,     
    0xb9,   0x7C,     
    0xb3,   0xaf,     
    0xb4,   0x97,     
    0xb5,   0xFF,     
    0xb0,   0xC5,     
    0xb1,   0x94,     
    0xb2,   0x0f,     
    0xc4,   0x9d,     
    0xc0,   0xc8,     
    0xc1,   0x96,     
    0x86,   0x1d,     
    0x50,   0x00,     
    0x51,   0x90,     
    0x52,   0x18,     
    0x53,   0x00,     
    0x54,   0x00,     
    0x55,   0x88,     
    0x57,   0x00,     
    0x5a,   0x90,     
    0x5b,   0x18,     
    0x5c,   0x05,     
    0xc3,   0xed,     
    0x7f,   0x00,     
    0xda,   0x04,     
    0xe5,   0x1f,     
    0xe1,   0x77,     
    0xe0,   0x00,     
    0xdd,   0xff,     
    0x05,   0x00,    
    0x3d,   0x48,     
    0xff,   0x01,   // set sensor to SVGA  
    0x12,   0x40,     
    0x17,   0x11,     
    0x18,   0x43,     
    0x19,   0x00,     
    0x1a,   0x4b,     
    0x32,   0x09,     
    0x37,   0xc0,     
    0x4f,   0xca,     
    0x50,   0xa8,     
    0x6d,   0x00,     
    0x3d,   0x38,     
    0x35,   0xc0,     
    0x22,   0x0f,     
    0x6d,   0x00,     
    0xff,   0x00,   // set output to QCIF   // keep view angle  
    0x86,   0x3d,     
    0xc0,   0x64,       // image horizontal size HSIze[10:3]  
    0xc1,   0x4b,       // image Vertical size VSIze[10:3]  
    0x8c,   0x00,       // HSize[11],HSize[2:0],Vsize[2:0]  
    0x50,   0x92,       // down sample /4  
    0x51,   0xC8,       // H_Size[7:0],     0x(real/4)  
    0x52,   0x96,   // V_Size[7:0]  (real/4)  
    0x53,   0x00,       // OFFSET_X[7 0]  
    0x54,   0x00,   // OFFSET_Y[7 0]  
    0x55,   0x00,   // V_size[8],offset_y[10:8],H_Size[8],offset_X[10:8]  
    0x5a,   0x2c,   // outw[7:0]  real/4  
    0x5b,   0x24,       // outH[7:0]  real/4  
    0x5c,   0x00,       // bit [7:4],zmspd  ,bit2 outh[8],bit 1..0  ,outw[9 8]  
    0xd3,   0x04,   // bit 6..0,DVP PCLK=sysclk(48)/[6..0]  
    0xe0,   0x04,   // add the following 4 line to set  YUV output  
    0xe1,   0x67,   
    0xda,   0x00,   // RGB565 0x08 YUV 0x00  
    0xe0,   0x00,   
          
    0x00,   0x00   
};  
********************************************************/   
/////////////////////////////////////////////////////////   
/**************** add by syp according  to ov *******************/   
/////////////////////////////////////////////////////////   
const static u8 OV_REGS_INITIALIZE[] =   
{   
    0xff,   0x00,//Ê¹ÄÜtable12   
    0x2c,   0xff,//   
    0x2e,   0xdf,   
    0xff,   0x01,   
    //0x12,     0x80,   
    0x3c,   0x32,   
    0x11,   0x00,//ÄÚ²¿Ê±ÖÓ¹Ø±Õ   
    0x09,        0x02,   
    0x04,   0x28,   
    0x13,   0xe5,   
    0x14,   0x48,   
    0x2c,   0x0c,   
    0x33,   0x78,   
    0x3a,        0x33,   
    0x3b,   0xfb,   
    //0x36,     0x00,   
    //0x37,     0x42,    
    0x3e,   0x00,   
    0x43,   0x11,   
    0x16,   0x10,   
    0x39,   0x02,   
    0x35,   0x88,   
    0x22,   0x0a,   
    0x37,        0x40,   
    0x23,   0x00,   
    0x34,   0xa0,   
    0x36,        0x1a,//   
    0x06,   0x02,///   
    0x07,   0xc0,   
    0x0d,   0xb7,   
    0x0e,   0x01, //   
    0x4c,   0x00,   
    0x4a,   0x81,   
    0x21,   0x99,   
    //0x24,        0x40,//   
    //0x09,     0x02,   
    0x24,   0x40,    
    0x25,   0x38,    
    0x26,   0x82,    
    0x5c,   0x00,   
    0x63,   0x00,   
    0x46,        0x3f,     
    0x61,   0x70,   
    0x62,   0x80,   
    0x7c,   0x05,   
    0x20,   0x80,   
    0x28,   0x30,   
    0x6c,   0x00,   
    0x6d,        0x80,//   
    0x6e,   0x00,   
    0x70,   0x02,   
    0x71,   0x94,   
    0x73,   0xc1,   
    0x3d,   0x34,   
    0x5a,   0x57,   
    0x4f,   0xbb,   
    0x50,   0x9c,   
    0xff,        0x00,//   
    /*0x6d,     0x80,  
    0x39,   0x02,  
    0x3a,   0x33,  
    0x3b,   0xfb,  
    0x3c,   0x32,  
  
    0xff,   0x00,*/   
    0xe5,   0x7f,    
    0xf9,   0xc0,    
    0x41,   0x24,    
    0xe0,   0x14,   
    0x76,   0xff,    
    0x33,   0xa0,     
    0x42,   0x20,      
    0x43,   0x18,      
    0x4c,   0x00,      
    0x87,   0xd0,      
    0x88,   0x3f,     
    0xd7,   0x03,      
    0xd9,   0x10,      
    0xd3,   0x82,      
    0xc8,   0x08,      
    0xc9,   0x80,      
    0x7c,   0x00,      
    0x7d,   0x00,      
    0x7c,   0x03,      
    0x7d,   0x48,      
    0x7d,   0x48,      
    0x7c,   0x08,      
    0x7d,   0x20,      
    0x7d,   0x10,      
    0x7d,   0x0e,      
    0x90,   0x00,      
    0x91,   0x0e,      
    0x91,   0x1a,      
    0x91,   0x31,      
    0x91,   0x5a,   //   
    0x91,   0x69,      
    0x91,   0x75,      
    0x91,   0x7e,      
    0x91,   0x88,      
    0x91,   0x8f,     
    0x91,   0x96,      
    0x91,   0xa3,      
    0x91,   0xaf,     
    0x91,   0xc4,      
    0x91,   0xd7,      
    0x91,   0xe8,      
    0x91,   0x20,      
    0x92,   0x00,      
    0x93,   0x06,      
    0x93,   0xe3,     
    //0x93,     0x31,      
    0x93,   0x05,   
    0x93,   0x05,    
    0x93,   0x00,      
    0x93,   0x04,      
    0x93,   0x00,      
    0x93,   0x00,      
    0x93,   0x00,      
    0x93,   0x00,      
    0x93,   0x00,      
    0x93,   0x00,      
    0x93,   0x00,      
    0x96,   0x00,      
    0x97,   0x08,      
    0x97,   0x19,      
    0x97,   0x02,      
    0x97,   0x0c,      
    0x97,   0x24,      
    0x97,   0x30,      
    0x97,   0x28,      
    0x97,   0x26,      
    0x97,   0x02,      
    0x97,   0x98,      
    0x97,   0x80,      
    0x97,   0x00,      
    0x97,   0x00,      
    0xc3,   0xed,      
    //0xc4,     0x9a,      
    0xa4,   0x00,  //    
    0xc5,   0x11,      
    0xc6,   0x51,     
    0xbf,        0x80,//   
    0xc7,   0x00,      
    0xb6,   0x66,      
    0xb8,   0xA5,      
    0xb7,   0x64,      
    0xb9,   0x7C,      
    0xb3,   0xaf,      
    0xb4,   0x97,      
    0xb5,   0xFF,      
    0xb0,   0xC5,      
    0xb1,   0x94,      
    0xb2,   0x0f,      
    0xc4,   0x5c,  //    
    0xc0,   0xc8,      
    0xc1,   0x96,      
    0x86,   0x1d,      
    0x50,   0x00,      
    0x51,   0x90,      
    0x52,   0x18,      
    0x53,   0x00,      
    0x54,   0x00,      
    0x55,   0x88,      
    0x57,   0x00,      
    0x5a,   0x90,      
    0x5b,   0x18,      
    0x5c,   0x05,      
    0xc3,   0xed,      
    0x7f,   0x00,      
    0xda,   0x00,      
    0xe5,   0x1f,      
    0xe1,   0x77,      
    0xe0,   0x00,      
    0xdd,   0x7f,      
    0x05,   0x00,     
    /*0x3d,     0x48,     
    0xff,   0x01,   // set sensor to SVGA  
    0x12,   0x40,     
    0x17,   0x11,     
    0x18,   0x43,     
    0x19,   0x00,     
    0x1a,   0x4b,     
    0x32,   0x09,     
    0x37,   0xc0,     
    0x4f,   0xca,     
    0x50,   0xa8,     
    0x6d,   0x00,     
    0x3d,   0x38,     
    0x35,   0xc0,     
    0x22,   0x0f,     
    0x6d,   0x00,     
    0xff,   0x00,   // set output to QCIF   // keep view angle  
    0x86,   0x3d,     
    0xc0,   0x64,       // image horizontal size HSIze[10:3]  
    0xc1,   0x4b,       // image Vertical size VSIze[10:3]  
    0x8c,   0x00,       // HSize[11],HSize[2:0],Vsize[2:0]  
    0x50,   0x92,       // down sample /4  
    0x51,   0xC8,       // H_Size[7:0],     0x(real/4)  
    0x52,   0x96,   // V_Size[7:0]  (real/4)  
    0x53,   0x00,       // OFFSET_X[7 0]  
    0x54,   0x00,   // OFFSET_Y[7 0]  
    0x55,   0x00,   // V_size[8],offset_y[10:8],H_Size[8],offset_X[10:8]  
    0x5a,   0x2c,   // outw[7:0]  real/4  
    0x5b,   0x24,       // outH[7:0]  real/4  
    0x5c,   0x00,       // bit [7:4],zmspd  ,bit2 outh[8],bit 1..0  ,outw[9 8]  
    0xd3,   0x04,   // bit 6..0,DVP PCLK=sysclk(48)/[6..0]  
    0xe0,   0x04,   // add the following 4 line to set  YUV output  
    0xe1,   0x67,   
    0xda,   0x00,   // RGB565 0x08 YUV 0x00  
    0xe0,   0x00,   
          
    0x00,   0x00 */   
};////end code by syp 2008.6.24   
/////////////////////////////////////////////////////////////   
//apply by ov   
/*--------CIF:352*288----------*/   
const static u8 OV2640_UXGA_CIF[]=   
{   
      0xff,      0x00,   
      0xe0,      0x04,   
      0xc0,      0xc8,   
      0xc1,      0x96,   
      0x86,      0x35,   
      0x50,      0x92,   
      0x51,      0x90,   
      0x52,      0x2c,   
      0x53,      0x00,   
      0x54,      0x00,   
      0x55,      0x88,   
      0x57,      0x00,   
      0x5a,      0x58,   
      0x5b,      0x48,   
      0x5c,      0x00,   
      0xd3,      0x08,   
      0xe0,      0x00   
};   
/*--------QCIF:176*144----------*/   
const static u8 OV2640_UXGA_QCIF[]=   
{   
      0xff,      0x00,   
      0xc0,      0xC8,   
      0xc1,      0x96,   
      0x8c,      0x00,   
      0x86,      0x3D,   
      0x50,      0x9B,   
      0x51,      0x90,   
      0x52,      0x2C,   
      0x53,      0x00,   
      0x54,      0x00,   
      0x55,      0x88,   
      0x5a,      0x2C,   
      0x5b,      0x24,   
      0x5c,      0x00,   
      0xd3,      0x04   
};   
/*-------QVGA:320*240---------*/   
const static u8 OV2640_UXGA_QVGA[]=   
{   
      0xff,      0x00,   
      0xe0,      0x04,   
      0xc0,      0xc8,   
      0xc1,      0x96,   
      0x86,      0x3d,   
      0x50,      0x92,   
      0x51,      0x90,   
      0x52,      0x2c,   
      0x53,      0x00,   
      0x54,      0x00,   
      0x55,      0x88,   
      0x57,      0x00,   
      0x5a,      0x50,   
      0x5b,      0x3c,   
      0x5c,      0x00,   
      0xd3,      0x04,   
      0xe0,      0x00   
};   
/*-------SVGA:800*600 ---------*/   
const static u8 OV2640_UXGA_SVGA[]=   
{   
      0xff,      0x00,   
      0xe0,      0x04,   
      0xc0,      0xc8,   
      0xc1,      0x96,   
      0x86,      0x35,   
      0x50,      0x89,   
      0x51,      0x90,   
      0x52,      0x2c,   
      0x53,      0x00,   
      0x54,      0x00,   
      0x55,      0x88,   
      0x57,      0x00,   
      0x5a,      0xc8,   
      0x5b,      0x96,   
      0x5c,      0x00,   
      0xd3,      0x02,   
      0xe0,      0x00   
};   
/*--------SXGA:1280*1024---------*/   
const static u8 OV2640_UXGA_SXGA[]=   
{   
      0xff,      0x00,   
      0xe0,      0x04,   
      0xc0,      0xc8,   
      0xc1,      0x96,   
      0x86,      0x3d,   
      0x50,      0x00,   
      0x51,      0x90,   
      0x52,      0x2c,   
      0x53,      0x00,   
      0x54,      0x00,   
      0x55,      0x88,   
      0x57,      0x00,   
      0x5a,      0x40,   
      0x5b,      0xf0,   
      0x5c,      0x01,   
      0xd3,      0x82,   
      0xe0,      0x00   
};   
/*-------VGA:640*480---------*/   
const static u8 OV2640_UXGA_VGA[]=   
{   
      0xff,      0x00,   
      0xe0,      0x04,   
      0xc0,      0xc8,   
      0xc1,      0x96,   
      0x86,      0x3d,   
      0x50,      0x89,   
      0x51,      0x90,   
      0x52,      0x2c,   
      0x53,      0x00,   
      0x54,      0x00,   
      0x55,      0x88,   
      0x57,      0x00,   
      0x5a,      0xa0,   
      0x5b,      0x78,   
      0x5c,      0x00,   
      0xd3,      0x04,   
      0xe0,      0x00   
};   
/*-------XGA:1024*768---------*/   
const static u8 OV2640_UXGA_XGA[]=   
{   
      0xff,      0x00,   
      0xc0,      0xC8,   
      0xc1,      0x96,   
      0x8c,      0x00,   
      0x86,      0x3D,   
      0x50,      0x00,   
      0x51,      0x90,   
      0x52,      0x2C,   
      0x53,      0x00,   
      0x54,      0x00,   
      0x55,      0x88,   
      0x5a,      0x00,   
      0x5b,      0xC0,   
      0x5c,      0x01,   
      0xd3,      0x02   
};   
const static u8 *OV2640_SETTING_PELS[]=   
{   
        OV2640_UXGA_QCIF,   
        OV2640_UXGA_QVGA,   
    OV2640_UXGA_CIF,   
    OV2640_UXGA_VGA,   
    OV2640_UXGA_SVGA,   
    OV2640_UXGA_XGA,   
    OV2640_UXGA_SXGA       
};   
   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
const static u8 OV2640_BRIGHTNESS_DISABLE[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x00,   0xff,   
    0x7D,   0x00,   0x04,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_BRIGHTNESS_ENABLE[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x00,   0xff,   
    0x7D,   0x04,   0x04,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_BRIGHTNESS_LEVEL0[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x09,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x08,   0x08,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_BRIGHTNESS_LEVEL1[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x09,   0xff,   
    0x7D,   0x10,   0xff,   
    0x7D,   0x08,   0x08,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_BRIGHTNESS_LEVEL2[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x09,   0xff,   
    0x7D,   0x00,   0xff,   
    0x7D,   0x00,   0x08,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_BRIGHTNESS_LEVEL3[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x09,   0xff,   
    0x7D,   0x10,   0xff,   
    0x7D,   0x00,   0x08,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_BRIGHTNESS_LEVEL4[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x09,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x00,   0x08,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_BRIGHTNESS_LEVEL5[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x09,   0xff,   
    0x7D,   0x30,   0xff,   
    0x7D,   0x00,   0x08,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_BRIGHTNESS_LEVEL6[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x09,   0xff,   
    0x7D,   0x40,   0xff,   
    0x7D,   0x00,   0x08,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_BRIGHTNESS_LEVEL7[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x09,   0xff,   
    0x7D,   0x50,   0xff,   
    0x7D,   0x00,   0x08,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_BRIGHTNESS_LEVEL8[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x09,   0xff,   
    0x7D,   0x60,   0xff,   
    0x7D,   0x00,   0x08,   
    0x00,   0x00,   0x00   
};   
   
const static u8 *OV_SETTING_BRIGHTNESS[]=   
{   
    OV2640_BRIGHTNESS_LEVEL0,   
    OV2640_BRIGHTNESS_LEVEL1,   
    OV2640_BRIGHTNESS_LEVEL2,   
    OV2640_BRIGHTNESS_LEVEL3,   
    OV2640_BRIGHTNESS_LEVEL4,   
    OV2640_BRIGHTNESS_LEVEL5,   
    OV2640_BRIGHTNESS_LEVEL6,   
    OV2640_BRIGHTNESS_LEVEL7,   
    OV2640_BRIGHTNESS_LEVEL8,   
};   
   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
const static u8 OV2640_CONTRAST_DISABLE[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x00,   0xff,   
    0x7D,   0x00,   0x04,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_CONTRAST_ENABLE[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x00,   0xff,   
    0x7D,   0x04,   0x04,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_CONTRAST_LEVEL0[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x07,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x10,   0xff,   
    0x7D,   0x4a,   0xff,   
    0x7D,   0x06,   0x0c,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_CONTRAST_LEVEL1[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x07,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x14,   0xff,   
    0x7D,   0x40,   0xff,   
    0x7D,   0x06,   0x0c,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_CONTRAST_LEVEL2[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x07,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x18,   0xff,   
    0x7D,   0x34,   0xff,   
    0x7D,   0x06,   0x0c,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_CONTRAST_LEVEL3[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x07,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x1c,   0xff,   
    0x7D,   0x2a,   0xff,   
    0x7D,   0x06,   0x0c,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_CONTRAST_LEVEL4[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x07,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x06,   0x0c,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_CONTRAST_LEVEL5[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x07,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x24,   0xff,   
    0x7D,   0x16,   0xff,   
    0x7D,   0x06,   0x0c,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_CONTRAST_LEVEL6[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x07,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x28,   0xff,   
    0x7D,   0x0c,   0xff,   
    0x7D,   0x06,   0x0c,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_CONTRAST_LEVEL7[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x07,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x2c,   0xff,   
    0x7D,   0x02,   0xff,   
    0x7D,   0x06,   0x0c,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_CONTRAST_LEVEL8[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x07,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x30,   0xff,   
    0x7D,   0x08,   0xff,   
    0x7D,   0x0e,   0x0c,   
    0x00,   0x00,   0x00   
};   
   
const static u8 *OV_SETTING_CONTRAST[]=   
{   
    OV2640_CONTRAST_LEVEL0,   
    OV2640_CONTRAST_LEVEL1,   
    OV2640_CONTRAST_LEVEL2,   
    OV2640_CONTRAST_LEVEL3,   
    OV2640_CONTRAST_LEVEL4,   
    OV2640_CONTRAST_LEVEL5,   
    OV2640_CONTRAST_LEVEL6,   
    OV2640_CONTRAST_LEVEL7,   
    OV2640_CONTRAST_LEVEL8     
};   
   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
const static u8 OV2640_HUE_DISABLE[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x00,   0xff,   
    0x7D,   0x00,   0x01,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_HUE_ENABLE[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x00,   0xff,   
    0x7D,   0x01,   0x01,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_HUE_LEVEL0[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x01,   0xff,   
    0x7D,   0x40,   0xff,   
    0x7D,   0x6F,   0xff,   
    0x7C,   0x0A,   0xff,   
    0x7D,   0x05,   0x03,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_HUE_LEVEL1[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x01,   0xff,   
    0x7D,   0x6F,   0xff,   
    0x7D,   0x40,   0xff,   
    0x7C,   0x0A,   0xff,   
    0x7D,   0x05,   0x03,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_HUE_LEVEL2[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x01,   0xff,   
    0x7D,   0x80,   0xff,   
    0x7D,   0x00,   0xff,   
    0x7C,   0x0A,   0xff,   
    0x7D,   0x06,   0x03,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_HUE_LEVEL3[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x01,   0xff,   
    0x7D,   0x6F,   0xff,   
    0x7D,   0x40,   0xff,   
    0x7C,   0x0A,   0xff,   
    0x7D,   0x06,   0x03,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_HUE_LEVEL4[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x01,   0xff,   
    0x7D,   0x40,   0xff,   
    0x7D,   0x6F,   0xff,   
    0x7C,   0x0A,   0xff,   
    0x7D,   0x06,   0x03,   
    0x00,   0x00,   0x00   
};   
   
const static u8 *OV_SETTING_HUE[]=   
{   
    OV2640_HUE_LEVEL0,   
    OV2640_HUE_LEVEL1,   
    OV2640_HUE_LEVEL2,   
    OV2640_HUE_LEVEL3,   
    OV2640_HUE_LEVEL4      
};   
   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
const static u8 OV2640_SATURATION_DISABLE[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x00,   0xff,   
    0x7D,   0x00,   0x02,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SATURATION_ENABLE[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x00,   0xff,   
    0x7D,   0x02,   0x02,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SATURATION_LEVEL0[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x03,   0xff,   
    0x7D,   0x00,   0xff,   
    0x7D,   0x00,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SATURATION_LEVEL1[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x03,   0xff,   
    0x7D,   0x10,   0xff,   
    0x7D,   0x10,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SATURATION_LEVEL2[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x03,   0xff,   
    0x7D,   0x20,   0xff,   
    0x7D,   0x20,   0xff,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_SATURATION_LEVEL3[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x03,   0xff,   
    0x7D,   0x30,   0xff,   
    0x7D,   0x30,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SATURATION_LEVEL4[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x03,   0xff,   
    0x7D,   0x40,   0xff,   
    0x7D,   0x40,   0xff,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_SATURATION_LEVEL5[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x03,   0xff,   
    0x7D,   0x50,   0xff,   
    0x7D,   0x50,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SATURATION_LEVEL6[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x03,   0xff,   
    0x7D,   0x60,   0xff,   
    0x7D,   0x60,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SATURATION_LEVEL7[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x03,   0xff,   
    0x7D,   0x70,   0xff,   
    0x7D,   0x70,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SATURATION_LEVEL8[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7C,   0x03,   0xff,   
    0x7D,   0x80,   0xff,   
    0x7D,   0x80,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 *OV_SETTING_SATURATION[]=   
{   
    OV2640_SATURATION_LEVEL0,   
    OV2640_SATURATION_LEVEL1,   
    OV2640_SATURATION_LEVEL2,   
    OV2640_SATURATION_LEVEL3,   
    OV2640_SATURATION_LEVEL4,   
    OV2640_SATURATION_LEVEL5,   
    OV2640_SATURATION_LEVEL6,   
    OV2640_SATURATION_LEVEL7,   
    OV2640_SATURATION_LEVEL8       
};   
   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
const static u8 OV2640_SHARPNESS_AUTO[]=   
{   
    0xFF,   0x00,   0xff,   
    0x92,   0x01,   0xff,   
    0x93,   0x20,   0x20,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SHARPNESS_MANUAL[]=   
{   
    0xFF,   0x00,   0xff,   
    0x92,   0x01,   0xff,   
    0x93,   0x00,   0x20,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SHARPNESS_LEVEL0[]=   
{   
    0xFF,   0x00,   0xff,   
    0x92,   0x01,   0xff,   
    0x93,   0xc0,   0x1f,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_SHARPNESS_LEVEL1[]=   
{   
    0xFF,   0x00,   0xff,   
    0x92,   0x01,   0xff,   
    0x93,   0xc1,   0x1f,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_SHARPNESS_LEVEL2[]=   
{   
    0xFF,   0x00,   0xff,   
    0x92,   0x01,   0xff,   
    0x93,   0xc2,   0x1f,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_SHARPNESS_LEVEL3[]=   
{   
    0xFF,   0x00,   0xff,   
    0x92,   0x01,   0xff,   
    0x93,   0xc4,   0x1f,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_SHARPNESS_LEVEL4[]=   
{   
    0xFF,   0x00,   0xff,   
    0x92,   0x01,   0xff,   
    0x93,   0xc8,   0x1f,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_SHARPNESS_LEVEL5[]=   
{   
    0xFF,   0x00,   0xff,   
    0x92,   0x01,   0xff,   
    0x93,   0xd0,   0x1f,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_SHARPNESS_LEVEL6[]=   
{   
    0xFF,   0x00,   0xff,   
    0x92,   0x01,   0xff,   
    0x93,   0xdf,       0x1f,   
    0x00,   0x00,   0x00   
};   
   
const static u8 *OV_SETTING_SHARPNESS[]=   
{   
    OV2640_SHARPNESS_LEVEL0,   
    OV2640_SHARPNESS_LEVEL1,   
    OV2640_SHARPNESS_LEVEL2,   
    OV2640_SHARPNESS_LEVEL3,   
    OV2640_SHARPNESS_LEVEL4,   
    OV2640_SHARPNESS_LEVEL5,   
    OV2640_SHARPNESS_LEVEL6   
};   
   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
const static u8 OV2640_WHITEBALANCE_AUTO[]=   
{   
    0xFF,   0x00,   0xff,   
    0xb2,   0x1f,       0xff,   
    0xb4,   0x1f,       0xff,   
    0xb8,   0x1f,       0xff,   
    0xb5,   0x9b,   0xff,   
    0xa1,   0x91,   0xff,   
    0xa4,   0x62,   0xff,   
    0xb9,   0x6c,   0xff,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_WHITEBALANCE_SUNNY[]=   
{   
    0xFF,   0x00,   0xff,   
    0xb2,   0x00,   0xff,   
    0xb4,   0x1f,       0xff,   
    0xb8,   0x00,   0xff,   
    0xb5,   0x9b,   0xff,   
    0xa1,   0xc2,   0xff,   
    0xa4,   0x86,   0xff,   
    0xb9,   0x6c,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_WHITEBALANCE_CLOUDY[]=   
{   
    0xFF,   0x00,   0xff,   
    0xb2,   0x00,   0xff,   
    0xb4,   0x1f,       0xff,   
    0xb8,   0x00,   0xff,   
    0xb5,   0xb2,   0xff,   
    0xa1,   0xc2,   0xff,   
    0xa4,   0x86,   0xff,   
    0xb9,   0x6c,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_WHITEBALANCE_OFFICE[]=   
{   
    0xFF,   0x00,   0xff,   
    0xb2,   0x1f,       0xff,   
    0xb4,   0x00,   0xff,   
    0xb8,   0x00,   0xff,   
    0xb5,   0x9b,   0xff,   
    0xa1,   0xc2,   0xff,   
    0xa4,   0x86,   0xff,   
    0xb9,   0x6c,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_WHITEBALANCE_HOME[]=   
{   
    0xFF,   0x00,   0xff,   
    0xb2,   0x00,   0xff,   
    0xb4,   0x00,   0xff,   
    0xb8,   0x1f,       0xff,   
    0xb5,   0x9b,   0xff,   
    0xa1,   0xc2,   0xff,   
    0xa4,   0x86,   0xff,   
    0xb9,   0x6c,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_WHITEBALANCE_NIGHT[]=   
{   
    0xFF,   0x00,   0xff,   
    0xb2,   0x00,   0xff,   
    0xb4,   0x00,   0xff,   
    0xb8,   0x1f,       0xff,   
    0xb5,   0x9b,   0xff,   
    0xa1,   0xc2,   0xff,   
    0xa4,   0x86,   0xff,   
    0xb9,   0x44,   0xff,   
       
    0x7d,   0x12,   0xff,   
    0x79,   0x28,   0xff,   
    0x7a,   0x28,   0xff,   
       
    0x0f,       0x4b,   0xff,   
    0x03,   0x8f,       0xff,   
       
    0x00,   0x00,   0x00   
};   
   
const static u8 *OV_SETTING_WHITEBALANCE[]=   
{   
    OV2640_WHITEBALANCE_SUNNY,   
    OV2640_WHITEBALANCE_CLOUDY,   
    OV2640_WHITEBALANCE_OFFICE,   
    OV2640_WHITEBALANCE_HOME,   
    OV2640_WHITEBALANCE_NIGHT   
};   
   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
const static u8 OV2640_SPECIALEFFECT_DISABLE[]=   
{   
    0xFF,   0x00,   0xff,   
    0x86,   0x3d,   0xff,   
    0x7c,   0x00,   0xff,   
    0x7d,   0x00,   0xf8,   
    0x7c,   0x05,   0xff,   
    0x7d,   0x80,   0xff,   
    0x7d,   0x80,   0xff,      
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SPECIALEFFECT_NEGATIVE[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7c,   0x00,   0xff,   
    0x7d,   0x40,   0xf8,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SPECIALEFFECT_GRAY[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7c,   0x00,   0xff,   
    0x7d,   0x20,   0xf8,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SPECIALEFFECT_SEPIA[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7c,   0x00,   0xff,   
    0x7d,   0x18,   0xf8,   
    0x7c,   0x05,   0xff,   
    0x7d,   0x40,   0xff,   
    0x7d,   0xa0,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SPECIALEFFECT_BLUISH[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7c,   0x00,   0xff,   
    0x7d,   0x18,   0xf8,   
    0x7c,   0x05,   0xff,   
    0x7d,   0xe0,   0xff,   
    0x7d,   0x86,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SPECIALEFFECT_REDDISH[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7c,   0x00,   0xff,   
    0x7d,   0x18,   0xf8,   
    0x7c,   0x05,   0xff,   
    0x7d,   0x60,   0xff,   
    0x7d,   0xe0,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SPECIALEFFECT_GREENISH[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7c,   0x00,   0xff,   
    0x7d,   0x18,   0xf8,   
    0x7c,   0x05,   0xff,   
    0x7d,   0x53,   0xff,   
    0x7d,   0x4e,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_SPECIALEFFECT_ALLFIXED[]=   
{   
    0xFF,   0x00,   0xff,   
    0x7c,   0x00,   0xff,   
    0x7d,   0x98,   0xf8,   
    0x7c,   0x05,   0xff,   
    0x7d,   0x33,   0xff,   
    0x7d,   0xcc,   0xff,   
    0x7d,   0x99,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 *OV_SETTING_SPECIALEFFECT[]=   
{   
    OV2640_SPECIALEFFECT_NEGATIVE,   
    OV2640_SPECIALEFFECT_GRAY,   
    OV2640_SPECIALEFFECT_SEPIA,   
    OV2640_SPECIALEFFECT_BLUISH,   
    OV2640_SPECIALEFFECT_REDDISH,   
    OV2640_SPECIALEFFECT_GREENISH,     
    OV2640_SPECIALEFFECT_ALLFIXED      
};   
   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
const static u8 OV2640_AUTOEXPOSURE_LEVEL0[]=   
{   
    0xFF,   0x01,   0xff,   
    0x24,   0x20,   0xff,   
    0x25,   0x18,   0xff,   
    0x26,   0x60,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 OV2640_AUTOEXPOSURE_LEVEL1[]=   
{   
    0xFF,   0x01,   0xff,   
    0x24,   0x34,   0xff,   
    0x25,   0x1c,   0xff,   
    0x26,   0x70,   0xff,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_AUTOEXPOSURE_LEVEL2[]=   
{   
    0xFF,   0x01,   0xff,   
    0x24,   0x3e,   0xff,   
    0x25,   0x38,   0xff,   
    0x26,   0x81,   0xff,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_AUTOEXPOSURE_LEVEL3[]=   
{   
    0xFF,   0x01,   0xff,   
    0x24,   0x48,   0xff,   
    0x25,   0x40,   0xff,   
    0x26,   0x81,   0xff,   
    0x00,   0x00,   0x00   
};   
const static u8 OV2640_AUTOEXPOSURE_LEVEL4[]=   
{   
    0xFF,   0x01,   0xff,   
    0x24,   0x58,   0xff,   
    0x25,   0x50,   0xff,   
    0x26,   0x92,   0xff,   
    0x00,   0x00,   0x00   
};   
   
const static u8 *OV_SETTING_AUTOEXPOSURE[]=   
{   
    OV2640_AUTOEXPOSURE_LEVEL0,   
    OV2640_AUTOEXPOSURE_LEVEL1,   
    OV2640_AUTOEXPOSURE_LEVEL2,   
    OV2640_AUTOEXPOSURE_LEVEL3,   
    OV2640_AUTOEXPOSURE_LEVEL4   
};   
   
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
const static u8 OV2640_YUV422[]=    
{   
    0xFF,   0x00,   
    0x05,   0x00,   
    0xDA,   0x01,   
    0xD7,   0x01,   
    0x33,   0xa0,       //version 1.01   
    0xe1,   0x67,       //version 1.01   
    0x00,   0x00   
};   
   
const static u8 OV2640_YUV420[]=   
{   
    0xFF,   0x00,   
    0x05,   0x00,   
    0xDA,   0x01,   
    0xD7,   0x1D,   
    0x00,   0x00   
};   
   
const static u8 OV2640_RGB565[]=   
{   
    0xFF,   0x00,   
    0x05,   0x00,   
    0xDA,   0x08,   
    0x98,   0x00,   
    0x99,   0x00,   
    0x00,   0x00   
};   
   
const static u8 OV2640_RAW_SENSOR[]=   
{   
    0x05,   0x01,   
    0x00,   0x00   
};   
   
const static u8 OV2640_RAW_PROCESSED[]=   
{   
    0x05,   0x00,   
    0xDA,   0x04,   
    0x00,   0x00   
};   
   
const static u8 OV2640_JPEG[]=   
{   
    0xFF,   0x00,   
    0x05,   0x00,   
    0xDA,   0x10,   
    0xD7,   0x03,   
    0xDF,   0x00,   
    0x33,   0x80,   
    0x3C,   0x40,   
    0xe1,   0x77,   
    0x00,   0x00   
};   
   
const static u8 *OV_SETTING_FORMAT[]=   
{   
    OV2640_YUV422,   
    OV2640_YUV420,   
    OV2640_RGB565,   
    OV2640_JPEG,   
    NULL,   
    NULL,   
    NULL,   
    OV2640_RAW_SENSOR,   
    OV2640_RAW_PROCESSED,   
    NULL,   
    NULL   
};   
   
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
const static u8 OV_REGS_PREVIEW[] =    
{   
    0xFF,   0x01,   
    0x3D,   REG3DA_SVGA,    
    0x11,   0x01,   
    0x12,   0x40,   
    0x17,   0x11,   
    0x18,   0x43,   
    0x19,   0x00,   
    0x1A,   0x4B,   
    0x32,   0x09,   
    0xFF,   0x00,   
    0xC0,   0x64,   
    0xC1,   0x4B,   
    0x8C,   0x00,   
    0x86,   0x3D,   
    0x00, 0x00   
};   
   
const static u8 OV_REGS_STILLIMAGE[] =    
{   
    0xFF,   0x01,   
    0x12,   0x00,   
    0x3D,   REG3DA_UXGA,    
    0x11,   REG11A_UXGA,   
    0x17,   0x11,   
    0x18,   0x75,   
    0x19,   0x01,   
    0x1A,   0x97,   
    0x32,   0x36,   
    0x37,   0x42,   
    0x4f,   0xbb,    
    0x50,   0x9c,   
    0x6d,   0x80,   
    0x35,   0x88,   
    0x22,   0x0a,   
    0x6d,   0x80,   
       
    0xFF,   0x00,   
    0xC0,   0xC8,   
    0xC1,   0x96,   
    0x8C,   0x00,   
    0x86,   0x35,   
       
    0x00,   0x00   
};   
   
const static u8 OV_REGS_COLORMATRIX_YUV[] =   
{   
    0x96,   0x00,      
    0x97,   0x08,      
    0x97,   0x19,      
    0x97,   0x02,      
    0x97,   0x0c,      
    0x97,   0x24,      
    0x97,   0x30,      
    0x97,   0x28,      
    0x97,   0x26,      
    0x97,   0x02,      
    0x97,   0x98,      
    0x97,   0x80,      
    0x97,   0x00,      
    0x97,   0x00,          
    0x00,   0x00   
};   
   
const static u8 OV_REGS_COLORMATRIX_YCbCr[] =   
{   
    0x96,   0x00,      
    0x97,   0x08,      
    0x97,   0x19,      
    0x97,   0x02,      
    0x97,   0x0c,      
    0x97,   0x24,      
    0x97,   0x30,      
    0x97,   0x28,      
    0x97,   0x26,      
    0x97,   0x02,      
    0x97,   0x98,      
    0x97,   0x80,      
    0x97,   0x00,      
    0x97,   0x00,          
    0x00,   0x00   
};   
   
const static u8 OV_REGS_DEBUG[] =   
{   
    0xff,0x00,   
    0xe0,0x14,   
    0xe1,0x77,   
    0xe5,0x1f,   
    0xd7,0x03,   
    0xda,0x10,   
    0xd3,0x04,   
    0xeb,0x31,   
    0xdd,0x7f,   
    0xe0,0x00,   
       
    0x00,0x00   
};   
   
static int table_write(const u8* ptab)   
{   
    u8  address;   
    u8  value;   
    const u8  *pdata=ptab;   
   
    if ( NULL==pdata )   
        return -1;   
           
    while(1)   
    {   
        address=*pdata++;   
        value=*pdata++;   
        if ( (0==address) && (0==value) )   
        {   
            break;   
        }   
        ovcamerachip_reg8_write(address,value);   
    }   
   
    return 0;   
}   
   
static int table_mask_write(const u8* ptab)   
{   
    u8  address;   
    u8  value,orgval;   
    u8  mask;   
    const u8  *pdata=ptab;   
   
    if ( NULL==pdata )   
        return -1;   
           
    while(1)   
    {   
        address =*pdata++;   
        value = *pdata++;   
        mask = *pdata++;           
        if ( (0==address) && (0==value) &&(0==mask) )   
        {   
            break;   
        }   
           
        if(mask != 0xFF)   
        {   
            ovcamerachip_reg8_read( address, &orgval);   
            orgval &= (~mask);             
            value  &= mask;   
            value |=orgval;   
        }   
           
        ov2640print("adress = %8x  value = %8x \n", address,value);    
        ovcamerachip_reg8_write(address,value);   
    }   
   
    return 0;   
}   
   
static u32 getchipclock( void )   
{   
    u32 fclk;   
    u8  reg;   
       
    ovcamerachip_reg8_write(0xff,0x01);    
    ovcamerachip_reg8_read( 0x3D, ®);   
    reg = reg & 0x3F;   
    reg = 0x40 - reg;   
    fclk = g_ovcamerachip.mclock * reg /2;   
       
    ovcamerachip_reg8_read( 0x11, ®);   
    reg = reg & 0x3F;   
    reg = (reg +1)*2;   
    fclk = fclk / reg;   
       
    ov2640print("Current OV2640 chip clock is %8dHz\n", fclk);     
       
    return fclk;   
}   
   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//   
// Remove Banding   
//   
//   
// Set all the clock related function of OV2640 before call this function   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
static int setBandingFilter(int lightfrequency)   
{   
    long  val;   
    u32 maxlines;   
    u32 scale;   
    u8 reg;   
    u8 reg4A;   
       
    if( (lightfrequency !=50) && (lightfrequency !=60) )   
    {   
        return -1;   
    }   
       
    //internal clock   
    val = getchipclock();   
    val /= 1000;   //KHz   
       
    maxlines = g_ovcamerachip.stream ? 1248 : 672;   
    val *= maxlines;   
    val *= 5;   
       
    scale  = g_ovcamerachip.stream ? 3 : 1;   
    scale *=8*2;   
    scale *=lightfrequency;   
       
    val = val / scale;   
       
    val += 500;   
    val /=1000;   
       
    ovcamerachip_reg8_write(0xff,0x01);    
    ovcamerachip_reg8_read(0x0c,®);   
    ovcamerachip_reg8_read(0x4A,®4A);   
    reg4A &= 0x0F;   
       
    if(lightfrequency ==50)   
    {   
        reg |= 0x04;   
        ovcamerachip_reg8_write(0x0C,reg);     
               
        reg = val;   
        ovcamerachip_reg8_write(0x4F,reg);     
           
        reg = (val>>2) & 0xC0;   
    }   
    else   
    {   
        reg &= 0xFC;   
        ovcamerachip_reg8_write(0x0C,reg);     
               
        reg = val;   
        ovcamerachip_reg8_write(0x50,reg);     
           
        reg = (val >>4) & 0x30;      
    }   
       
    reg4A |=reg;   
    ovcamerachip_reg8_write(0x4A,reg);     
           
    return 0;   
}   
   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//   
//  Gain & Exposure   
//   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////   
static u32 gainreg2real16m ( u32 gainreg )   
{   
    u32 real;   
       
    ov2640print("gainreg =%d\n",gainreg);      
       
    real = gainreg & 0x000f;   
    real+=16;   
       
    if( gainreg & 0x10 )   
    {   
        real = real <<1;   
    }   
       
    if( gainreg & 0x20 )   
    {   
        real = real <<1;   
    }   
       
    if( gainreg & 0x40 )   
    {   
        real = real <<1;   
    }   
       
    if( gainreg & 0x80 )   
    {   
        real = real <<1;   
    }   
           
    ov2640print("gainreal =%d\n",real);    
    return real;   
}   
   
static int gainreal16m2reg(u32 gainreal)   
{   
    u32 gain;   
       
    gain = 0;   
       
    if( gainreal >31 )   
    {   
        gain |= 0x10;   
        gainreal = gainreal >>1;   
    }   
       
    if( gainreal >31 )   
    {   
        gain |= 0x20;   
        gainreal = gainreal >>1;   
    }   
       
    if( gainreal >31 )   
    {   
        gain |= 0x40;   
        gainreal = gainreal >>1;   
    }   
       
    if( gainreal >31 )   
    {   
        gain |= 0x80;   
        gainreal = gainreal >>1;   
    }   
       
    if( gainreal >16 )   
    {   
        gain |= (( gainreal -16 ) & 0x0f );   
    }   
       
    return gain;   
}   
   
static u32 getVideoExposureGain( void )   
{   
    u8  reg;   
    u32     exposure;   
    u32   gain;   
    u32   gainreal;   
       
    ov2640print("getVideoExposureGain( + )\n");    
       
    ovcamerachip_reg8_write(0xff,0x01);    
    ovcamerachip_reg8_read(0x45,®);   
    exposure = reg & 0x3f;   
    exposure <<= 8;   
    gain = reg & 0xc0;   
    gain <<=2;   
    ovcamerachip_reg8_read(0x10,®);   
       
    exposure +=reg;   
    exposure <<=2;   
       
    ovcamerachip_reg8_read(0x04,®);   
       
    exposure +=(reg & 0x03);   
   
    ovcamerachip_reg8_read(0x11,®);   
       
    exposure *= (reg+1);   
       
    ovcamerachip_reg8_read(0x00,®);   
    gain += reg;   
       
    gainreal = gainreg2real16m( gain );   
       
    ov2640print("getVideoExposureGain( - )\n");    
    return exposure*gainreal;   
}   
   
static int setStillimageExposure(u32 preexpgain, u8 reg11)   
{   
    u32 val32;   
    u32 wlines10ms;   
    u32 exposure,gain;   
    u8  reg8;   
    u64 expgain = preexpgain;   
       
    ov2640print("setStillimageExposure ( + )\n");      
   
    expgain *= 1248;   
    expgain *=   (0x40 - REG3DA_UXGA);   
       
    val32 = 672 * (reg11+1);   
    val32 *= ( 0x40 - REG3DA_SVGA ); //0x3D setting of preview   
    val32 *= 3;    
       
    expgain += (val32/2);   
    expgain /=val32;   
           
    expgain = expgain *2;   
       
    wlines10ms  =  (65*(0x40 - REG3DA_UXGA) * (g_ovcamerachip.mclock/1000) )/(reg11+1);   
    wlines10ms = (wlines10ms +50000)/100000;   
       
    if( expgain < (1248 *16) )   
    {   
        exposure = expgain/16;   
        if(exposure > wlines10ms)   
        {   
            exposure /= wlines10ms;   
            exposure *= wlines10ms;   
        }   
    }   
    else   
    {   
        exposure =1248;   
    }   
       
    gain = ( expgain * 2/exposure +1 ) / 2;   
    gain = gainreal16m2reg ( gain );   
       
    ovcamerachip_reg8_write(0xFF,0x01);   
    reg8 = gain & 0xFF;   
    ovcamerachip_reg8_write(0x00,reg8);   
           
    ovcamerachip_reg8_read(0x45,®8);   
    reg8 = reg8 & 0xC0;   
    reg8 += (exposure >>10) & 0x3F;   
    ovcamerachip_reg8_write(0x45,reg8);   
       
    reg8 = exposure >>2;   
    ovcamerachip_reg8_write(0x10,reg8);   
       
    ovcamerachip_reg8_read(0x04,®8);   
    reg8 = reg8 & 0xFC;   
    reg8 += (u8)(exposure & 0x03);   
    ovcamerachip_reg8_write(0x04,reg8);   
       
    ov2640print("setStillimageExposure ( - )\n");      
       
    return 0;   
}   
   
static void agcaecswitch(int onoff)   
{   
    u8 reg13;   
   
    ovcamerachip_reg8_write(0xff,0x01);   
    if(onoff ==0)   
    {   
        reg13 = 0xA0;   
    }   
    else   
    {   
        reg13 = 0xE5;   
    }   
       
    ovcamerachip_reg8_write(0x13,reg13);               
       
    return;   
}   
   
static int videoformat ( int format )   
{   
    ov2640print("videoformat( + )\n");     
    if (( format < 0 ) || ( OVCAMERACHIP_SFT_MAX <= format ))   
    {   
        return -1;   
    }   
       
    if ( NULL ==OV_SETTING_FORMAT[ format ] )   
    {   
        return -1;   
    }   
       
    table_write((u8*)OV_SETTING_FORMAT[format]);   
    g_ovcamerachip.format = format;   
       
    ov2640print("videoformat( - )\n");     
    return 0;   
}   
   
static int camerasize ( unsigned int width, unsigned int height )   
{   
    //u8 regval;   
    ov2640print("camerasize( + )\n");      
       
    if ( ( width & 0x0003 ) || (height & 0x0003))   
    {   
        return -1;   
    }   
    /*  
    ovcamerachip_reg8_write(0xff,00);     
    regval = width/4;  
    ovcamerachip_reg8_write(0x5A,regval);  
    regval = height/4;  
    ovcamerachip_reg8_write(0x5B,regval);  
    regval = (width>>10) & 0x03;  
    regval += (u8) (height >>8) & 0x04;  
    ovcamerachip_reg8_write(0x5C,regval);  
    */   
    g_ovcamerachip.width = width;   
    g_ovcamerachip.height = height;   
       
    ov2640print("camerasize( - )\n");      
    return 0;   
}   
   
void zoomscale(u8 zoom)   
{   
    unsigned int inwidth,inheight;   
    unsigned int xoff,yoff;   
    unsigned int cropwidth,cropheight;   
    u8 izoom,regval;   
    inwidth =800;   
    inheight =600;   
   
    ov2640print("zoomscale( + )\n");           
       
    if( zoom >5 )   
    {   
        izoom = zoom+5;    
    }   
    else   
    {   
        izoom =zoom *2;   
    }   
   
    xoff = 8 * izoom;   
    yoff = 6 * izoom;   
    cropwidth = inwidth - xoff * 2;   
    cropheight = inheight -yoff *2;   
       
    if(g_ovcamerachip.stream)   
    {   
        xoff*=2;   
        yoff*=2;   
        cropwidth*=2;   
        cropheight*=2;   
    }   
       
    regval = cropwidth / 4;   
    ovcamerachip_reg8_write ( 0x51, regval );   
    regval = cropheight / 4;   
    ovcamerachip_reg8_write ( 0x52, regval );   
    regval = xoff & 0xff;   
    ovcamerachip_reg8_write ( 0x53, regval );   
    regval = yoff & 0xff;   
    ovcamerachip_reg8_write ( 0x54, regval );   
    regval = (cropheight >>3 ) & 0x80;   
    regval += (cropwidth >>7 ) & 0x08;   
    regval += ( xoff >>8 ) & 0x07;   
    regval += ( yoff >>4 ) & 0x70;   
    ovcamerachip_reg8_write ( 0x55, regval );   
       
    regval = 0;   
    inwidth = g_ovcamerachip.width;   
    inheight = g_ovcamerachip.height;   
    while ( 2 * inheight < cropheight )   
    {   
        regval++;   
        cropheight /= 2;   
    }   
    regval <<= 3;   
    while ( 2* inwidth < cropwidth )   
    {   
        regval++;   
        cropwidth /=2;   
    }   
       
    if( regval >0 )   
    {   
        regval += 0x80;   
    }   
    ovcamerachip_reg8_write ( 0x50, regval );   
   
    u8 camclock = 0x04;   
       
    if (g_ovcamerachip.format != OVCAMERACHIP_SFT_JPEG)   
    {   
        if(regval & 0x80)   
        {   
            camclock = (  regval >>3 ) & 0x07;   
            regval = regval & 0x07;   
               
            if(regval > camclock)   
            {   
                camclock = regval;   
            }   
            camclock = 0x01 <<camclock;   
        }   
        if( camclock > 0x08 )   
        {   
            camclock = 0x08;   
        }      
    }   
   
    ovcamerachip_reg8_write ( 0xd3, camclock );   
   
    ov2640print("zoomscale( - )\n");       
           
    return;   
}   
   
//still image    
static void stillimage( void ) //version 1.01    
{   
    u8 reg,frames;   
    u32 expgain;   
    u8 pels=3;   
    ov2640print("stillimage( + )\n");      
       
/*  agcaecswitch(0);   
    expgain = getVideoExposureGain();  
    g_ovcamerachip.exposure = expgain;  
          
    table_write( OV_REGS_STILLIMAGE );  
      
    zoomscale( g_ovcamerachip.zoom );  
      
    ovcamerachip_reg8_write(0xc3,0xed);   
    ovcamerachip_reg8_write(0x7f,0x00);   
      
    setStillimageExposure(expgain, REG11A_UXGA);  
  
    ovcamerachip_reg8_write(0xff,0x00);  
    ovcamerachip_reg8_write(0xeb,0x30);   
    expgain = 0;  
    frames = 0;   
    ovcamerachip_reg8_write(0xdd,0x73);   
    ovcamerachip_reg8_write(0xe0,0x00);       
    ovcamerachip_reg8_write(0xe9,0x3F);   
    do  
    {  
        ovcamerachip_reg8_read(0xe9,®);  
        if(reg & 0x04)  
        {  
            ovcamerachip_reg8_write(0xe9,0x3F);   
            frames++;     
        }  
        mdelay(1);  
        expgain++;  
    } while ((frames < 3)&&~expgain);  
      
    ovcamerachip_reg8_write(0xdd,0x7f);   
    ovcamerachip_reg8_write(0xeb,0x30);   
      
    mdelay(10);  
    */   
    ov2640print("setting width is %d\n",g_ovcamerachip.width);   
    switch(g_ovcamerachip.width)   
        {   
        case  QCIF:pels=0;   
                          ov2640print("This is QCIF:176*144 MODULE\n");   
                          break;   
        case QVGA:pels=1;   
                           ov2640print("This is QVGA:320*240 MODULE\n");   
                           break;   
        case     CIF:pels=2;   
                           ov2640print("This is CIF:325*288 MODULE\n");   
                          break;   
        case    VGA:pels=3;   
                           ov2640print("This is VGA:640*480 MODULE\n");   
                           break;   
        case  SVGA:pels=4;   
                           ov2640print("This is SVGA:800*600 MODULE\n");   
                           break;   
        case    XGA:pels=5;   
                           ov2640print("This is XGA:1024*768 MODULE\n");   
                           break;   
        case  SXGA:pels=6;   
                           ov2640print("This is SXGA:1280*1024 MODULE\n");   
                           break;   
        default:ov2640print("this camera does not support this size\n");   
                     return -1;   
            break;   
        }   
    table_write(OV2640_SETTING_PELS[pels]);   
    ov2640print("stillimage( - )\n");      
}   
   
static void preview_start( void )    
{   
    u8 reg;   
    u8 pels=3;   
    ov2640print("preview_start( + )\n");       
    //agcaecswitch(1);   
    //ovcamerachip_reg8_write(0xe0,0x14);      
    ov2640print("setting width is %d\n",g_ovcamerachip.width);   
    switch(g_ovcamerachip.width)   
        {   
        case  QCIF:pels=0;   
                          ov2640print("This is QCIF:176*144 MODULE\n");   
                          break;   
        case QVGA:pels=1;   
                           ov2640print("This is QVGA:320*240 MODULE\n");   
                           break;   
        case     CIF:pels=2;   
                           ov2640print("This is CIF:325*288 MODULE\n");   
                          break;   
        case    VGA:pels=3;   
                           ov2640print("This is VGA:640*480 MODULE\n");   
                           break;   
        case  SVGA:pels=4;   
                           ov2640print("This is SVGA:800*600 MODULE\n");   
                           break;   
        case    XGA:pels=5;   
                           ov2640print("This is XGA:1024*768 MODULE\n");   
                           break;   
        case  SXGA:pels=6;   
                           ov2640print("This is SXGA:1280*1024 MODULE\n");   
                           break;   
        default:ov2640print("this camera does not support this size\n");   
                     return -1;   
            break;   
        }   
    table_write(OV2640_SETTING_PELS[pels]);   
    //table_write(OV_REGS_PREVIEW);   
       
    //zoomscale( g_ovcamerachip.zoom );   
       
/*  reg = g_ovcamerachip.framerate;  
    ovcamerachip_reg8_write(0xff,0x01);  
    ovcamerachip_reg8_write(0x11,reg);  
*/     
/*  setBandingFilter(g_ovcamerachip.lightfrequency);  
  
    ovcamerachip_reg8_write(0xff,0x00);   
    ovcamerachip_reg8_write(0xdd,0x7f);   
    mdelay(1);  
    ovcamerachip_reg8_write(0xe0,0x00);   
    mdelay(1);  
    ovcamerachip_reg8_write(0xeb,0x31);*/      
       
    ov2640print("preview_start( - )\n");       
}    
   
static void stream_start( void )   
{   
    /*  
    .  
    .  
    .  
    */   
    mdelay(1);     
}   
   
   
static void stream_stop( void )   
{   
    u8 reg;   
    u32 i=0;   
           
    ovcamerachip_reg8_write(0xff,0x00);   
    ovcamerachip_reg8_read(0xeb,®);   
    if( (reg & 0x10) == 0x00)    
    {   
        return;   
    }   
    ovcamerachip_reg8_write(0xeb,0x20);   
    ovcamerachip_reg8_write(0xe9,0x02);   
    do   
    {   
        ovcamerachip_reg8_read(0xe9,®);   
        if ( ( reg & 0x02 ) ==0 )    
        {   
            break;   
        }   
        i++;   
    }while(i < 100000);   
           
    mdelay(1);     
}   
   
int camerachip_ip_init( void )   
{   
        //Ê¹ÄÜTABLE13   
    ovcamerachip_reg8_write(0xff,0x01);   
    //¸´Î»½øÈëUXGAÄ£Ê½ ²»ÔÊÐíËõ·ÅÑÕÉ«Ìõ²âÊÔÄ£Ê½¹Ø±Õ   
    ovcamerachip_reg8_write(0x12,0x80);   
    //ÑÓÊ±1Ãë   
    mdelay(1);   
    //Ð´ÈëUXGAµÄÅäÖÃ   
    table_write(OV_REGS_INITIALIZE);   
       
    /*´ËÎªÒÔÇ°µÄ´úÂë*/   
    //****************************   
    g_ovcamerachip.width = 176;   
    g_ovcamerachip.height = 144;   
    g_ovcamerachip.framerate = 0x01;   
    g_ovcamerachip.exposure = 20000;       
    g_ovcamerachip.lightfrequency = 50;    
    g_ovcamerachip.format = OVCAMERACHIP_SFT_YUV422 ;   
    g_ovcamerachip.saturation = -1;   
    g_ovcamerachip.brightness = -1;   
    g_ovcamerachip.sharpness = -1;   
    g_ovcamerachip.contrast = -1;   
    g_ovcamerachip.whitebalance = -1;   
    g_ovcamerachip.specialeffect = -1;   
       
    g_ovcamerachip.zoom = 0;   
    g_ovcamerachip.flip =0;   
    g_ovcamerachip.mirror =0;   
      //  ***********************************/   
/*  mdelay(1);  
    ovcamerachip_reg8_write(0xff,0x00);  
    ovcamerachip_reg8_write(0xdd,0x73);  
    ovcamerachip_reg8_write(0xe0,0x14);  
    */   
    return 0;      
}   
   
int camerachip_ip_set_format(unsigned int width, unsigned int height, int format)   
{   
    int ret;   
       
    ov2640print("camerachip_ip_set_format( + )\n");    
       
    if ( ( width > OV2640_MAX_WIDTH ) || ( height > OV2640_MAX_HEIGHT ) )   
    {   
        return -1;   
    }   
    ret = camerasize( width, height );   
       
    if(ret)   
    {   
        return -1;   
    }   
       
    ret = videoformat ( format );   
    if(ret)   
    {   
        return ret;   
    }   
       
    ov2640print("camerachip_ip_set_format( - )\n");    
    return 0;   
}   
   
int camerachip_ip_zoom(u8 zoom)   
{   
    if( zoom>OV2640_MAXLEVEL_ZOOM )   
    {   
        return -1;   
    }   
       
    ovcamerachip_reg8_write(0xeb,0x20);    
       
    zoomscale( zoom );   
       
    ovcamerachip_reg8_write(0xeb,0x31);    
       
    g_ovcamerachip.zoom = zoom;   
       
    return 0;   
}   
   
int camerachip_ip_flip(int flip)   
{   
    int ret;   
    u8 reg04;   
    ret = ovcamerachip_reg8_write(0xff,0x01);    
    ovcamerachip_reg8_read( 0x04, ®04);   
    if( flip == 0 )    
    {   
        reg04 &= 0xAF;    
    }   
    else    
    {   
        reg04 |= 0x50;   
    }   
       
    ovcamerachip_reg8_write(0x04,reg04);   
       
    return 0;   
}   
   
int camerachip_ip_mirror(int mirror)   
{   
    int ret;   
    u8 reg04;   
    ret = ovcamerachip_reg8_write(0xff,0x01);    
    ovcamerachip_reg8_read( 0x04, ®04);   
    if( mirror == 0 )    
    {   
        reg04 &= 0x7F;    
    }   
    else    
    {   
        reg04 |= 0x80;   
    }   
       
    ovcamerachip_reg8_write(0x04,reg04);   
       
    return 0;   
}   
   
int camerachip_ip_lightfrequency(int lightfrequency)   
{   
    if( ( lightfrequency!=50 ) && ( lightfrequency !=60 ) )   
    {   
        return -1;   
    }   
       
    setBandingFilter    (lightfrequency);   
       
    g_ovcamerachip.lightfrequency = lightfrequency;   
       
    return 0;   
}   
   
int camerachip_ip_framerate(int framerate)   
{   
    u8  reg;   
    int  lightfrequency;   
    if(( framerate < 0 ) || ( framerate >  OV2640_MAXLEVEL_FRAMERATE ))   
    {   
        return -1;   
    }   
       
    reg = framerate;       
    ovcamerachip_reg8_write(0xff,0x01);   
    ovcamerachip_reg8_write(0x11,reg);   
    g_ovcamerachip.framerate = framerate;   
       
    lightfrequency = g_ovcamerachip.lightfrequency;   
    setBandingFilter    ( lightfrequency );   
       
    return 0;   
}   
   
int camerachip_ip_specialeffect(  int specialeffect )   
{   
    if( specialeffect > OV2640_MAXLEVEL_SPECIALEFFECT )   
    {   
        return -1;   
    }   
   
    if( specialeffect < 0 )   
    {   
        table_mask_write(OV2640_SPECIALEFFECT_DISABLE);            
    }   
    else   
    {      
        table_mask_write(OV_SETTING_SPECIALEFFECT[specialeffect]);     
    }   
   
    g_ovcamerachip.specialeffect = specialeffect;   
       
    return 0;   
}   
   
int camerachip_ip_brightness(  int brightness )   
{   
    if( brightness > OV2640_MAXLEVEL_BRIGHTNESS )   
    {   
        return -1;   
    }   
       
    if( brightness <0 )   
    {   
        table_mask_write(OV2640_BRIGHTNESS_DISABLE);           
    }   
    else   
    {      
        table_mask_write(OV_SETTING_BRIGHTNESS[brightness]);       
        table_mask_write(OV2640_BRIGHTNESS_ENABLE);    
    }   
   
    g_ovcamerachip.brightness = brightness;   
   
    return 0;   
}   
   
int camerachip_ip_sharpness(  int sharpness )   
{   
    if ( sharpness > OV2640_MAXLEVEL_SHARPNESS)   
    {   
        return -1;   
    }   
       
    if( sharpness <0 )   
    {   
        table_mask_write(OV2640_SHARPNESS_AUTO);       
    }   
    else   
    {   
        table_mask_write(OV2640_SHARPNESS_MANUAL);     
        table_mask_write(OV_SETTING_SHARPNESS[sharpness]);   
    }   
   
    g_ovcamerachip.sharpness = sharpness;   
   
    return 0;   
}   
   
int camerachip_ip_hue(  int hue )   
{   
    if( hue > OV2640_MAXLEVEL_HUE)   
    {   
        return -1;   
    }   
       
    if( hue <0 )   
    {   
        table_mask_write(OV2640_HUE_DISABLE);   
    }   
    else   
    {   
        table_mask_write(OV_SETTING_HUE[hue]);   
        table_mask_write(OV2640_HUE_ENABLE);   
    }   
       
    g_ovcamerachip.hue = hue;   
   
    return 0;   
}   
   
int camerachip_ip_saturation(  int saturation )   
{   
    if( saturation > OV2640_MAXLEVEL_SATURATION)   
    {   
        return -1;   
    }   
       
    if( saturation <0 )   
    {   
        table_mask_write(OV2640_SATURATION_DISABLE);   
    }   
    else   
    {   
        table_mask_write(OV_SETTING_SATURATION[saturation]);   
        table_mask_write(OV2640_SATURATION_ENABLE);   
    }   
   
    g_ovcamerachip.saturation = saturation;   
   
    return 0;   
}   
   
int camerachip_ip_contrast(  int contrast )   
{   
    if( contrast > OV2640_MAXLEVEL_CONTRAST)   
    {   
        return -1;   
    }   
       
    if (contrast < 0 )   
    {   
        table_mask_write(OV2640_CONTRAST_DISABLE);   
    }   
    else   
    {   
        table_mask_write(OV_SETTING_CONTRAST[contrast]);   
        table_mask_write(OV2640_CONTRAST_ENABLE);   
    }   
       
    g_ovcamerachip.contrast = contrast;   
   
    return 0;   
}   
   
int camerachip_ip_whitebalance( int whitebalance  )   
{   
    if( whitebalance >  OV2640_MAXLEVEL_WHITEBALANCE )   
    {   
        return -1;   
    }   
       
    if( whitebalance < 0 )   
    {   
        table_mask_write(OV2640_WHITEBALANCE_AUTO);    
    }   
    else   
    {   
        table_mask_write(OV_SETTING_WHITEBALANCE[whitebalance]);       
    }   
       
    g_ovcamerachip.whitebalance = whitebalance;   
       
    return 0;   
}   
   
   
int camerachip_ip_gamma( int gamma  )   
{   
   
    return 0;   
}   
   
int camerachip_ip_stream_on()   
{   
    if(g_ovcamerachip.stream)   
    {   
        stillimage();      
    }   
    else   
    {   
        preview_start();   
    }   
       
    return 0;      
}   
   
int camerachip_ip_stream_off( void )   
{   
    //stream_stop();           
    return 0;   
}   
   
int camerachip_ip_debug( void )   
{   
    //table_write(OV_REGS_DEBUG);   
    return 0;   
}   