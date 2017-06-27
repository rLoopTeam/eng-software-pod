//ONLY RUN THIS ON POWER NODE

#include <localdef.h>


typedef enum
{

	STATE__NEW_FRAME = 0U,

	STATE__LOAD_BUFFER,

	STATE__START_DMA,

	STATE__WAIT_DMA_DONE,

	STATE__END

}TEST_STATES;


int main()
{

	TEST_STATES eState;
	Luint32 u32Length;
	Luint8 * pu8Buffer;
	Luint8 u8Test;

	//init the FLASH memory
	vRM4_FLASH__Init();

	//init the DMA
	vRM4_DMA__Init();

	//init SCI2
	vRM4_SCI__Init(SCI_CHANNEL__2);
	vRM4_SCI__Set_Baudrate(SCI_CHANNEL__2, 9600);

	//init pi comms
	vPICOMMS__Init();

	//init states
	eState = STATE__NEW_FRAME;

	//main program loop.
	while(1)
	{

		//handle the states
		switch(eState)
		{

			case STATE__NEW_FRAME:

				//start a new frame
				rI2CTX_beginFrame();

				//move state
				eState = STATE__LOAD_BUFFER;
				break;

			case STATE__LOAD_BUFFER:

				//add 0xAA as param 1
				rI2CTX_addParameter_uint8(0x0001U, 0xAA);

				eState = STATE__START_DMA;
				break;

			case STATE__START_DMA:

				//end the frame
				u32Length = (Luint32)rI2CTX_endFrame();

				//get the buffer pointer
				pu8Buffer = pu8I2CTx__Get_BufferPointer();

				//todo, probably should check transaction is not running

				//start the transaction.
				vRM4_SCI_DMA__Begin_Tx(SCI_CHANNEL__2, pu8Buffer, u32Length);

				//change state
				eState = STATE__WAIT_DMA_DONE;
				break;

			case STATE__WAIT_DMA_DONE:

				u8Test = u8RM4_SCI_DMA__Is_TxBusy(SCI_CHANNEL__2);
				if(u8Test == 0U)
				{
					eState = STATE__END;
				}
				else
				{
					//stay in state
				}

				break;

			case STATE__END:

				break;
		}

	}
}



