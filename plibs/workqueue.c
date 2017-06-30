#include "workqueue.h"


port_semph_t sem_wq; //  the semaphore for trigging work thread
prv_list_t workqueue; // the ready list of aperiodic Servant
extern ps_servant_t servants[NUMOFSERVANTS];




static void workthread()
{
	prv_work_t current_work;
	while(1){
		port_wait(sem_wq);
		while(workqueue.length){
			current_work =  prv_work_pop();
			current_work->runnable(current_work->data);
		}
		// work thread finishes all the work
	}
}

// called by system_start()
void prv_work_initialize()
{
	workqueue.length = 0;
	workqueue.first = workqueue.last = workqueue.current = NULL;
	port_semph_create(sem_wq);

	// the priority 1 set for the only work process
	port_workprocess_create(workthread, NULL, 1);
}

int prv_work_is_null()
{
	if( workqueue.length == 0 )
		return 1;
	else
		return 0;
}

void prv_work_triggering()
{
	port_trigger(sem_wq);
}

// called by the interrupt handler
void prv_work_add(prv_id_t sid, void * data)
{
	prv_work_t  work_st = (struct work *)port_malloc(sizeof(struct work));

	work_st->data = data;
	work_st->runnable = servants[sid]->runnable;

	prv_list_insert(work_st, & workqueue);
}

// called by the workqueue thread
prv_work_t prv_work_pop()
{
	prv_work_t work_st = (struct work *)prv_list_pop(&workqueue);
	return work_st;
}


