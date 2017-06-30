#ifndef __WORKQUEUE_H_
#define __WORKQUEUE_H_

#include "PSPMconfigure.h"
#include "PSPMport.h"

// called by interrupt upper part
void prv_work_initialize();

int prv_work_is_null();

void prv_work_triggering();

void prv_work_add(prv_id_t sid, void *data);

prv_work_t prv_work_pop();

#endif
