/*
 * fcu__fctl__track_database__types.h
 *
 *  Created on: 20 Jan 2017
 *      Author: Lachlan
 */

#ifndef _FCU__FCTL__TRACK_DATABASE__TYPES_H_
#define _FCU__FCTL__TRACK_DATABASE__TYPES_H_

	//some defines for this system

	/** Total number of track databases stored in memory */
	#define C_FCTL_TRACKDB__MAX_MEM_DATABASES							(8U)

	/** Max number of stripes the track DB knows about */
	#define C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES						(64U)

	/** The maximum number of setpoints */
	#define C_FCTL_TRACKDB__MAX_SETPOINTS								(1024U)

	/** Header spare words are requred to bring the packet size up */
	#define C_FCTL_TRACKDB__HEADER_SPARE_WORDS							(16U)

	#define C_FCTL_TRACKDB__PROFILE_SPARE_WORDS							(16U)

	/** Define the size of the blob, but compare this to the actual sizeof*/
	#define C_FCTL_TRACKDB__BLOB_SIZE			 ((((8U + C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES + C_FCTL_TRACKDB__HEADER_SPARE_WORDS) + (4U + C_FCTL_TRACKDB__MAX_SETPOINTS + C_FCTL_TRACKDB__MAX_SETPOINTS + C_FCTL_TRACKDB__PROFILE_SPARE_WORDS)) * 4U) + 2U)

	/** List of all track databases
	 * SHOULD MAKE A MULTIPLE OF 16 BYTES for better eeprom layout
	 * 8 + STRIPES(64) + SPARE(16) = 88
	 * 6 + SPARE(16) + SETPOINTS(256)*2 =
	 * 2 +
	 * = 626
	 * 16 * 40 = 640*4 = 2560/16 = 160
	 * */
#ifdef WIN32
	#pragma pack(push, 1)
#endif
	struct _strTrackDatabase
	{

		/** Track database structure.
		 * Static description of the track (regardless of run profile).
		 * Can be merged with run profile struc if more convenient
		 */
		struct
		{

			/**1 Header word for easy identification
			 * Could be like 0xABCD1234*/
			//Luint32 u32Header;
			Luint8 u8Header[4];

			/**2 The total length of the data from after this point to the end of
			 * the CRC
			 */
			//Luint32 u32DataLength;
			Luint8 u8DataLength[4];

			/**3 This is the ID of the track database entry.  User should match this to
			 * what is expected for the current run;
			 */
			//Luint32 u32TrackID;
			Luint8 u8TrackID[4];

			/**4 Track beginning. Should be always 0 by construction, but we may have situations
			 * where we need to adjust this */
			//Luint32 u32TrackBeginningXPosition_mm;
			Luint8 u8TrackBeginningXPosition_mm[4];

			/**5 Track end. x position of foam pit */
			//Luint32 u32TrackEndXPosition_mm;
			Luint8 u8TrackEndXPosition_mm[4];

			/**6 Minimum x position in tube to start using LRF.
			 * Called "min position to use laser range finder" in FCU spec 2.3 */
			//Luint32 u32LRFAreaBeginningXPosition_mm;
			Luint8 u8LRFAreaBeginningXPosition_mm[4];

			/**5 Number of stripes on this track (listed in the array below).
			 * Max 41 in the big tube.
			 * Can't be greater than C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES*/
			//Luint32 u32NumberOfStripes;
			Luint8 u8NumberOfStripes[4];

			/**8 List of stripes beginning x position in tube. Called "stripes location table" in FCU spec 2.3 */
			//Luint32 u32StripeBeginningXPosition_mm[C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES];
			Luint8 u8StripeBeginningXPosition_mm[C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES][4];

			/** Enable Accels on the current track */
			Luint8 u8EnableAccels[4];

			/** Enable laser range on the current track */
			Luint8 u8EnableLRF[4];

			/** Enable contrast sensor on current track */
			Luint8 u8EnableContrast[4];

			/** Spare Data */
			Luint8 u8SpareData[C_FCTL_TRACKDB__HEADER_SPARE_WORDS][4];

			/** Footer to know we are valid here */
			Luint8 u8Footer[4];

			/** Run profile structure */
			struct
			{

				/** Bytes 0-3: x position of the front of the pusher car (or rear of pod) before the run. Called "pusher start x position" in FCU spec 2.3 "*/
				//Luint32 u32PusherFrontStartXPosition_mm;
				Luint8 u8PusherFrontStartXPosition_mm[4];

				/** Bytes 4-7: expected x position of the front of the pusher car at the end of push phase. Called "end pushed phase x position" in FCU spec 1.1 */
				//Luint32 u32PusherFrontEndXPosition_mm;
				Luint8 u8PusherFrontEndXPosition_mm[4];


				/** Bytes 8-11: Target x position of pod front at the end of the run. Called "stop x position" in FCU spec 8.4 */
				//Luint32 u32PodFrontTargetXPosition_mm;
				Luint8 u8PodFrontTargetXPosition_mm[4];

				/** Byte 12: Number of setpoints of braking curve for this run.
				 * Not sure of the max. Using 100 as an example.
				 * Can't be greater than C_FCTL_TRACKDB__MAX_SETPOINTS*/
				//Luint32 u32NumberOfSetpoints;
				Luint8 u8NumberOfSetpoints[4];

				/** Bytes 13-112: List of braking setpoints' x position */
				//Luint32 u32BrakingSetPointXPosition_mm[C_FCTL_TRACKDB__MAX_SETPOINTS];
				Luint8 u8BrakingSetPointXPosition_mm[C_FCTL_TRACKDB__MAX_SETPOINTS][4];

				/** Bytes 113-212: List of braking setpoints' speed */
				//sLuint32 u32BrakingSetPointSpeed_mms[C_FCTL_TRACKDB__MAX_SETPOINTS];
				Luint8 u8BrakingSetPointSpeed_mms[C_FCTL_TRACKDB__MAX_SETPOINTS][4];

				/** Spare Data */
				Luint8 u8SpareData[C_FCTL_TRACKDB__PROFILE_SPARE_WORDS][4];


			}sRunProfile;

			/** The CRC for this entire packet
			 * Only 16bit CRC */
			Luint8 u8CRC[2];

			//needed to keep the file size div by 16 and div into chunks of 10 less than eth frame size.
			Luint8 u8Unused[2];

		}sDB;

	#ifndef WIN32
	};
	#else
	};
	#endif
#ifdef WIN32
	#pragma pack(pop)
#endif







#endif /* _FCU__FCTL__TRACK_DATABASE__TYPES_H_ */
