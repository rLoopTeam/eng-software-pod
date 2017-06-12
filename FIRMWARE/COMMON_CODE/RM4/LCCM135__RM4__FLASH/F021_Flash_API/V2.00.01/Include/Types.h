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
 *         File:  Types.h                                                                                               
 *
 *  Description:  Types used by the F021 API.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  John R Hall
 *---------------------------------------------------------------------------------------------------------------------
 *
 *********************************************************************************************************************/


#ifndef _RM4_FLASH_TYPES_H_
#define _RM4_FLASH_TYPES_H_


#include <RM4/LCCM105__RM4__BASIC_TYPES/basic_types.h>

#ifndef WIN32

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
/*LDRA_NOANALYSIS*/
//#include <stdint.h>
//#include <stddef.h>
/*LDRA_ANALYSIS*/

#if defined(__TI_COMPILER_VERSION__)   /* TI CCS Compiler */
#include <RM4/LCCM135__RM4__FLASH/F021_Flash_API/V2.00.01/Include/CGT.CCS.h>
#elif defined(__GNUC__)                /* gcc Compiler */
#include "CGT.gcc.h"
#else
#error "A valid code generation compiler type was not determined!"
#endif

#if !defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN)
#error "Target Endianess is not defined"
#endif


/*****************************************************************************/
/* GLOBAL DEFINITIONS                                                        */
/*****************************************************************************/
#if !defined(HIGH_BYTE_FIRST)
#define HIGH_BYTE_FIRST     0U
#endif

#if !defined(LOW_BYTE_FIRST)
#define LOW_BYTE_FIRST      1U
#endif

//#if !defined(CPU_BYTE_ORDER)
//	#if defined(_LITTLE_ENDIAN)
//	   #define CPU_BYTE_ORDER    (LOW_BYTE_FIRST)
//	#else
//	#error
//	   #define CPU_BYTE_ORDER    (HIGH_BYTE_FIRST)
//	#endif
//#endif

#if !defined(false)
#define false	0U
#endif
#if !defined(true)
#define true	1U
#endif

/*****************************************************************************/
/* TYPE DEFINITIONS                                                          */
/*****************************************************************************/
typedef unsigned char boolean_t;

/*!
    \brief This is used to indicate which Cpu is being used.
*/
typedef enum
{
   Fapi_MasterCpu,
   Fapi_SlaveCpu0
}  ATTRIBUTE_PACKED Fapi_CpuSelectorType;

/*!
    \brief This is used to indicate what type of Cpu is being used.
*/
typedef enum
{
   ARM7 = 0U,  /* ARM7 core, Legacy placeholder */
   M3   = 1U,  /* ARM Cortex M3 core */
   R4   = 2U,  /* ARM Cortex R4 core without ECC logic */
   R4F  = 3U,  /* ARM Cortex R4, R4F, and R5 cores with ECC logic*/
   C28  = 4U,  /* TI C28x core */
   Undefined1 = 5U,  /* To Be Determined.  Future core placeholder */
   Undefined2 = 6U,  /* To Be Determined.  Future core placeholder */
   Undefined3 = 7U   /* To Be Determined.  Future core placeholder */
}  ATTRIBUTE_PACKED Fapi_CpuType;

/*!
    \brief This is used to indicate what type of Family is being used.
*/
typedef enum
{
   Family_FMC       = 0x00,
   Family_L2FMC     = 0x10,
   Family_Sonata    = 0x20,
   Family_Stellaris = 0x30,
   Family_Future    = 0x40
} ATTRIBUTE_PACKED Fapi_FamilyType;

/*!
    \brief This is used to indicate what type of Address is being used.
*/
typedef enum
{
   Fapi_Flash,
   Fapi_FlashEcc,
   Fapi_Otp,
   Fapi_OtpEcc,
   Fapi_Undefined
}  ATTRIBUTE_PACKED Fapi_AddressMemoryType;

/*!
    \brief This is used to return the information from the engineering row in the TI OTP.
*/
typedef struct
{
   Luint32 u32AsicId;
   Luint8  u8Revision;
   Luint32 u32LotNumber;
   Luint16 u16FlowCheck;
   Luint16 u16WaferNumber;
   Luint16 u16XCoordinate;
   Luint16 u16YCoordinate;
}  ATTRIBUTE_PACKED Fapi_EngineeringRowType;

typedef struct
{
   Luint32 au32StatusWord[4];
}  ATTRIBUTE_PACKED Fapi_FlashStatusWordType;

