/**
 * @file		rm4_emac__bd_private.h
 * @brief		Private block descriptor defines.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM254R0.FILE.003
 */

#ifndef RM4_EMAC__BD_PRIVATE_H_
#define RM4_EMAC__BD_PRIVATE_H_

	/* Packet Flags */
	#define EMAC_DSC_FLAG_SOP 0x80000000u
	#define EMAC_DSC_FLAG_EOP 0x40000000u
	#define EMAC_DSC_FLAG_OWNER 0x20000000u
	#define EMAC_DSC_FLAG_EOQ 0x10000000u
	#define EMAC_DSC_FLAG_TDOWNCMPLT 0x08000000u
	#define EMAC_DSC_FLAG_PASSCRC 0x04000000u
	#define EMAC_DSC_FLAG_JABBER 0x02000000u
	#define EMAC_DSC_FLAG_OVERSIZE 0x01000000u
	#define EMAC_DSC_FLAG_FRAGMENT 0x00800000u
	#define EMAC_DSC_FLAG_UNDERSIZED 0x00400000u
	#define EMAC_DSC_FLAG_CONTROL 0x00200000u
	#define EMAC_DSC_FLAG_OVERRUN 0x00100000u
	#define EMAC_DSC_FLAG_CODEERROR 0x00080000u
	#define EMAC_DSC_FLAG_ALIGNERROR 0x00040000u
	#define EMAC_DSC_FLAG_CRCERROR 0x00020000u
	#define EMAC_DSC_FLAG_NOMATCH 0x00010000u

/*
EMAC TX Buffer descriptor data structure


*/
struct RM4_EMAC__TX_BD_T
{

	/*
	28.2.6.4.1 Next Descriptor Pointer
	The pNextBlockDescriptor descriptor pointer points to the 32-bit word aligned memory address of the pNextBlockDescriptor buffer descriptor
	in the transmit queue. This pointer is used to create a linked list of buffer descriptors. If the value of this
	pointer is zero, then the current buffer is the last buffer in the queue. The software application must set
	this value prior to adding the descriptor to the active transmit list. This pointer is not altered by the EMAC.
	The value of pNextBlockDescriptor should never be altered once the descriptor is in an active transmit queue, unless its
	current value is NULL. If the pNextBlockDescriptor pointer is initially NULL, and more packets need to be queued for
	transmit, the software application may alter this pointer to point to a newly appended descriptor. The
	EMAC will use the new pointer value and proceed to the pNextBlockDescriptor descriptor unless the pNextBlockDescriptor value has
	already been read. In this latter case, the transmitter will halt on the transmit channel in question, and the
	software application may restart it at that time. The software can detect this case by checking for an end
	of queue (EOQ) condition flag on the updated packet descriptor when it is returned by the EMAC.
	 */
	volatile struct RM4_EMAC__TX_BD_T * pNextBlockDescriptor;

	/*
	28.2.6.4.2 Buffer Pointer
	The buffer pointer is the byte-aligned memory address of the memory buffer associated with the buffer
	descriptor. The software application must set this value prior to adding the descriptor to the active transmit
	list. This pointer is not altered by the EMAC.
	*/
	volatile Luint32 pu32Buffer;

	/*
	28.2.6.4.3 Buffer Offset
	This 16-bit field indicates how many unused bytes are at the start of the buffer. For example, a value of
	0000h indicates that no unused bytes are at the start of the buffer and that valid data begins on the first
	byte of the buffer, while a value of 000Fh indicates that the first 15 bytes of the buffer are to be ignored by
	the EMAC and that valid buffer data starts on byte 16 of the buffer. The software application must set this
	value prior to adding the descriptor to the active transmit list. This field is not altered by the EMAC.
	Note that this value is only checked on the first descriptor of a given packet (where the start of packet
	(SOP) flag is set). It can not be used to specify the offset of subsequent packet fragments. Also, since the
	buffer pointer may point to any byte�aligned address, this field may be entirely superfluous, depending on
	the device driver architecture.
	The range of legal values for this field is 0 to (Buffer Length � 1).

	28.2.6.4.4 Buffer Length
	This 16-bit field indicates how many valid data bytes are in the buffer. On single fragment packets, this
	value is also the total length of the packet data to be transmitted. If the buffer offset field is used, the offset
	bytes are not counted as part of this length. This length counts only valid data bytes. The software
	application must set this value prior to adding the descriptor to the active transmit list. This field is not
	altered by the EMAC.
	 */
	volatile Luint32 u16BufferOffset__u16BufferLength;


