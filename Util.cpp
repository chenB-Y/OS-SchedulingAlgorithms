#include "Util.h"
ProcesDetails* dupTheArr(int size , ProcesDetails arr[], ProcesDetails p[])
{
	for (int i = 0; i < size; i++)
	{
		p[i].setArrival(arr[i].getArrival());
		p[i].setComputation(arr[i].getComputation());
		p[i].setCurrent(arr[i].getCurrent());
		p[i].setFlag(arr[i].getFlag());
	}
	return p;
}
void sortTheProcess(int size,ProcesDetails arr[]) {
	for (int i = 0; i < size; i++) // bubble sort 
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j].getArrival() > arr[j + 1].getArrival())
				swap(arr[j], arr[j + 1]);
		}
	}
}
double avgTT_fcfs(int size,ProcesDetails arr[]) {
	int counter = 0, completeTime= 0;
	double turnAroundTime = 0;
	sortTheProcess(size,arr);
	for (int i = 0; i < size; i++)
	{
		if (i == 0){
			completeTime = arr[i].getArrival() + arr[i].getComputation(); // initalize complet time of process
			arr[i].setFlag(0);
			turnAroundTime += completeTime - arr[i].getArrival();
		}
		else {
			if (completeTime < arr[i].getArrival())
				completeTime = arr[i].getArrival();
			completeTime += arr[i].getComputation(); // initalize complet time of process
			arr[i].setFlag(0);
			turnAroundTime += completeTime - arr[i].getArrival();
		}
	}
	return turnAroundTime / size;
}
double avgTT_lcfs_nonpreemptive(int size, ProcesDetails arr[]) {
	sortTheProcess(size, arr);
	int completeTime, cpuTime = arr[0].getArrival(), liveProcess = size;
	double turnAroundTime = 0;
	while (liveProcess != 0)
	{
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1; j >= 0; j--)
		{
			if ((arr[j].getArrival() <= cpuTime) && (arr[j].getFlag() == 1))
			{
				if (i == 0) {
					completeTime = arr[j].getArrival() + arr[j].getComputation(); // initalize complete time of process
					arr[j].setFlag(0);
					turnAroundTime += completeTime - arr[j].getArrival();
					cpuTime = completeTime;
					liveProcess--;
					break;
				}
				else {
					if (cpuTime < arr[i].getArrival())
						completeTime += arr[i].getArrival() - cpuTime;
					completeTime += arr[j].getComputation(); // initalize complete time of process
					arr[j].setFlag(0);
					turnAroundTime += completeTime - arr[j].getArrival();
					cpuTime = completeTime;
					liveProcess--;
					break;
				}
			}
		}
	}
	if (cpuTime < arr[size - liveProcess].getArrival() && liveProcess != 0)// check if the cpu need to wait for the process to get in 
		cpuTime = arr[size - liveProcess].getArrival();
}
	return turnAroundTime / size;
}
double avgTT_lcfs_preemptive(int size, ProcesDetails arr[])
{
	sortTheProcess(size, arr);
	double turnAroundTime = 0;
	bool isFirst = true;
	int completeTime = 0 , cpuTime = 9999,temp, liveProcess =size;
	for (int i = 0; i < size; i++) {
		if (arr[i].getComputation() == 0) {
			arr[i].setFlag(0);
			liveProcess--;
		}
		else {
			if (cpuTime > arr[i].getArrival())
				cpuTime = arr[i].getArrival();
		}
	}
	for (int i = size -1;i < INFINITY;i--)
	{
		if ((arr[i].getArrival() <= cpuTime) && (arr[i].getFlag() == 1)){
			 if ((arr[i].getArrival() + arr[i].getComputation() <= arr[i + 1].getArrival() && arr[i + 1].getFlag()==1) || arr[size-1].getFlag() == 0) {
				// check if the process can run untill the end
				if (isFirst == true){
					arr[i].setFlag(0);
					cpuTime += arr[i].getComputation();
					turnAroundTime += cpuTime - arr[i].getArrival();
					isFirst = false;
					liveProcess--;
					i = size;
				}
				else{
					cpuTime += arr[i].getComputation(); // initalize complete time of process
					arr[i].setFlag(0);
					turnAroundTime += cpuTime - arr[i].getArrival();
					liveProcess--;
					i = size;
				}
			 }
			else { // the process can run only part of is commputationTime beacause other process will arrive in the middle
				if (i == size - 1)
				{
					arr[i].setFlag(0);
					cpuTime += arr[i].getComputation();
					turnAroundTime += cpuTime - arr[i].getArrival();
					liveProcess--;
					i = size;
				}
				else {
					temp = arr[i].getComputation();
					arr[i].setComputation(arr[i].getComputation() - arr[i + 1].getArrival() + arr[i].getArrival());
					cpuTime += (temp - arr[i].getComputation());
					i = size; // always chec from the end if there is newer process to run (LCFS)
				}
			}
		}
		if (liveProcess == 0)
			break;
		if (i == 0) { // we want to stay on the size of the array and we always check from the end to the begin
			i = size;
		if (cpuTime < arr[size -liveProcess].getArrival())// check if the cpu need to wait for the process to get in 
			cpuTime = arr[size - liveProcess].getArrival();
		}
	}

	return turnAroundTime / size;
}