/*!
    \brief This contains all the possible modes used in the Fapi_IssueAsyncProgrammingCommand().
*/
typedef enum
{
   Fapi_AutoEccGeneration, /* This is the default u32Mode for the command and will auto generate the ECC for the 
                              provided data buffer */
   Fapi_DataOnly,          /* Command will only process the data buffer */
   Fapi_EccOnly,           /* Command will only process the ecc buffer */
   Fapi_DataAndEcc         /* Command will process data and ecc buffers */
}  ATTRIBUTE_PACKED Fapi_FlashProgrammingCommandsType;

/*!
    \brief This is used to indicate which Flash bank is being used.
*/
typedef enum
{
   Fapi_FlashBank0=0,
   Fapi_FlashBank1=1,
   Fapi_FlashBank2=2,
   Fapi_FlashBank3=3,
   Fapi_FlashBank4=4,
   Fapi_FlashBank5=5,
   Fapi_FlashBank6=6,
   Fapi_FlashBank7=7
}  ATTRIBUTE_PACKED Fapi_FlashBankType;

/*!
    \brief This is used to indicate what F021 Bank Technology the bank is
*/
typedef enum
{
    Fapi_FLEP=0,
    Fapi_FLEE=1,
    Fapi_FLES=2,
    Fapi_FLHV=3
}  ATTRIBUTE_PACKED Fapi_FlashBankTechType;

/*!
    \brief This is used to indicate which Flash sector is being used.
*/
typedef enum
{
   Fapi_FlashSector0,
   Fapi_FlashSector1,
   Fapi_FlashSector2,
   Fapi_FlashSector3,
   Fapi_FlashSector4,
   Fapi_FlashSector5,
   Fapi_FlashSector6,
   Fapi_FlashSector7,
   Fapi_FlashSector8,
   Fapi_FlashSector9,
   Fapi_FlashSector10,
   Fapi_FlashSector11,
   Fapi_FlashSector12,
   Fapi_FlashSector13,
   Fapi_FlashSector14,
   Fapi_FlashSector15,
   Fapi_FlashSector16,
   Fapi_FlashSector17,
   Fapi_FlashSector18,
   Fapi_FlashSector19,
   Fapi_FlashSector20,
   Fapi_FlashSector21,
   Fapi_FlashSector22,
   Fapi_FlashSector23,
   Fapi_FlashSector24,
   Fapi_FlashSector25,
   Fapi_FlashSector26,
   Fapi_FlashSector27,
   Fapi_FlashSector28,
   Fapi_FlashSector29,
   Fapi_FlashSector30,
   Fapi_FlashSector31,
   Fapi_FlashSector32,
   Fapi_FlashSector33,
   Fapi_FlashSector34,
   Fapi_FlashSector35,
   Fapi_FlashSector36,
   Fapi_FlashSector37,
   Fapi_FlashSector38,
   Fapi_FlashSector39,
   Fapi_FlashSector40,
   Fapi_FlashSector41,
   Fapi_FlashSector42,
   Fapi_FlashSector43,
   Fapi_FlashSector44,
   Fapi_FlashSector45,
   Fapi_FlashSector46,
   Fapi_FlashSector47,
   Fapi_FlashSector48,
   Fapi_FlashSector49,
   Fapi_FlashSector50,
   Fapi_FlashSector51,
   Fapi_FlashSector52,
   Fapi_FlashSector53,
   Fapi_FlashSector54,
   Fapi_FlashSector55,
   Fapi_FlashSector56,
   Fapi_FlashSector57,
   Fapi_FlashSector58,
   Fapi_FlashSector59,
   Fapi_FlashSector60,
   Fapi_FlashSector61,
   Fapi_FlashSector62,
   Fapi_FlashSector63
}  ATTRIBUTE_PACKED Fapi_FlashSectorType;

/*!
    \brief This contains all the possible Flash State Machine commands.
*/
typedef enum
{
   Fapi_ProgramData    = 0x0002,
   Fapi_EraseSector    = 0x0006,
   Fapi_EraseBank      = 0x0008,
   Fapi_ValidateSector = 0x000E,
   Fapi_ClearStatus    = 0x0010,
   Fapi_ProgramResume  = 0x0014,
   Fapi_EraseResume    = 0x0016,
   Fapi_ClearMore      = 0x0018
}  ATTRIBUTE_PACKED Fapi_FlashStateCommandsType;

