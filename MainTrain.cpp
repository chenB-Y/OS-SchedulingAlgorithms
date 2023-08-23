// חן חזיזה 319027892
//שחר נעים 318685807
#include "ProcesDetails.h"
#include "Util.h"
void main()
{
	int i =0,numOfPrcs =0, arrivalTime, computationTime;
	char c;
	ifstream file;
	file.open("input1.txt");
	file >> numOfPrcs;
	ProcesDetails* process = new ProcesDetails[numOfPrcs];
	cout << "num of process is:  " << numOfPrcs << endl;
	while (file >> arrivalTime >> c >> computationTime)
	{
		process[i] = ProcesDetails(arrivalTime, computationTime);
		i++;
	}
	file.close();
	for (int j = 0; j < numOfPrcs; j++) {
		cout << "The details of process number " << j+1 << " is: ";
		process[j].printProcess();
	}
	ProcesDetails* p = new ProcesDetails[numOfPrcs];
	dupTheArr(numOfPrcs, process, p);
	cout << "FCFS: mean turnaround = " << avgTT_fcfs(numOfPrcs, p) << endl;
	dupTheArr(numOfPrcs, process, p);
	cout << "LCFS (NP): mean turnaround = " << avgTT_lcfs_nonpreemptive(numOfPrcs, p) << endl;
	dupTheArr(numOfPrcs, process, p);
	cout << "LCFS (P): mean turnaround = " << avgTT_lcfs_preemptive(numOfPrcs, p) << endl;
	dupTheArr(numOfPrcs, process, p);
	cout << "RR: mean turnaround = " << avgTT_RR(numOfPrcs, p) << endl;;
	dupTheArr(numOfPrcs, process, p);
	cout <<"SJF: mean turnaround = " << avgTT_sjf_preemptive(numOfPrcs, p) << endl;
	delete[] process;
	delete[] p;
}