#ifndef P3220103_P3220172_PIZZA_H
#define P3220103_P3220172_PIZZA_H

#include <pthread.h>

#define Ntel 2
#define Ncook 2
#define Noven 10
#define Ndeliverer 10
#define Torderlow 1
#define Torderhigh 5
#define Norderlow 1
#define Norderhigh 5
#define Pm 0.35
#define Pp 0.25
#define Ps 0.40
#define Tpaymentlow 1
#define Tpaymenthigh 3
#define Pfail 0.05
#define Cm 10
#define Cp 11
#define Cs 12
#define Tprep 1
#define Tbake 10
#define Tpack 1
#define Tdellow 5
#define Tdelhigh 15

// Global variables for resources
extern int available_phones, available_cooks, available_ovens, available_deliverers;

// Mutexes and Condition Variables
extern pthread_mutex_t mutex_phones, mutex_cooks, mutex_ovens, mutex_deliverers, mutex_stats;
extern pthread_cond_t cond_phones, cond_cooks, cond_ovens, cond_deliverers, cond_stats;

void *process_order(void *arg);

#endif // PIZZA_SYSTEM_H
