#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
class ProcesDetails
{
private:
	int arrivalTime;
	int computationTime; 
	bool flag; // 1 = not finish, 0 =finish 
	int currentTime; // amount of unit tine the process done already
public:
	ProcesDetails(int _start, int _need){
		this->arrivalTime = _start;
		this->computationTime = _need;
		this->flag = 1;
		this->currentTime = _need;
	}
	ProcesDetails(){ }
	~ProcesDetails(){ }
	int getArrival();
	int getComputation();
	bool getFlag();
	int getCurrent();
	void setArrival(int _a);
	void setComputation(int _c);
	void setFlag(bool _f);
	void setCurrent(int _c);
	void printProcess();
};

