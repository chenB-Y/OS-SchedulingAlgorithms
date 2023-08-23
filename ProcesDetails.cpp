#include "ProcesDetails.h"
int ProcesDetails:: getArrival() {
	return this->arrivalTime;
}
int ProcesDetails:: getComputation() {
	return this->computationTime;
}
bool ProcesDetails:: getFlag() {
	return this->flag;
}
int ProcesDetails::getCurrent() {
	return this->currentTime;
}
void ProcesDetails:: setArrival(int _a) {
	this->arrivalTime = _a;
}
void ProcesDetails:: setComputation(int _c) {
	this->computationTime = _c;
}
void ProcesDetails:: setFlag(bool _f) {
	this->flag = _f;
}
void ProcesDetails:: setCurrent(int _c) {
	this->currentTime = _c;
}

void ProcesDetails:: printProcess() {
	cout << "arrivalTime is: " << this->arrivalTime << "  computationTime is: " << this->computationTime << endl;
}
