
#ifndef __POWER__PI_COMMS__TYPES_H_
#define __POWER__PI_COMMS__TYPES_H_


	/** Pi Comms SM types*/
	typedef enum
	{

		/** Do nothing */
		PICOM_STATE__IDLE = 0U,

		/** Setup for the next frame transmission */
		PICOM_STATE__SETUP_FRAME,

		/** assemble the next buffer of data */
		PICOM_STATE__ASSEMBLE_BUFFER,

		/** Star the DMA transaction */
		PICOM_STATE__START_DMA,

		/** once started, wait for the DMA to complete */
		PICOM_STATE__WAIT_DMA,


	}E_POWER_PICOM__STATE_T;



#endif /* __POWER__PI_COMMS__TYPES_H_ */
