
#define PID_MAX_VALUE 12000
#define PID_MIN_VALUE -12000

typedef struct
{
	double e,_e,__e;
	long u;
	long u_delta;
	double dt;
	double itg,er_delta;
	double kp,ki,kd;
	double k1,k2,k3;
}pid_type;

extern void PID_init(pid_type * ut);
extern unsigned long  PID_Compute_Descrete(double err);
extern unsigned long PID_Compute_Continuous(double error,double t_delta);
extern void PID_set_maxmin(unsigned long max , unsigned long min);
extern void PID_update(pid_type p);