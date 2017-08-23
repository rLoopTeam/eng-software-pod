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


	/** Track database V2
	 * Header = 4
	 * Size = 16 + 16 + 16 + 16 + 16 = 80
	 * Spares 10
	 * CRC = 2
	 * For 8 tracks = 656 bytes.
	 * */
#ifdef WIN32
	#pragma pack(push, 1)
#endif
	typedef struct
	{

		/** A simple header word to ensure we can ID our memory */
		Luint8 u8Header[4];

		struct
		{

			/** Accel Subsystem */
			struct
			{

				/** Use the accel system as part of the track database */
				Luint8 u8Use;

				/** Accel threshold S32*/
				Luint8 u8AccelThresh_mm_ss[4];

				/** Threshold time */
				Luint8 u8AccelThresh_x10ms[4];

				/** Decel threshold S32*/
				Luint8 u8DecelThresh_mm_ss[4];

				/** Threshold time */
				Luint8 u8DecelThresh_x10ms[4];

				// @todo: adjust the spares to account for added DecelThresh
				/** Spare */
				Luint32 u32Spare;

				//3 spares to take it to 16 bytes
				Luint8 u8Spares[3];

			}sAccel;

			/** FWD Laser configuration */
			struct
			{

				/** Use the forward laser */
				Luint8 u8Use;

				//make up 16 spares
				Luint8 u8Spares[15];

			}sFwdLaser;

			/** Contrast laser config */
			struct
			{
				/** Use the contrast laser */
				Luint8 u8Use;

				//make up 16 spares
				Luint8 u8Spares[15];

			}sContrastLaser;


			/** Control options */
			struct
			{

				/** Use the pusher pin detection */
				Luint8 u8UsePusher;

				/** Use hover engines, if 0 then do not spinup or spindown */
				Luint8 u8UseHover;

				/** Use Landing Gear Control */
				Luint8 u8UseLandingGear;

				/** Enable end of run cooling */
				Luint8 u8UseCooling;

				/** Should we transition from accel to coast on pusher or just timeout?*/
				Luint8 u8EnablePuserSeparationDetection;

				/** make up to 16*/
				Luint8 u8Spares[12];

			}sControl;

			/** Track Specifics */
			struct
			{

				/** The start of pod on track in mm */
				Luint8 u8TrackStart_mm[4];

				/** The end position of track in mm */
				Luint8 u8TrackEnd_mm[4];

				/** The length of the track in mm */
				Luint8 u8TrackLength_mm[4];

				/** make up to 16 bytes */
				Luint8 u8Spares[4];

			}sTrack;

			/** Timers */
			struct
			{

				/** The time from accel to coast interlock */
				Luint8 u8Accel_Coast[4];

				/** The time from coast to brake */
				Luint8 u8Coast_Brake[4];

			}sTime;


		}sDB2[C_FCTL_TRACKDB__MAX_MEM_DATABASES];

		//make up to x16 for RM48 alignment
		//should get zeroed out when WIN32 creates the file
		Luint8 u8Dummy[16-2-4-4-4];

		//CRC protection
		Luint8 u8CRC[2];

	#ifndef WIN32
	}TS_FCU_TRACK_DB;
	#else
	}TS_FCU_TRACK_DB;
	#endif
	#ifdef WIN32
	#pragma pack(pop)
	#endif


#if 0
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

#endif //0


#endif /* _FCU__FCTL__TRACK_DATABASE__TYPES_H_ */
