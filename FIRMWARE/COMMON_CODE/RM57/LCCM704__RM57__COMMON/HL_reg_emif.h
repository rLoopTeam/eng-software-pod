/** @file HL_reg_emif.h
*   @brief EMIF Register Layer Header File
*   @date 08-Feb-2017
*   @version 04.06.01
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the EMIF driver.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef __REG_EMIF_H__
#define __REG_EMIF_H__

//#include "HL_sys_common.h"
#include <localdef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Emif Register Frame Definition */
/** @struct emifBASE_t
*   @brief emifBASE Register Definition
*
*   This structure is used to access the EMIF module registers.
*/
typedef volatile struct emifBase
{
    Luint32 MIDR;          /**< 0x0000 Module ID Register */
    Luint32 AWCC;          /**< 0x0004 Asynchronous wait cycle register*/
    Luint32 SDCR;          /**< 0x0008 SDRAM configuration register */
    Luint32 SDRCR ;        /**< 0x000C Set Interrupt Enable Register */
    Luint32 CE2CFG;        /**< 0x0010 Asynchronous 1 Configuration Register */
    Luint32 CE3CFG;        /**< 0x0014 Asynchronous 2 Configuration Register */
    Luint32 CE4CFG;        /**< 0x0018 Asynchronous 3 Configuration Register */
    Luint32 CE5CFG;        /**< 0x001C Asynchronous 4 Configuration Register */
    Luint32 SDTIMR;        /**< 0x0020 SDRAM Timing Register */
    Luint32 dummy1[6];     /** reserved **/
    Luint32 SDSRETR;       /**< 0x003c SDRAM Self Refresh Exit Timing Register */
    Luint32 INTRAW;        /**< 0x0040 0x0020 Interrupt Vector Offset*/
    Luint32 INTMSK;        /**< 0x0044 EMIF Interrupt Mask Register */
    Luint32 INTMSKSET;     /**< 48 EMIF Interrupt Mask Set Register */
    Luint32 INTMSKCLR;     /**< 0x004c EMIF Interrupt Mask Register */
    Luint32 dummy2[6];     /** reserved **/
    Luint32 PMCR;          /**< 0x0068 Page Mode Control Register*/

} emifBASE_t;

#define emifREG ((emifBASE_t *)0xFCFFE800U)

/* USER CODE BEGIN (1) */
/* USER CODE END */

#ifdef __cplusplus
}
#endif

#endif
