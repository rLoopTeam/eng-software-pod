/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 © Copyright 2009-2012 Texas Instruments Incorporated.  All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *      Project:  Hercules™ ARM® Safety MCUs - F021 Flash API 
 *      Version:  v2.00.01 Build(000824)                                                                                
 *   Build Date:  2013-07-18                                                                                            
 *
 *         File:  FapiFunctions.h                                                                                       
 *
 *  Description:  All the FAPI function extern definitions.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  John R Hall
 *---------------------------------------------------------------------------------------------------------------------
 *
 *********************************************************************************************************************/


#ifndef RM4_FLASH_FAPI_FUNCTIONS_H_
#define RM4_FLASH_FAPI_FUNCTIONS_H_

#ifndef WIN32

#ifdef __cplusplus
extern "C" {
#endif

/* Flash C API functions*/

/* Flash State Machine commands */
extern Fapi_StatusType Fapi_enableMainBankSectors(Luint16 u16SectorsEnables);

extern Fapi_StatusType Fapi_enableEepromBankSectors(Luint32 u32SectorsEnables_31_0, Luint32 u32SectorsEnables_63_32);

extern Fapi_StatusType Fapi_enableFsmDoneEvent(void);

extern Fapi_StatusType Fapi_disableFsmDoneEvent(void);

extern Fapi_StatusType Fapi_initializeFlashBanks(Luint32 u32HclkFrequency);

extern Fapi_StatusType Fapi_setActiveFlashBank(Fapi_FlashBankType oNewFlashBank);

extern Fapi_StatusType Fapi_enableBanksForOtpWrite(Luint8 u8Banks);

extern Fapi_StatusType Fapi_disableBanksForOtpWrite(void);

/* Functions only available on devices with L2FMC Flash controllers */
#if defined(_L2FMC) 

extern Fapi_StatusType Fapi_enableAutoEccCalculation(void);
extern Fapi_StatusType Fapi_disableAutoEccCalculation(void);

#endif  /* defined(_L2FMC) */

extern void Fapi_flushPipeline(void);

extern Luint32* Fapi_remapEccAddress(Luint32 u32EccAddress);

extern Luint32 Fapi_remapMainAddress(Luint32 u32MainAddress);

extern boolean_t Fapi_isAddressEcc(Luint32 u32Address);

/* Async Commands */
extern Fapi_StatusType Fapi_issueAsyncCommandWithAddress(
                                                         Fapi_FlashStateCommandsType oCommand,
                                                         Luint32* pu32StartAddress
                                                        );

extern Fapi_StatusType Fapi_issueAsyncCommand(Fapi_FlashStateCommandsType oCommand);

/* Info Commands */
extern Fapi_LibraryInfoType Fapi_getLibraryInfo(void);
extern Fapi_DeviceInfoType Fapi_getDeviceInfo(void);
extern Fapi_StatusType Fapi_getBankSectors(
                                           Fapi_FlashBankType oBank, 
                                           Fapi_FlashBankSectorsType* poFlashBankSectors 
                                          );

/* Read commands */
extern Fapi_StatusType Fapi_doBlankCheck(
                                         Luint32* pu32StartAddress,
                                         Luint32 u32Length,
                                         Fapi_FlashStatusWordType* poFlashStatusWord
                                        );

extern Fapi_StatusType Fapi_doMarginRead(
                                         Luint32* pu32StartAddress,
                                         Luint32* pu32ReadBuffer,
                                         Luint32 u32Length,
                                         Fapi_FlashReadMarginModeType oReadMode
                                        );

extern Fapi_StatusType Fapi_doVerify(
                                     Luint32* pu32StartAddress,
                                     Luint32 u32Length,
                                     Luint32* pu32CheckValueBuffer,
                                     Fapi_FlashStatusWordType* poFlashStatusWord
                                    );

extern Luint32 Fapi_calculatePsa(
                                Luint32* pu32StartAddress,
                                Luint32 u32Length,
                                Luint32 u32PsaSeed,
                                Fapi_FlashReadMarginModeType oReadMode
                               );

extern Fapi_StatusType Fapi_doPsaVerify(
                                        Luint32* pu32StartAddress,
                                        Luint32 u32Length,
                                        Luint32 u32PsaValue,
                                        Fapi_FlashStatusWordType* poFlashStatusWord
                                       );

extern Fapi_StatusType Fapi_doBlankCheckByByte(
                                               Luint8* pu8StartAddress,
                                               Luint32 u32Length,
                                               Fapi_FlashStatusWordType* poFlashStatusWord
                                              );

extern Fapi_StatusType Fapi_doMarginReadByByte(
                                               Luint8* pu8StartAddress,
                                               Luint8* pu8ReadBuffer,
                                               Luint32 u32Length,
                                               Fapi_FlashReadMarginModeType oReadMode
                                              );

extern Fapi_StatusType Fapi_doVerifyByByte(
                                           Luint8* pu8StartAddress,
                                           Luint32 u32Length,
                                           Luint8* pu8CheckValueBuffer,
                                           Fapi_FlashStatusWordType* poFlashStatusWord
                                          );

/* Programming Commands */
extern Fapi_StatusType Fapi_issueProgrammingCommand(
                                                    Luint32* pu32StartAddress,
                                                    Luint8*  pu8DataBuffer,
                                                    Luint8   u8DataBufferSizeInBytes,
                                                    Luint8*  pu8EccBuffer,
                                                    Luint8   u8EccBufferSizeInBytes,
                                                    Fapi_FlashProgrammingCommandsType oMode
                                                   );

extern Fapi_StatusType Fapi_issueProgrammingCommandForEccAddresses(
                                                                   Luint32* pu32StartAddress,
                                                                   Luint8*  pu8EccBuffer,
                                                                   Luint8   u8EccBufferSizeInBytes
                                                                  );

/* Utility Commands */
extern Fapi_StatusType Fapi_waitDelay(volatile Luint32 u32WaitDelay);

extern Luint32 Fapi_calculateFletcherChecksum(
                                             Luint32 u32Address,
                                             Luint32 u32Length
                                            );

extern Luint8 Fapi_calculateEcc(Luint32 u32Address, Luint64 u64Data );

/* User Defined Functions */
extern Fapi_StatusType Fapi_serviceWatchdogTimer(void);

#ifdef __cplusplus
}
#endif

#endif //WIN32

#endif /*FAPI_FUNCTIONS_H_*/

/**********************************************************************************************************************
 *  END OF FILE: FapiFunctions.h
 *********************************************************************************************************************/
