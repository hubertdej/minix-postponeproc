#include "kernel/system.h"

static void unset_flag(timer_t *tp);

/*===========================================================================*
 *				do_postpone				     *
 *===========================================================================*/
int do_postpone(struct proc *caller, message *m_ptr) {
  endpoint_t endpoint = m_ptr->m1_i1;
  int ticks = m_ptr->m1_i2;

  proc_nr_t proc_nr;
  if (!isokendpt(endpoint, &proc_nr)) {
    return EINVAL;
  }
  if (iskerneln(proc_nr)) {
    return EPERM;
  }

  struct proc *rp = proc_addr(proc_nr);
  if (isemptyp(rp)) {
    return EINVAL;
  }

  if (ticks != TMR_NEVER) {
    ticks += get_uptime();
  }

  timer_t *tp = &(rp->p_timer);
  tp->tmr_exp_time = ticks;
  tp->tmr_func = unset_flag;
  tmr_arg(tp)->ta_int = proc_nr;

  RTS_SET(rp, RTS_POSTPONED);
  set_timer(tp, tp->tmr_exp_time, tp->tmr_func);

  return OK;
}

/*===========================================================================*
 *				unset_flag				     *
 *===========================================================================*/
static void unset_flag(timer_t *tp) {
  proc_nr_t proc_nr = tmr_arg(tp)->ta_int;

  struct proc *rp = proc_addr(proc_nr);
  if (isemptyp(rp)) {
    return;
  }

  RTS_UNSET(rp, RTS_POSTPONED);
}
