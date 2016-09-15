#pragma once

enum PodState {
	PodState_StandBy,
	PodState_WaitingForPusher,
	PodState_BeingPushed,
	PodState_Coasting,
	PodState_Braking,
	PodState_Parking,
	PodState_RunDone,
	PodState_EBrake,
	PodState_Disabled
};

typedef enum RelayStatus {
	RelayOpen = 0,
	RelayClosed = 1
};