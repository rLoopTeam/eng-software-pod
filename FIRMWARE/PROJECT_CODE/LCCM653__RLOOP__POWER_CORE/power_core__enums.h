/**
 * @file		power_core__enums.h
 * @brief		Power Node Control Code Constants
 * @author		Edward Chan
 * @copyright	rLoop Inc.
 */

#ifndef RLOOP_LCCM653__RLOOP__POWER_CORE_POWER_CORE__ENUMS_H_
#define RLOOP_LCCM653__RLOOP__POWER_CORE_POWER_CORE__ENUMS_H_

/** Hover Engine Cooling System Enums **/
typedef enum
{
	POWER_COOLING__MAX_HOVERENG = 4U
}E_PWR__COOLING_HOVERENGINES_INDEX_T;

/** Hover Engine Cooling System States **/
typedef enum
{
	/** The solenoid is off */
	POWER_COOLING__HOVER_OFF = 0U,

	/** The solenoid is on */
	POWER_COOLING__HOVER_ON
}E_PWR__COOLING_HOVESOLENOID_STATE_T;

/** Eddy Brakes Coolinig System Enums **/
typedef enum
{
	POWER_COOLING__MAX_EDDYBRAKES = 1U
}E_PWR__COOLING_EDDYBRAKES_INDEX_T;

/** Eddy Brakes Cooling System States **/
typedef enum
{
	/** The solenoid is off */
	POWER_COOLING__EDDY_OFF = 0U,

	/** The solenoid is on */
	POWER_COOLING__EDDY_ON
}E_PWR__COOLING_EDDYSOLENOID_STATE_T;

/** Cooling System Status**/
typedef enum
{
	COOLING_STATE__WAITING,
	COOLING_STATE__NORMAL,
	COOLING_STATE__WARNING,
	COOLING_STATE__CRITICAL,
	COOLING_STATE__EMERGENCY
}E_PWRNODE__COOLING_STATES;

#endif /* RLOOP_LCCM653__RLOOP__POWER_CORE_POWER_CORE__ENUMS_H_ */