/*LDRA_INSPECTED 495 S MR: 6.3 "This does have a size indicated.  LDRA is incorrect" */
typedef  Luint32 Fapi_FlashStatusType;

/*!
    \brief This contains all the possible Flash State Machine commands.
*/
typedef enum
{
   Fapi_NormalRead = 0x0,
   Fapi_RM0        = 0x1,
   Fapi_RM1        = 0x2
}  ATTRIBUTE_PACKED Fapi_FlashReadMarginModeType;

/*!
    \brief This is the master type containing all possible returned status codes.
*/
typedef enum
{
   Fapi_Status_Success = 0U,           /* Function completed successfully */
   Fapi_Status_FsmBusy = 1U,             /* FSM is Busy */
   Fapi_Status_FsmReady = 2U,            /* FSM is Ready */
   Fapi_Error_Fail = 3U,                 /* Generic Function Fail code */
   Fapi_Error_NullPointer = 4U,          /* One of the pointer parameters is a null pointer */
   Fapi_Error_InvalidCommand = 5U,       /* Command used is invalid for the function called */
   Fapi_Error_InvalidEccAddress = 6U,    /* Returned if the ECC Address given to a function is invalid for that function */
   Fapi_Error_OtpChecksumMismatch = 7U,  /* Returned if OTP checksum does not match expected value */
   Fapi_Error_InvalidHclkValue = 8U,     /* Returned if FClk is above max FClk value - FClk is a calculated from HClk and
                                       RWAIT/EWAIT */
   Fapi_Error_InvalidBank = 9U,          /* Returned if the specified bank does not exist */
   Fapi_Error_InvalidAddress = 10U,       /* Returned if the specified Address does not exist in Flash or OTP */
   Fapi_Error_InvalidReadMode = 11U,      /* Returned if the specified read u32Mode does not exist */
   Fapi_Error_AsyncIncorrectDataBufferLength = 12U,   /* Returned if Data buffer size specified exceeds Data bank width */
   Fapi_Error_AsyncIncorrectEccBufferLength = 13U,    /* Returned if ECC buffer size specified exceeds ECC bank width */
   Fapi_Error_AsyncDataEccBufferLengthMismatch = 14U, /* Returned if Data buffer size either is not 64bit aligned or Data
                                                   length exceeds amount ECC supplied */
   Fapi_Error_FeatureNotAvailable = 15U  /* FMC feature is not available on this device */
}  ATTRIBUTE_PACKED Fapi_StatusType;

