
/***********************************************************************************************
 * File Name        : os_kernel.c
 * Description      : Os configuration file it manually implemented just for the first version 
 *                    later it will be generated from OIL configuration file
 * Date             : 30 Nov 2025
 * Author           : Houssame ELBIADE
 ***********************************************************************************************/

#ifndef OS_CFG_
#define OS_CFG_

#include "os_types.h"

#define OS_NUM_TASKS    0x04

typedef struct 
{
    os_entry_point entry;
    OsPriorityType priority;
    os_uint8_t autosart_mask; // bu app mode bit 0 -> app mode 0 and so on ...
    os_uin32_t* task_stack_base; // base address of the task's stack frame
    os_uin32_t task_stack_budget; // in bytes
} Os_TaskConfigType;

extern Os_TaskConfigType TaskConfigTab[OS_NUM_TASKS];

#endif /* OS_CFG_ */