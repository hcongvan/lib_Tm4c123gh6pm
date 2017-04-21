#include "pid.h"

pid_type * pid;
void PID_init(pid_type * ut)
{
	pid = ut;
	pid->kp = 0.3;
	pid->ki = 0.2;
	pid->kd = 0.1;
	pid->k1 = pid->kp + pid->ki + pid->kd;
	pid->k2 = -(pid->kp) - 2*(pid->kd);
	pid->k3 = pid->kd;
	
}
unsigned long  PID_Compute_Descrete(double err)
{
	pid->__e = pid->_e;
	pid->_e = pid->e;
	pid->e = err;
	pid->u_delta = (pid->k1)*(pid->e) + (pid->k2)*(pid->_e) + (pid->k3)*(pid->__e);
	if((pid->u_delta) != 0)
		pid->u =  pid->u + pid->u_delta;
	else 
		pid->u = 0;
	if((pid->u) > PID_MAX_VALUE) pid->u = PID_MAX_VALUE;
	if((pid->u) < PID_MIN_VALUE) pid->u = PID_MIN_VALUE;
	return (long)pid->u;
}
unsigned long PID_Compute_Continuous(double error,double t_delta)
{
	pid->_e = pid->e;
	pid->e = error;
	pid->er_delta = pid->e - pid->_e;
	pid->dt = t_delta;
	pid->itg = pid->itg +pid->er_delta;
	pid->u = (pid->kp)*(pid->e) + ((pid->ki)*(pid->itg)*(pid->dt)) + ((pid->kd)*(pid->er_delta)/(pid->dt));
	if((pid->u) > PID_MAX_VALUE) pid->u = PID_MAX_VALUE;
	if((pid->u) < PID_MIN_VALUE) pid->u = PID_MIN_VALUE;
	return (long)pid->u;
}
void PID_set_maxmin(unsigned long max , unsigned long min)
{
	#ifdef PID_MAX_VALUE
	#undef PID_MAX_VALUE
	#define PID_MAX_VALUE max
	#endif
	#ifdef PID_MIN_VALUE
	#undef PID_MIN_VALUE
	#define PID_MIN_VALUE min
	#endif	
}
void PID_update(pid_type p)
{
	pid->ki = p.ki;
	pid->kp = p.kp;
	pid->kd = p.kd;
	pid->k1 = pid->ki + pid->kp + pid->kd ;
	pid->k2 = -(pid->kp) - 2*(pid->ki);
	pid->k3 = pid->kd;
	
}	