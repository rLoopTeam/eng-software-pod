/** @file HL_emif.h
*   @brief emif Driver Definition File
*   @date 08-Feb-2017
*   @version 04.06.01
*   
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


#ifndef _EMIF_H_
#define _EMIF_H_

#include "HL_reg_emif.h"
#include <localdef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN (0) */
/* USER CODE END */

/** @enum emif_pins
*   @brief Alias for emif pins
*
*/
enum emif_pins
{
    emif_wait_pin0 = 0U,
    emif_wait_pin1 = 1U
};


/** @enum emif_size
*   @brief Alias for emif page size
*
*/
enum emif_size
{
    elements_256 = 0U,
    elements_512 = 1U,
    elements_1024 = 2U,
    elements_2048 = 3U
};

/** @enum emif_port
*   @brief Alias for emif port
*
*/
enum emif_port
{
    emif_8_bit_port = 0U,
    emif_16_bit_port = 1U
};


/** @enum emif_pagesize
*   @brief Alias for emif pagesize
*
*/
enum emif_pagesize
{
    emif_4_words = 0U,
    emif_8_words = 1U
};

/** @enum emif_wait_polarity
*   @brief Alias for emif wait polarity
*
*/
enum emif_wait_polarity
{
    emif_pin_low = 0U,
    emif_pin_high = 1U
};


#define PTR ((volatile Luint32 *)(0x80000000U))


/* Configuration registers */
typedef struct emif_config_reg
{
    Luint32 CONFIG_AWCC;
    Luint32 CONFIG_SDCR;
    Luint32 CONFIG_SDRCR ;
    Luint32 CONFIG_CE2CFG;
    Luint32 CONFIG_CE3CFG;
    Luint32 CONFIG_CE4CFG;
    Luint32 CONFIG_CE5CFG;
    Luint32 CONFIG_SDTIMR;
    Luint32 CONFIG_SDSRETR;
    Luint32 CONFIG_INTMSK;
    Luint32 CONFIG_PMCR;
} emif_config_reg_t;


/* Configuration registers initial value for EMIF*/
#define EMIF_AWCC_CONFIGVALUE    ((Luint32)((Luint32)emif_pin_high << 29U) \
                                | (Luint32)((Luint32)emif_pin_low << 28U) \
                                | (Luint32)((Luint32)emif_wait_pin0 << 16U) \
                                | (Luint32)((Luint32)emif_wait_pin0 << 18U) \
                                | (Luint32)((Luint32)emif_wait_pin0 << 20U) \
                                | (Luint32)((Luint32)0U)          \
								| (Luint32)0xC0000000U)
								
#define EMIF_SDCR_CONFIGVALUE    ((Luint32)((Luint32)1U << 31U) \
                                | (Luint32)((Luint32)1U << 14U) \
                                | (Luint32)((Luint32)0U << 9U) \
								| (Luint32)((Luint32)0U << 4U) \
                                | (Luint32)((Luint32)elements_256))
								
#define EMIF_SDRCR_CONFIGVALUE   0U

#define EMIF_CE2CFG_CONFIGVALUE  ((Luint32)((Luint32)0U << 31U) \
                                | (Luint32)((Luint32)0U << 30U) \
                                | (Luint32)((Luint32)15U << 26U) \
                                | (Luint32)((Luint32)63U << 20U) \
                                | (Luint32)((Luint32)7U << 17U) \
                                | (Luint32)((Luint32)15U << 13U) \
                                | (Luint32)((Luint32)63U << 7U) \
                                | (Luint32)((Luint32)7U << 4U) \
                                | (Luint32)((Luint32)0U << 2U) \
                                | (Luint32)((Luint32)emif_8_bit_port))

#define EMIF_CE3CFG_CONFIGVALUE  ((Luint32)((Luint32)0U << 31U) \
                                | (Luint32)((Luint32)0U << 30U) \
                                | (Luint32)((Luint32)15U << 26U) \
                                | (Luint32)((Luint32)63U << 20U) \
                                | (Luint32)((Luint32)7U << 17U) \
                                | (Luint32)((Luint32)15U << 13U) \
                                | (Luint32)((Luint32)63U << 7U) \
                                | (Luint32)((Luint32)7U << 4U) \
                                | (Luint32)((Luint32)0U << 2U) \
                                | (Luint32)((Luint32)emif_8_bit_port))
								
#define EMIF_CE4CFG_CONFIGVALUE  ((Luint32)((Luint32)0U << 31U) \
                                | (Luint32)((Luint32)0U << 30U) \
                                | (Luint32)((Luint32)15U << 26U) \
                                | (Luint32)((Luint32)63U << 20U) \
                                | (Luint32)((Luint32)7U << 17U) \
                                | (Luint32)((Luint32)15U << 13U) \
                                | (Luint32)((Luint32)63U << 7U) \
                                | (Luint32)((Luint32)7U << 4U) \
                                | (Luint32)((Luint32)0U << 2U) \
                                | (Luint32)((Luint32)emif_8_bit_port))
								
#define EMIF_CE5CFG_CONFIGVALUE   0x3FFFFFFDU
								
#define EMIF_SDTIMR_CONFIGVALUE  ((Luint32)((Luint32)0U << 27U) \
                                | (Luint32)((Luint32)0U << 24U) \
                                | (Luint32)((Luint32)0U << 20U) \
                                | (Luint32)((Luint32)0U << 16U) \
                                | (Luint32)((Luint32)0U << 12U) \
                                | (Luint32)((Luint32)0U << 8U) \
                                | (Luint32)((Luint32)0U << 4U) \
								| 0x00000000U)

#define EMIF_SDSRETR_CONFIGVALUE  0U
#define EMIF_INTMSK_CONFIGVALUE   0x00000000U
#define EMIF_PMCR_CONFIGVALUE     (0xFC000000U \
                                | (Luint32)((Luint32)0U << 2U) \
                                | (Luint32)((Luint32)emif_4_words << 1U) \
                                | (Luint32)((Luint32)0U) \
                                | (Luint32)((Luint32)0U << 10U) \
                                | (Luint32)((Luint32)emif_4_words << 9U) \
                                | (Luint32)((Luint32)0U << 8U) \
                                | (Luint32)((Luint32)0U << 18U) \
                                | (Luint32)((Luint32)emif_4_words << 17U) \
                                | (Luint32)((Luint32)0U << 16U))


/** 
 *  @defgroup EMIF EMIF
 *  @brief External Memory Interface.
 *  
 *  This EMIF memory controller is compliant with the JESD21-C SDR SDRAM memories utilizing a 16-bit
 *  data bus. The purpose of this EMIF is to provide a means for the CPU to connect to a variety of external
 *  devices including:
 *  - Single data rate (SDR) SDRAM
 *  - Asynchronous devices including NOR Flash and SRAM
 *  The most common use for the EMIF is to interface with both a flash device and an SDRAM device
 *  simultaneously. contains an example of operating the EMIF in this configuration.
 *
 *	Related Files
 *   - HL_reg_emif.h
 *   - HL_emif.h
 *   - HL_emif.c
 *  @addtogroup EMIF
 *  @{
 */
/* EMIF Interface Functions */

void emif_SDRAMInit(void);
void emif_SDRAM_StartupInit(void);
void emif_ASYNC1Init(void);
void emif_ASYNC2Init(void);
void emif_ASYNC3Init(void);
//void emifGetConfigValue(emif_config_reg_t *config_reg, config_value_type_t type);

/* USER CODE BEGIN (1) */
/* USER CODE END */

/**@}*/
#ifdef __cplusplus
}
#endif /*extern "C" */

#endif /*EMIF_H_*/
