#include <lib.h>
#include <minix/postpone.h>

int stop_proc(pid_t pid) {
  return postpone_proc(pid, -1);
}

int resume_proc(pid_t pid) {
  return postpone_proc(pid, 0);
}

int postpone_proc(pid_t pid, int interval) {
  message m;
  m.m1_i1 = pid;
  m.m1_i2 = interval;
  return _syscall(PM_PROC_NR, POSTPONE, &m);
}
