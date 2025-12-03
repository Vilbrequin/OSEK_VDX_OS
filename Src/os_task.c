/***********************************************************************************************
 * File Name        : os_task.c
 * Description      : OSEK Task Management Services
 * Date             : 30 Nov 2025
 * Author           : Houssame ELBIADE
 ***********************************************************************************************/

/***********************************************************************************************
 *                                          INCLUDES
 ***********************************************************************************************/
#include "os.h"

StatusType ActivateTask(TaskType TaskID)
{
    if (TaskID.task_id >= OS_NUM_TASKS)
    {
        return E_OS_ID;
    }

    TaskType *task = &TasksTab[TaskID.task_id];

    if (SUSPENDED == task->state)
    {
        task->state = READY;

        SET_READY(readyBitMap, task->priority);

        task->task_sp = task->task_init_sp;

        Os_Dispatch(); // call the scheduler

        return E_OK;
    }
    else
    {
        return E_OS_LIMIT;
    }
}

StatusType TerminateTask(void)
{
    TaskType *task = &TasksTab[RunningTask->task_id];

    task->state = SUSPENDED;

    CLEAR_READY(readyBitMap, task->priority);

    RunningTask = NULL;

    Os_Dispatch();

    /* Unrechable after the scheduler is called !!*/
    return E_OK;
}

StatusType ChainTask(TaskType TaskID)
{
    if (TaskID.task_id >= OS_NUM_TASKS)
    {
        return E_OS_ID;
    }

    TaskType *succ = &TasksTab[TaskID.task_id];
    TaskType* curr = RunningTask;

    // before terminating and activating any tasks we must check successor feasibility fisrt 
    if ((succ != curr) && (succ->state != SUSPENDED)){
        return E_OS_LIMIT;
    }
    // Safely terminate the current running task
    RunningTask->state = SUSPENDED;

    CLEAR_READY(readyBitMap, RunningTask->priority);

    RunningTask = NULL;
    
    // Activate the successor task to the ready state, in case of curr == succ the state is already Suspendend and it'
    // now ready 
    succ->state = READY;

    succ->task_sp = succ->task_init_sp;

    SET_READY(readyBitMap, succ->priority);

    Os_Dispatch();

    return E_OK;
}