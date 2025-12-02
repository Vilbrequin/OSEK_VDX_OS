/***********************************************************************************************
 * File Name        : os.h
 * Description      : Os initialisation logic, Os globals, internal helpers no scheduling here
 * Date             : 30 Nov 2025
 * Author           : Houssame ELBIADE
 ***********************************************************************************************/
#ifndef OS_H_
#define OS_H_

/***********************************************************************************************
 *                                          INCLUDES
 ***********************************************************************************************/
#include "os_types.h"
#include "os_cfg.h"

/***********************************************************************************************
 *                                     PRE-PROCESSOR MACROS
 ***********************************************************************************************/
#define SET_READY(bitmap, priority)             (bitmap |= (1 << priority))
#define CLEAR_READY(bitmap, priority)           (bitmap &= ~(1 << priority))


/***********************************************************************************************
 *                                        PUBLIC ENUMS
 ***********************************************************************************************/
typedef enum TaskStateType {
    SUSPENDED = 0x00,
    READY,
    RUNNING
} TaskStateType;

typedef enum StatusType {
    E_OK = 0x00,
    E_OS_ACCESS,
    E_OS_CALLEVEL,
    E_OS_ID,
    E_OS_LIMIT,  
    E_OS_NOFUNC,  
    E_OS_RESOURCE, 
    E_OS_STATE,  
    E_OS_VALUE
} StatusType;

/***********************************************************************************************
 *                                        PRIVATE TYPES
 ***********************************************************************************************/
typedef os_uint8_t OsPriorityType;

typedef void (*os_entry_point)(void);

/***********************************************************************************************
 *                                        PUBLIC TYPES
 ***********************************************************************************************/
typedef TaskStateType* TaskStateRefType;

typedef struct TaskType
{
    os_uint8_t task_id;
    OsPriorityType priority;
    os_entry_point entry_point;
    TaskStateType state;

    os_uin32_t* task_sp; // current saved stack pointer
    os_uin32_t* task_stack_base; // base address of the task's stack frame
    os_uin32_t task_stack_budget; // in bytes
} TaskType;

typedef TaskType* TaskRefType;


/***********************************************************************************************
 *                                        OS GLOBALS
 ***********************************************************************************************/
extern os_uin32_t readyBitMap; // TODO : need 2 Macros SET_READY, CLEAR_READY in os_kerne.c
extern TaskRefType RunningTask;
extern TaskType TasksTab[OS_NUM_TASKS];

/***********************************************************************************************
 *                                        PUBLIC SERVICES
 ***********************************************************************************************/
StatusType ActivateTask ( TaskType TaskID );
StatusType TerminateTask ( void );
StatusType ChainTask ( TaskType TaskID );
StatusType Schedule ( void );
StatusType GetTaskID ( TaskRefType TaskID );
StatusType GetTaskState ( TaskType TaskID,  TaskStateRefType State );

/***********************************************************************************************
 *                                       PRIVATE SERVICES
 ***********************************************************************************************/
void Os_Dispatch(void);

#endif /* OS_H_ */