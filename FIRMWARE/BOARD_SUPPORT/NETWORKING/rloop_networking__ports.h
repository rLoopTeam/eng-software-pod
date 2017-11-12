#ifndef _RLOOP_NETWORKING__PORTS_H_
#define _RLOOP_NETWORKING__PORTS_H_


	//http://confluence.rloop.org/display/SD/Static+IP+Assignments
	
		/** 192.168.x Subnet, allows easy network change */
#ifdef __LACHLANS__PC__
	#define C_RLOOP_NET_IP__SUBNET								(1U)
#else
	#define C_RLOOP_NET_IP__SUBNET								(1U)
#endif
	
	/** Flight Control Unit*/
	#define C_RLOOP_NET_PORT__FCU								(9531U)
	/** Flight Control Lower Network IP*/
	#define C_RLOOP_NET_IP__FCU									(100U)

    /** Landing Gear Unit*/
    #define C_RLOOP_NET_PORT__LGU                               (9548U)
    /** LGU Lower Network IP*/
    #define C_RLOOP_NET_IP__LGU                                 (120U)
	
	/** Aux Propulsion Unit*/
	#define C_RLOOP_NET_PORT__APU								(9615U)
	/** Aux Prop Lower Network IP*/
	#define C_RLOOP_NET_IP__APU									(140U)

	/** HE Thermal Unit*/
	#define C_RLOOP_NET_PORT__HETHERM							(9608U)
	/** HE Thermal Lower Network IP*/
	#define C_RLOOP_NET_IP__HETHERM								(141U)


	#define C_RLOOP_NET__POWER_A__PORT					(9110U)
	#define C_RLOOP_NET__POWER_B__PORT					(9111U)
	
	
#endif //_RLOOP_NETWORKING__PORTS_H_

