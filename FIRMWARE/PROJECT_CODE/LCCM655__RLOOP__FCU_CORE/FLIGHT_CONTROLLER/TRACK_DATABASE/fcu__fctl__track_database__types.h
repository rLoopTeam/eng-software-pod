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
	#define C_FCTL_TRACKDB__MAX_MEM_DATABASES							(16U)

	/** Max number of stripes the track DB knows about */
	#define C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES						(64U)

	/** The maximum number of setpoints */
	#define C_FCTL_TRACKDB__MAX_SETPOINTS								(256U)

	#define C_FCTL_TRACKDB__HEADER_SPARE_WORDS							(16U)

	#define C_FCTL_TRACKDB__PROFILE_SPARE_WORDS							(16U)

	/** Define the size of the blob, but compare this to the actual sizeof*/
	#define C_FCTL_TRACKDB__BLOB_SIZE			 ((((8U + C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES + C_FCTL_TRACKDB__HEADER_SPARE_WORDS) + (6U + C_FCTL_TRACKDB__MAX_SETPOINTS + C_FCTL_TRACKDB__MAX_SETPOINTS + C_FCTL_TRACKDB__PROFILE_SPARE_WORDS)) * 4U) + 2U)

	/** List of all track databases
	 * SHOULD MAKE A MULTIPLE OF 16 BYTES for better eeprom layout
	 *
	 * */
	struct _strTrackDatabases
	{

		/** Track database structure.
		 * Static description of the track (regardless of run profile).
		 * Can be merged with run profile struc if more convenient
		 */
		struct
		{

			/** Header word for easy identification
			 * Could be like 0xABCD1234*/
			Luint32 u32Header;

			/** The total length of the data from after this point to the end of
			 * the CRC
			 */
			Luint32 u32DataLength;

			/** This is the ID of the track database entry.  User should match this to
			 * what is expected for the current run;
			 */
			Luint32 u32TrackID;

			/** Bytes 0-3: Track beginning. Should be always 0 by construction, but we may have situations
			 * where we need to adjust this */
			Luint32 u32TrackBeginningXPosition_mm;

			/** Bytes 4-7: Track end. x position of foam pit */
			Luint32 u32TrackEndXPosition_mm;

			/** Bytes 8-11: Minimum x position in tube to start using LRF.
			 * Called "min position to use laser range finder" in FCU spec 2.3 */
			Luint32 u32LRFAreaBeginningXPosition_mm;

			/** Byte 12: Number of stripes on this track (listed in the array below).
			 * Max 41 in the big tube.
			 * Can't be greater than C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES*/
			Luint32 u32NumberOfStripes;

			/** Bytes 13-53: List of stripes beginning x position in tube. Called "stripes location table" in FCU spec 2.3 */
			Luint32 u32StripeBeginningXPosition_mm[C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES];

			/** Spare Data */
			Luint32 u32SpareData[C_FCTL_TRACKDB__HEADER_SPARE_WORDS];

			/** Footer to know we are valid here */
			Luint32 u32Footer;

			/** Run profile structure */
			struct
			{

				/** Just so we know that we are valid here */
				Luint32 u32Header;

				/** Bytes 0-3: x position of the front of the pusher car (or rear of pod) before the run. Called "pusher start x position" in FCU spec 2.3 "*/
				Luint32 u32PusherFrontStartXPosition_mm;

				/** Bytes 4-7: expected x position of the front of the pusher car at the end of push phase. Called "end pushed phase x position" in FCU spec 1.1 */
				Luint32 u32PusherFrontEndXPosition_mm;

				/** Bytes 8-11: Target x position of pod front at the end of the run. Called "stop x position" in FCU spec 8.4 */
				Luint32 u32PodFrontTargetXPosition_mm;

				/** Byte 12: Number of setpoints of braking curve for this run.
				 * Not sure of the max. Using 100 as an example.
				 * Can't be greater than C_FCTL_TRACKDB__MAX_SETPOINTS*/
				Luint32 u32NumberOfStripes;

				/** Bytes 13-112: List of braking setpoints' x position */
				Luint32 u32BrakingSetPointXPosition_mm[C_FCTL_TRACKDB__MAX_SETPOINTS];

				/** Bytes 113-212: List of braking setpoints' speed */
				Luint32 u32BrakingSetPointSpeed_mms[C_FCTL_TRACKDB__MAX_SETPOINTS];

				/** Spare Data */
				Luint32 u32SpareData[C_FCTL_TRACKDB__PROFILE_SPARE_WORDS];

				/** Quick footer check */
				Luint32 u32Footer;

			}sRunProfile;

			/** The CRC for this entire packet
			 * Only 16bit CRC */
			Luint16 u16CRC;

		}sDB;

	};







#endif /* _FCU__FCTL__TRACK_DATABASE__TYPES_H_ */