	/*
	28.2.6.4.5 Packet Length
	This 16-bit field specifies the number of data bytes in the entire packet. Any leading buffer offset bytes are
	not included. The sum of the buffer length fields of each of the packet�s fragments (if more than one) must
	be equal to the packet length. The software application must set this value prior to adding the descriptor to
	the active transmit list. This field is not altered by the EMAC. This value is only checked on the first
	descriptor of a given packet (where the start of packet (SOP) flag is set).

	28.2.6.4.6 Start of Packet (SOP) Flag
	When set, this flag indicates that the descriptor points to a packet buffer that is the start of a new packet.
	In the case of a single fragment packet, both the SOP and end of packet (EOP) flags are set. Otherwise,
	the descriptor pointing to the last packet buffer for the packet sets the EOP flag. This bit is set by the
	software application and is not altered by the EMAC.

	28.2.6.4.7 End of Packet (EOP) Flag
	When set, this flag indicates that the descriptor points to a packet buffer that is last for a given packet. In
	the case of a single fragment packet, both the start of packet (SOP) and EOP flags are set. Otherwise, the
	descriptor pointing to the last packet buffer for the packet sets the EOP flag. This bit is set by the software
	application and is not altered by the EMAC.

	28.2.6.4.8 Ownership (OWNER) Flag
	When set, this flag indicates that all the descriptors for the given packet (from SOP to EOP) are currently
	owned by the EMAC. This flag is set by the software application on the SOP packet descriptor before
	adding the descriptor to the transmit descriptor queue. For a single fragment packet, the SOP, EOP, and
	OWNER flags are all set. The OWNER flag is cleared by the EMAC once it is finished with all the
	descriptors for the given packet. Note that this flag is valid on SOP descriptors only.

	28.2.6.4.9 End of Queue (EOQ) Flag
	When set, this flag indicates that the descriptor in question was the last descriptor in the transmit queue
	for a given transmit channel, and that the transmitter has halted. This flag is initially cleared by the
	software application prior to adding the descriptor to the transmit queue. This bit is set by the EMAC when
	the EMAC identifies that a descriptor is the last for a given packet (the EOP flag is set), and there are no
	more descriptors in the transmit list (pNextBlockDescriptor descriptor pointer is NULL).
	The software application can use this bit to detect when the EMAC transmitter for the corresponding
	channel has halted. This is useful when the application appends additional packet descriptors to a transmit
	queue list that is already owned by the EMAC. Note that this flag is valid on EOP descriptors only.
	28.2.6.4.10 Teardown Complete (TDOWNCMPLT) Flag
	This flag is used when a transmit queue is being torn down, or aborted, instead of allowing it to be
	transmitted. This would happen under device driver reset or shutdown conditions. The EMAC sets this bit
	in the SOP descriptor of each packet as it is aborted from transmission.
	Note that this flag is valid on SOP descriptors only. Also note that only the first packet in an unsent list has
	the TDOWNCMPLT flag set. Subsequent descriptors are not processed by the EMAC.

	28.2.6.4.11 Pass CRC (PASSCRC) Flag
	This flag is set by the software application in the SOP packet descriptor before it adds the descriptor to the
	transmit queue. Setting this bit indicates to the EMAC that the 4 byte Ethernet CRC is already present in
	the packet data, and that the EMAC should not generate its own version of the CRC.
	When the CRC flag is cleared, the EMAC generates and appends the 4-byte CRC. The buffer length and
	packet length fields do not include the CRC bytes. When the CRC flag is set, the 4-byte CRC is supplied
	by the software application and is already appended to the end of the packet data. The buffer length and
	packet length fields include the CRC bytes, as they are part of the valid packet data. Note that this flag is
	valid on SOP descriptors only.
	*/
	volatile Luint32 u16Flags__u16PacketLength;

	#if C_LOCALDEF__LCCM254__USE_WITH_LWIP == 1U
		/* helper to know which pbuf this tx bd corresponds to */
		volatile struct pbuf *pLWIPBuf;
	#endif
};

/*
EMAC RX Buffer descriptor data structure
28.2.6.5 Receive Buffer Descriptor Format
A receive (RX) buffer descriptor (Figure 28-8) is a contiguous block of four 32-bit data words aligned on a
32-bit boundary that describes a packet or a packet fragment. Example 28-2 shows the receive buffer
descriptor described by a C structure
*/
struct RM4_EMAC__RX_BD_T
{
	/*
	28.2.6.5.1 Next Descriptor Pointer
	This pointer points to the 32�bit word aligned memory address of the pNextBlockDescriptor buffer descriptor in the receive
	queue. This pointer is used to create a linked list of buffer descriptors. If the value of this pointer is zero,
	then the current buffer is the last buffer in the queue. The software application must set this value prior to
	adding the descriptor to the active receive list. This pointer is not altered by the EMAC.
	The value of pNextBlockDescriptor should never be altered once the descriptor is in an active receive queue, unless its
	current value is NULL. If the pNextBlockDescriptor pointer is initially NULL, and more empty buffers can be added to the
	pool, the software application may alter this pointer to point to a newly appended descriptor. The EMAC
	will use the new pointer value and proceed to the pNextBlockDescriptor descriptor unless the pNextBlockDescriptor value has already been
	read. In this latter case, the receiver will halt the receive channel in question, and the software application
	may restart it at that time. The software can detect this case by checking for an end of queue (EOQ)
	condition flag on the updated packet descriptor when it is returned by the EMAC.
	 */
	volatile struct RM4_EMAC__RX_BD_T * pNextBlockDescriptor;

