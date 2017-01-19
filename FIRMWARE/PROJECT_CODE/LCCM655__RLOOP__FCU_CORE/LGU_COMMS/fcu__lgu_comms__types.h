/*
 * fcu__lgu_comms__types.h
 *
 *  Created on: 19 Jan 2017
 *      Author: Lachlan
 */

#ifndef _FCU__LGU_COMMS__TYPES_H_
#define _FCU__LGU_COMMS__TYPES_H_

	/** LGU Commands */
	typedef enum
	{

		/** Just a nothing type */
		LGU_COM__NOTHING = 0U,

		/** F->L Request status flags */
		LGU_COM__FCU_LGU__REQUEST_STATUS,

		LGU_COM__LGU_FCU__TX_STATUS,


	}E_FCU_LGU_COMM_TYPES_T;



#endif /* _FCU__LGU_COMMS__TYPES_H_ */
