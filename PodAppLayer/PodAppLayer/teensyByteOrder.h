#ifndef BYTE_ORDER_H
#define BYTE_ORDER_H

#define htons(x) ( ((x)<<8) | (((x)>>8)&0xFF) )
#define ntohs(x) htons(x)

#define htonl(x) ( ((x)<<24 & 0xFF000000) | \
                   ((x)<< 8 & 0x00FF0000) | \
                   ((x)>> 8 & 0x0000FF00) | \
                   ((x)>>24 & 0x000000FF) )
#define ntohl(x) htonl(x)

#define be64toh(x) ( ((x) <<56 & 0xFF00000000000000) | \
                     ((x) <<40 & 0x00FF000000000000) | \
				     ((x) <<24 & 0x0000FF0000000000) | \
				     ((x) <<8 &  0x000000FF00000000) | \
					 ((x) >> 8 & 0x00000000FF000000) | \
					 ((x) >> 24 &0x0000000000FF0000) | \
					 ((x) >> 40 &0x000000000000FF00) | \
					 ((x) >> 56 &0x00000000000000FF) )
#define ntoh(x) be64toh(x)

#endif