/*lint -e960*/
/*LDRA_NOANALYSIS*/
/*LDRA_INSPECTED 42 S MR: 3.5 "Necessary for FMC register definitions" */
/*LDRA_INSPECTED 74 S MR: 18.4 "Necessary for FMC register definitions" */
typedef union
{
	volatile struct
   {
#if defined (_C28X)
      Luint16 ChecksumLength:16;  /* 0x150 bits 15:0 */
      Luint16 OtpVersion:16;      /* 0x150 bits 31:16 */
      Luint32 OtpChecksum;        /* 0x154 bits 31:0 */
      Luint16 NumberOfBanks:16;   /* 0x158 bits 15:0 */
      Luint16 NumberOfSectors:16; /* 0x158 bits 31:16 */
      Luint16 MemorySize:16;      /* 0x15C bits 15:0 */
      Luint16 Package:16;         /* 0x15C bits 31:16 */
      Luint16 SiliconRevision:8;  /* 0x160 bits 7:0 */
      Luint16 AsicNumber_23_8:8; /* 0x160 bits 31:8 */
      Luint16 AsicNumber_31_24:16; /* 0x160 bits 31:8 */
      Luint32 LotNumber;          /* 0x164 bits 31:0 */
      Luint16 WaferNumber:16;     /* 0x168 bits 15:0 */
      Luint16 Flowbits:16;        /* 0x168 bits 31:16 */
      Luint16 YCoordinate:16;     /* 0x16C bits 15:0 */
      Luint16 XCoordinate:16;     /* 0x16C bits 31:16 */
      Luint16 EVSU:8;             /* 0x170 bits 7:0 */
      Luint16 PVSU:8;             /* 0x170 bits 15:8 */
      Luint16 ESU:8;              /* 0x170 bits 23:16 */
      Luint16 PSU:8;              /* 0x170 bits 31:24 */
      Luint16 CVSU:12;            /* 0x174 bits 11:0 */
      Luint16 Add_EXEZSU:4;       /* 0x174 bits 15:12 */
      Luint16 PVAcc:8;            /* 0x174 bits 23:16 */
      Luint16 RVSU:8;             /* 0x174 bits 31:24 */
      Luint16 PVH2:8;             /* 0x178 bits 7:0 */
      Luint16 PVH:8;              /* 0x178 bits 15:8 */
      Luint16 RH:8;               /* 0x178 bits 23:16 */
      Luint16 PH:8;               /* 0x178 bits 31:24 */
      Luint16 SmFrequency:12;     /* 0x17C bits 11:0 */
      Luint16 VSTAT:4;            /* 0x17C bits 15:12 */
      Luint16 Sequence:8;         /* 0x17C bits 23:16 */
      Luint16 EH:8;               /* 0x17C bits 31:24 */
      Luint16 VHV_EStep:16;       /* 0x180 bits 15:0 */
      Luint16 VHV_EStart:16;      /* 0x180 bits 31:16 */
      Luint16 MAX_PP:16;          /* 0x184 bits 15:0 */
      Luint16 OtpReserved1:16;    /* 0x184 bits 31:16 */
      Luint16 PROG_PW:16;         /* 0x188 bits 15:0 */
      Luint16 MAX_EP:16;          /* 0x188 bits 31:16 */
      Luint32 ERA_PW;             /* 0x18C bits 31:0 */
      Luint16 VHV_E:16;           /* 0x190 bits 15:0 */
      Luint16 VHV_P:16;           /* 0x190 bits 31:16 */
      Luint16 VINH:8;             /* 0x194 bits 7:0 */
      Luint16 VCG:8;              /* 0x194 bits 15:8 */
      Luint16 VHV_PV:16;          /* 0x194 bits 31:16 */
      Luint16 OtpReserved2:8;     /* 0x198 bits 7:0 */
      Luint16 VRead:8;            /* 0x198 bits 15:8 */
      Luint16 VWL_P:8;            /* 0x198 bits 23:16 */
      Luint16 VSL_P:8;            /* 0x198 bits 31:24 */
      Luint32 ApiChecksum;        /* 0x19C bits 15:0 */
      Luint32 OtpReserved3;    /* 0x1A0 bits 31:0 */
      Luint32 OtpReserved4;    /* 0x1A4 bits 31:0 */
      Luint32 OtpReserved5;    /* 0x1A8 bits 31:0 */
      Luint32 OtpReserved6;    /* 0x1AC bits 31:0 */
#else
      Luint32 ChecksumLength:16;  /* 0x150 bits 15:0 */
      Luint32 OtpVersion:16;      /* 0x150 bits 31:16 */
      Luint32 OtpChecksum;        /* 0x154 bits 31:0 */
      Luint32 NumberOfBanks:16;   /* 0x158 bits 15:0 */
      Luint32 NumberOfSectors:16; /* 0x158 bits 31:16 */
      Luint32 MemorySize:16;      /* 0x15C bits 15:0 */
      Luint32 Package:16;         /* 0x15C bits 31:16 */
      Luint32 SiliconRevision:8;  /* 0x160 bits 7:0 */
      Luint32 AsicNumber:24;       /* 0x160 bits 31:8 */
      Luint32 LotNumber;          /* 0x164 bits 31:0 */
      Luint32 WaferNumber:16;     /* 0x168 bits 15:0 */
      Luint32 Flowbits:16;        /* 0x168 bits 31:16 */
      Luint32 YCoordinate:16;     /* 0x16C bits 15:0 */
      Luint32 XCoordinate:16;     /* 0x16C bits 31:16 */
      Luint32 EVSU:8;             /* 0x170 bits 7:0 */
      Luint32 PVSU:8;             /* 0x170 bits 15:8 */
      Luint32 ESU:8;              /* 0x170 bits 23:16 */
      Luint32 PSU:8;              /* 0x170 bits 31:24 */
      Luint32 CVSU:12;            /* 0x174 bits 11:0 */
      Luint32 Add_EXEZSU:4;       /* 0x174 bits 15:12 */
      Luint32 PVAcc:8;            /* 0x174 bits 23:16 */
      Luint32 RVSU:8;             /* 0x174 bits 31:24 */
      Luint32 PVH2:8;             /* 0x178 bits 7:0 */
      Luint32 PVH:8;              /* 0x178 bits 15:8 */
      Luint32 RH:8;               /* 0x178 bits 23:16 */
      Luint32 PH:8;               /* 0x178 bits 31:24 */
      Luint32 SmFrequency:12;     /* 0x17C bits 11:0 */
      Luint32 VSTAT:4;            /* 0x17C bits 15:12 */
      Luint32 Sequence:8;         /* 0x17C bits 23:16 */
      Luint32 EH:8;               /* 0x17C bits 31:24 */
      Luint32 VHV_EStep:16;       /* 0x180 bits 15:0 */
      Luint32 VHV_EStart:16;      /* 0x180 bits 31:16 */
      Luint32 MAX_PP:16;          /* 0x184 bits 15:0 */
      Luint32 OtpReserved1:16;    /* 0x184 bits 31:16 */
      Luint32 PROG_PW:16;         /* 0x188 bits 15:0 */
      Luint32 MAX_EP:16;          /* 0x188 bits 31:16 */
      Luint32 ERA_PW;             /* 0x18C bits 31:0 */
      Luint32 VHV_E:16;           /* 0x190 bits 15:0 */
      Luint32 VHV_P:16;           /* 0x190 bits 31:16 */
      Luint32 VINH:8;             /* 0x194 bits 7:0 */
      Luint32 VCG:8;              /* 0x194 bits 15:8 */
      Luint32 VHV_PV:16;          /* 0x194 bits 31:16 */
      Luint32 OtpReserved2:8;     /* 0x198 bits 7:0 */
      Luint32 VRead:8;            /* 0x198 bits 15:8 */
      Luint32 VWL_P:8;            /* 0x198 bits 23:16 */
      Luint32 VSL_P:8;            /* 0x198 bits 31:24 */
      Luint32 ApiChecksum:32;     /* 0x19C bits 31:0 */
      Luint32 OtpReserved3:32;    /* 0x1A0 bits 31:0 */
      Luint32 OtpReserved4:32;    /* 0x1A4 bits 31:0 */
      Luint32 OtpReserved5:32;    /* 0x1A8 bits 31:0 */
      Luint32 OtpReserved6:32;    /* 0x1AC bits 31:0 */
#endif        
   } OTP_VALUE;
   volatile Luint8  au8OtpWord[0x60];
   volatile Luint16 au16OtpWord[0x30];
   volatile Luint32 au32OtpWord[0x18];
}Fapi_TiOtpBytesType;
/*LDRA_ANALYSIS*/
/*lint +e960*/

