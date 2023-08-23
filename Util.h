#pragma once
#include"ProcesDetails.h"
ProcesDetails* dupTheArr(int size, ProcesDetails arr[],ProcesDetails p[]);
void sortTheProcess(int size ,ProcesDetails arr[]);
double avgTT_fcfs(int size, ProcesDetails arr[]);
double avgTT_lcfs_preemptive(int size, ProcesDetails arr[]);
double avgTT_lcfs_nonpreemptive(int size, ProcesDetails arr[]);
double avgTT_RR(int size, ProcesDetails arr[]);
double avgTT_sjf_preemptive(int size, ProcesDetails arr[]);


