#include "syslib.h"

int sys_postpone(endpoint_t endpoint, int ticks) {
  message m;
  m.m1_i1 = endpoint;
  m.m1_i2 = ticks;
  return _kernel_call(SYS_POSTPONE, &m);
}
