#ifndef _POSTPONE_H
#define _POSTPONE_H

#include <sys/types.h>

int stop_proc(pid_t);
int resume_proc(pid_t);
int postpone_proc(pid_t, int);

#endif