	/*
	28.2.6.5.2 Buffer Pointer
	The buffer pointer is the byte-aligned memory address of the memory buffer associated with the buffer
	descriptor. The software application must set this
	*/
	volatile Luint32 pu32Buffer;

	/*
	28.2.6.5.3 Buffer Offset
	This 16-bit field must be initialized to zero by the software application before adding the descriptor to a
	receive queue.
	Whether or not this field is updated depends on the setting of the RXBUFFEROFFSET register. When the
	offset register is set to a non-zero value, the received packet is written to the packet buffer at an offset
	given by the value of the register, and this value is also written to the buffer offset field of the descriptor.
	When a packet is fragmented over multiple buffers because it does not fit in the first buffer supplied, the
	buffer offset only applies to the first buffer in the list, which is where the start of packet (SOP) flag is set in
	the corresponding buffer descriptor. In other words, the buffer offset field is only updated by the EMAC on
	SOP descriptors.
	The range of legal values for the BUFFEROFFSET register is 0 to (Buffer Length � 1) for the smallest
	value of buffer length for all descriptors in the list.

	28.2.6.5.4 Buffer Length
	This 16-bit field is used for two purposes:
	� Before the descriptor is first placed on the receive queue by the application software, the buffer length
	field is first initialized by the software to have the physical size of the empty data buffer pointed to by
	the buffer pointer field.
	� After the empty buffer has been processed by the EMAC and filled with received data bytes, the buffer
	length field is updated by the EMAC to reflect the actual number of valid data bytes written to the
	buffer.

	 */
	volatile Luint32 u16BufferOffset__u16BufferLength;