typedef struct TI_OTP_TYPE
{
   Fapi_TiOtpBytesType aOtpBank[8];
}Fapi_TiOtpType;

/*!
    \brief
*/
typedef enum
{
   Alpha_Internal,          /* For internal TI use only.  Not intended to be used by customers */
   Alpha,                   /* Early Engineering release.  May not be functionally complete */
   Beta_Internal,           /* For internal TI use only.  Not intended to be used by customers */
   Beta,                    /* Functionally complete, to be used for testing and validation */
   Production               /* Fully validated, functionally complete, ready for production use */
}  ATTRIBUTE_PACKED Fapi_ApiProductionStatusType;

typedef struct
{
   Luint8  u8ApiMajorVersion;
   Luint8  u8ApiMinorVersion;
   Luint8  u8ApiRevision;
   Fapi_ApiProductionStatusType oApiProductionStatus;
   Luint32 u32ApiBuildNumber;
   Luint8  u8ApiTechnologyType;
   Luint8  u8ApiTechnologyRevision;
   Luint8  u8ApiEndianness;
   Luint32 u32ApiCompilerVersion;
}Fapi_LibraryInfoType;

typedef struct
{
   Luint16 u16NumberOfBanks;
   Luint16 u16Reserved;
   Luint16 u16DeviceMemorySize;
   Luint16 u16DevicePackage;
   Luint32 u32AsicId;
   Luint32 u32LotNumber;
   Luint16 u16WaferNumber;
   Luint16 u16FlowCheck;
   Luint16 u16WaferYCoordinate;
   Luint16 u16WaferXCoordinate;
}Fapi_DeviceInfoType;

typedef struct
{
    Fapi_FlashBankTechType oFlashBankTech;
    Luint32 u32NumberOfSectors;
    Luint32 u32BankStartAddress;
    Luint16 au16SectorSizes[16];
}Fapi_FlashBankSectorsType;

#endif //WIN32

#endif /* _RM4_FLASH_TYPES_H_*/

/**********************************************************************************************************************
 *  END OF FILE: Types.h
 *********************************************************************************************************************/
