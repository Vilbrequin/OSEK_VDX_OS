/***********************************************************************************************
 * File Name        : os_types.h
 * Description      : Os types - as obvious as it is :)
 * Date             : 30 Nov 2025
 * Author           : Houssame ELBIADE
 ***********************************************************************************************/
#ifndef OS_TYPES_
#define OS_TYPES_


typedef unsigned char os_uint8_t;

typedef unsigned long os_uin32_t;

typedef os_uint8_t OsPriorityType;

typedef void (*os_entry_point)(void);

typedef unsigned long os_bool;

#define FALSE   0x00
#define TRUE    0x01

#define NULL    ((void*)0)

#endif