	/*
	28.2.6.5.5 Packet Length
	This 16-bit field specifies the number of data bytes in the entire packet. This value is initialized to zero by
	the software application for empty packet buffers. The value is filled in by the EMAC on the first buffer
	used for a given packet. This is signified by the EMAC setting a start of packet (SOP) flag. The packet
	length is set by the EMAC on all SOP buffer descriptors.

	28.2.6.5.6 Start of Packet (SOP) Flag
	When set, this flag indicates that the descriptor points to a packet buffer that is the start of a new packet.
	In the case of a single fragment packet, both the SOP and end of packet (EOP) flags are set. Otherwise,
	the descriptor pointing to the last packet buffer for the packet has the EOP flag set. This flag is initially
	cleared by the software application before adding the descriptor to the receive queue. This bit is set by the
	EMAC on SOP descriptors.

	28.2.6.5.7 End of Packet (EOP) Flag
	When set, this flag indicates that the descriptor points to a packet buffer that is last for a given packet. In
	the case of a single fragment packet, both the start of packet (SOP) and EOP flags are set. Otherwise, the
	descriptor pointing to the last packet buffer for the packet has the EOP flag set. This flag is initially cleared
	by the software application before adding the descriptor to the receive queue. This bit is set by the EMAC
	on EOP descriptors.

	28.2.6.5.8 Ownership (OWNER) Flag
	When set, this flag indicates that the descriptor is currently owned by the EMAC. This flag is set by the
	software application before adding the descriptor to the receive descriptor queue. This flag is cleared by
	the EMAC once it is finished with a given set of descriptors, associated with a received packet. The flag is
	updated by the EMAC on SOP descriptor only. So when the application identifies that the OWNER flag is
	cleared on an SOP descriptor, it may assume that all descriptors up to and including the first with the EOP
	flag set have been released by the EMAC. (Note that in the case of single buffer packets, the same
	descriptor will have both the SOP and EOP flags set.)

	28.2.6.5.9 End of Queue (EOQ) Flag
	When set, this flag indicates that the descriptor in question was the last descriptor in the receive queue for
	a given receive channel, and that the corresponding receiver channel has halted. This flag is initially
	cleared by the software application prior to adding the descriptor to the receive queue. This bit is set by
	the EMAC when the EMAC identifies that a descriptor is the last for a given packet received (also sets the
	EOP flag), and there are no more descriptors in the receive list (pNextBlockDescriptor descriptor pointer is NULL).
	The software application can use this bit to detect when the EMAC receiver for the corresponding channel
	has halted. This is useful when the application appends additional free buffer descriptors to an active
	receive queue. Note that this flag is valid on EOP descriptors only.

	28.2.6.5.10 Teardown Complete (TDOWNCMPLT) Flag
	This flag is used when a receive queue is being torn down, or aborted, instead of being filled with received
	data. This would happen under device driver reset or shutdown conditions. The EMAC sets this bit in the
	descriptor of the first free buffer when the tear down occurs. No additional queue processing is performed

	28.2.6.5.11 Pass CRC (PASSCRC) Flag
	This flag is set by the EMAC in the SOP buffer descriptor if the received packet includes the 4-byte CRC.
	This flag should be cleared by the software application before submitting the descriptor to the receive
	queue.

	28.2.6.5.12 Jabber Flag
	This flag is set by the EMAC in the SOP buffer descriptor, if the received packet is a jabber frame and was
	not discarded because the RXCEFEN bit was set in the RXMBPENABLE. Jabber frames are frames that
	exceed the RXMAXLEN in length, and have CRC, code, or alignment errors.

	28.2.6.5.13 Oversize Flag
	This flag is set by the EMAC in the SOP buffer descriptor, if the received packet is an oversized frame and
	was not discarded because the RXCEFEN bit was set in the RXMBPENABLE.

	28.2.6.5.14 Fragment Flag
	This flag is set by the EMAC in the SOP buffer descriptor, if the received packet is only a packet fragment
	and was not discarded because the RXCEFEN bit was set in the RXMBPENABLE.

	28.2.6.5.15 Undersized Flag
	This flag is set by the EMAC in the SOP buffer descriptor, if the received packet is undersized and was
	not discarded because the RXCSFEN bit was set in the RXMBPENABLE.
	28.2.6.5.16 Control Flag
	This flag is set by the EMAC in the SOP buffer descriptor, if the received packet is an EMAC control frame
	and was not discarded because the RXCMFEN bit was set in the RXMBPENABLE.

	28.2.6.5.17 Overrun Flag
	This flag is set by the EMAC in the SOP buffer descriptor, if the received packet was aborted due to a
	receive overrun.

	28.2.6.5.18 Code Error (CODEERROR) Flag
	This flag is set by the EMAC in the SOP buffer descriptor, if the received packet contained a code error
	and was not discarded because the RXCEFEN bit was set in the RXMBPENABLE.

	28.2.6.5.19 Alignment Error (ALIGNERROR) Flag
	This flag is set by the EMAC in the SOP buffer descriptor, if the received packet contained an alignment
	error and was not discarded because the RXCEFEN bit was set in the RXMBPENABLE.

	28.2.6.5.20 CRC Error (CRCERROR) Flag
	This flag is set by the EMAC in the SOP buffer descriptor, if the received packet contained a CRC error
	and was not discarded because the RXCEFEN bit was set in the RXMBPENABLE.

	28.2.6.5.21 No Match (NOMATCH) Flag
	This flag is set by the EMAC in the SOP buffer descriptor, if the received packet did not pass any of the
	EMAC�s address match criteria and was not discarded because the RXCAFEN bit was set in the
	RXMBPENABLE. Although the packet is a valid Ethernet data packet, it was only received because the
	EMAC is in promiscuous mode.
	 */
	volatile Luint32 u16Flags__u16PacketLength;

	#if C_LOCALDEF__LCCM254__USE_WITH_LWIP == 1U
		/* helper to know which pbuf this rx bd corresponds to */
		//for LWIP USE
		volatile struct pbuf *pLWIPBuf;
	#endif
};

/**
 * Helper struct to hold the data used to operate on a particular
 * receive channel
 */
struct RM4_EMAC__RX_CHANNEL_T
{
	volatile struct RM4_EMAC__RX_BD_T * pFreeHeadBD;
	volatile struct RM4_EMAC__RX_BD_T * pHeadDescriptor;
	volatile struct RM4_EMAC__RX_BD_T * pActiveTailBD;

	#if C_LOCALDEF__LCCM254__USE_WITH_LWIP == 1U
		Luint32 freed_pbuf_len;
	#endif
};

/**
 * Helper struct to hold the data used to operate on a particular
 * transmit channel
 */
struct RM4_EMAC__TX_CHANNEL_T
{
	volatile struct RM4_EMAC__TX_BD_T * pHeadDescriptor;
	volatile struct RM4_EMAC__TX_BD_T * pActiveTailBD;
	volatile struct RM4_EMAC__TX_BD_T * pNextBD_ToProcess;
};


#endif /* RM4_EMAC__BD_PRIVATE_H_ */
