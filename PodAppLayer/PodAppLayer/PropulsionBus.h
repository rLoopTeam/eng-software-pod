#pragma once

#include "rPodCommonConstants.h"

float PropulsionBusVoltage;
float PropulsionBusCurrent;
enum RelayStatus PropulsionBusRelay;


propulsionBusStatus PropulsionBusStatus;

enum propulsionBusStatus {
	PropulsionBusOk,
	PropulstionBusError
};