double avgTT_RR(int size, ProcesDetails arr[]) {
	sortTheProcess(size, arr);
	int cpuTime = arr[0].getArrival() ,aliveProcess = size;
	bool newRound = true;
	double turnAroundTime = 0;
	for (int i = 0; i < INFINITY; i++)
	{
		i = (i % size);
		if ((arr[i].getArrival() <= cpuTime) && (arr[i].getFlag() == 1)) {
			//check if the process in the ready Q and it is dont finish
			if (arr[i].getComputation() <= 2 ) 
				// this is the last round of the process
			{
				cpuTime += arr[i].getComputation();
				arr[i].setComputation(0);
				arr[i].setFlag(0);
				aliveProcess--;
				turnAroundTime += (cpuTime - arr[i].getArrival());
				if (cpuTime < arr[(i+1)%size].getArrival())
					cpuTime = arr[(i + 1) % size].getArrival();
			}
			else { // computation time of the process big then 2 
				arr[i].setComputation(arr[i].getComputation() - 2);
				cpuTime += 2;
			}
		}
		if (aliveProcess == 0)
			break;
	}
	return turnAroundTime / size;
}
double avgTT_sjf_preemptive(int size, ProcesDetails arr[]) {
	sortTheProcess(size, arr);
	int cpuTime =999999;
	int aliveP = size, min, temp;
	double turnAroundTime = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i].getComputation() == 0) {
			arr[i].setFlag(0);
			aliveP--;
		}
		else {
			if (cpuTime > arr[i].getArrival())
				cpuTime = arr[i].getArrival();
		}
	}
	for (int j = 0; j < INFINITY; j++)
	{
		j = j % size;
		temp = cpuTime;
		int cpuTime_place2 = 99999, cpuTime_place1 = 99999;
		int place_1 = 0, place_2 = 0, counter = 0;
		for (int i = 0; i < size; i++){
			if ((arr[i].getArrival() <= cpuTime && arr[i].getFlag() == 1 && (arr[i].getComputation() <= cpuTime_place2 || arr[i].getComputation() <= cpuTime_place1)) 
				|| (counter < 2 && arr[i].getFlag() ==1))
			{
				cpuTime_place1 = arr[place_2].getComputation();
				place_1 = place_2;
				cpuTime_place2 = arr[i].getComputation();
				place_2 = i;
				cpuTime += abs(arr[i].getArrival() - cpuTime);
				counter++;
			}
		}
		cpuTime = temp;
		if (aliveP == 1)
			place_1 = place_2;
		if (arr[place_1].getCurrent() <= arr[place_2].getComputation() || arr[place_2].getArrival() > (cpuTime + arr[place_1].getCurrent())){
			cpuTime += arr[place_1].getCurrent();
			arr[place_1].setCurrent(0);
			arr[place_1].setFlag(0);
			aliveP--;
			turnAroundTime += (cpuTime - arr[place_1].getArrival());
		}
		else {
			arr[place_1].setCurrent(arr[place_1].getComputation() - (arr[place_2].getArrival() - cpuTime));
			cpuTime += (arr[place_2].getArrival() - cpuTime);
		}
		if (aliveP == 0)
			break;
	}
	return turnAroundTime / size;
}

