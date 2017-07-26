/**
 * @file		HE_THERM__TYPES.H
 * @brief		Type defines
 * @author		Lachlan Grogan
 * @st_fileID	LCCM721R0.FILE.003
 */

#ifndef _HE_THERM__TYPES_H_
#define _HE_THERM__TYPES_H_


	/** Temp sensor scanning states */
	typedef enum
	{

		/** Do nothing */
		HETHERM_TEMP_STATE__IDLE = 0U,

		/** Load the temp sensor defaults from memory */
		HETHERM_TEMP_STATE__LOAD_DEFAULTS,

		/** Configure the sensor resolution after the memory load */
		HETHERM_TEMP_STATE__CONFIGURE_RESOLUTION,

		/** If we are not loading from memory start a scan */
		HETHERM_TEMP_STATE__START_SCAN,

		/** Wait for the scanning to finish */
		HETHERM_TEMP_STATE__WAIT_SCAN,

		/** Running with the temp system */
		HETHERM_TEMP_STATE__RUN

	}TE_HETHERM_TEMP__STATE_T;


#endif //_HE_THERM__TYPES_H_
