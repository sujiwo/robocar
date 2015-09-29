#ifndef __PTIME_H__
#define __PTIME_H__ 

// for measurement
#define CPU_CLOCK_PER_USEC 500.0 //[MHz]=[clock/usec]
#define CPU_USEC_PER_CLOCK 0.002 //[usec/clock]

inline unsigned long long int rdtsc(void)
{
        unsigned long long int x;
        __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
        return x;
}

inline double ptime()
{
        static long long prv_tclock0 = 0;
        unsigned long long tclock0 = rdtsc();
        double time_usec = ((tclock0 - prv_tclock0) * CPU_USEC_PER_CLOCK + 0.5);
        //printf(" %6.2lf[ms]\n", time_usec / 1000.0);
        prv_tclock0 = tclock0;
        return time_usec / 1000.0;
}


#endif


