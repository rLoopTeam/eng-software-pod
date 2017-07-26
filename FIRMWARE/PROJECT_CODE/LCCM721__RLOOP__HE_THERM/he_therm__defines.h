/**
 * @file		HE_THERM__DEFINES.H
 * @brief		HET Defines
 * @author		Lachlan Grogan
 * @st_fileID	LCCM721R0.FILE.011
 */


#ifndef LCCM721__RLOOP__HE_THERM_HE_THERM__DEFINES_H_
#define LCCM721__RLOOP__HE_THERM_HE_THERM__DEFINES_H_


	/** Mask for Temp Sensor ROM ID's that are on the left side of the pod */
	#define C_HETHERM_ROMID_MASK__LEFT_SIDE			0x01, 0x00

	/** Mask for Temp Sensor ROM ID's that are on the right side of the pod */
	#define C_HETHERM_ROMID_MASK__RIGHT_SIDE		0x02, 0x00

	/** Mask for Temp Sensor ROM ID's that are on brake motors */
	#define C_HETHERM_ROMID_MASK__BRAKE_MOTORS		0x04, 0x00




#endif /* LCCM721__RLOOP__HE_THERM_HE_THERM__DEFINES_H_ */
