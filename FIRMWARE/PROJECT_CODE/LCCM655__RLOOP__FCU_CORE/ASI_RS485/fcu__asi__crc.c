/**
 * @file		FCU__ASI__CRC.C
 * @brief		CRC Functions
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__ASI__CRC
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U

//the structure
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Compute the CRC
 * 
 * @param[in]		u16DataLen				Length of data
 * @param[in]		*pu8Data				framedParameter
 * @return			The returned CRC
 * @st_funcMD5		05528F06BBCE33A1BDD3D45F7ADDEA6E
 * @st_funcID		LCCM655R0.FILE.071.FUNC.001
 */
Luint16 u16FCU_ASI_CRC__ComputeCRC(Luint8 *pu8Data, Luint16 u16DataLen)
{
	Luint16 u16CRC;
	Luint16 u16TempCRC;
	Luint8 u8TempLSB;
	Luint8 u8Flag;
	Luint16 u16ByteIndex;
	Luint8 u8BitIndex;

	//init
	u16CRC = 0xFFFFU;

	if(pu8Data != 0x00000000)
	{
		for(u16ByteIndex = 0; u16ByteIndex < u16DataLen - 2U; u16ByteIndex++)
		{
			u8TempLSB = 0x00FF & u16CRC;

			u16CRC = u8TempLSB ^ pu8Data[u16ByteIndex];

			for(u8BitIndex = 0; u8BitIndex < 8U; u8BitIndex++)
			{
				u16TempCRC = u16CRC;

				u8Flag = u16TempCRC & 0x0001U;

				u16CRC = u16CRC >> 1U;

				if(u8Flag != 0x00U)
				{
					u16CRC = u16CRC ^ 0xA001U;
				}
				else
				{
					//fall on
				}

			}//for(u8BitIndex = 0; u8BitIndex < 8; u8BitIndex++)
		}
	}
	else
	{
		//fall on with 0xFFF
	}

	return u16CRC;
}

/***************************************************************************//**
 * @brief
 * Add CRC to modbus command frame
 * 
 * @param[in]		*pu8Data				framedParameter
 * @st_funcMD5		8ACCAE552F9F545DBB5F8093372A0D04
 * @st_funcID		LCCM655R0.FILE.071.FUNC.002
 */
void vFCU_ASI_CRC__AddCRC(Luint8 *pu8Data)
{
	Luint16 u16CRC;

	if(pu8Data != 0x00000000U)
	{
		u16CRC = u16FCU_ASI_CRC__ComputeCRC(pu8Data, C_ASI__RW_FRAME_SIZE);

		// lower crc byte
		pu8Data[6]= (Luint8)(u16CRC & 0x00FFU);

		// higher crc byte
		pu8Data[7]= (Luint8)(u16CRC >> 8U);
	}
	else
	{
		//pointer error
	}
}

/***************************************************************************//**
 * @brief
 * Check CRC from ASI device response
 *
 * @param[in]	rData		Response Data
 * @return			-1 = error
 * 					0 = success
 */
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u8DataLen		## Desc ##
 * @param[in]		*pu8Data		## Desc ##
 * @st_funcMD5		3B9AF9CEEF213072301C15272C0EBDFC
 * @st_funcID		LCCM655R0.FILE.071.FUNC.003
 */
Lint16 s16FCU_ASI_CRC__CheckCRC(Luint8 *pu8Data, Luint8 u8DataLen)
{
	Luint16 u16CRC;
	Lint16 s16Return;



	if(pu8Data != 0x00000000U)
	{
		u16CRC = u16FCU_ASI_CRC__ComputeCRC(pu8Data, u8DataLen);

		if ( ( (pu8Data[u8DataLen + 1]) != (u16CRC >> 8) ) || ( (pu8Data[u8DataLen]) != (u16CRC & 0x00FF) ) )
		{
			s16Return = -1;
		}
		else
		{
			//success
			s16Return = 0U;
		}
	}
	else
	{
		s16Return = -2;
	}

	return s16Return;
}


#endif //C_LOCALDEF__LCCM655__ENABLE_ASI_RS485
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
