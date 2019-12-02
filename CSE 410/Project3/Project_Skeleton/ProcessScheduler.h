/*
 * File    : ProcessScheduler.h
 *
 * Header for the ProcessScheduler class for Project3.
 *
 * Class   : ProcessScheduler.h
 * Impl    : ProcessScheduler.cpp
 * Author  : CSE410 Spring 2018
 *
 * Notes   : You need to implement or add some functions in this class
 */

#ifndef PROCESSSCHEDULER_H_
#define PROCESSSCHEDULER_H_

#include <string>
#include <vector>
#include <stdlib.h>
class Process;

class ProcessScheduler
{
public:
	enum Option {NA, FCFS, SPN, SRT, HRRN, RR};
	ProcessScheduler(const int argc, const char** args);
	virtual ~ProcessScheduler();
	void Execute();
	void PrintToScreen();
	Option GetOption() const {return mOption;}

private:
	ProcessScheduler();
	void ExecuteFCFS();
	void ExecuteSPN();
	void ExecuteSRT();
	void ExecuteHRRN();
	void ExecuteRR();
	void ReadInputFile(const std::string file);
	void WriteToFile();
	void AddProcess(const std::string arrival, const std::string service);
	int GetQuantum() const {return atoi(mQuantum.c_str());}
	bool SetOption(const std::string option);
	void SortByServiceTime();
	void SortByProcessID();
	void SortByRemainingTime();
	int GetQuantum() {return atoi(mQuantum.c_str());}

	std::vector <Process*> mProcesses;
	std::string mInputFileName;
	std::string mOutputFileName;
	Option mOption;
	std::string mQuantum;
};

#endif /* PROCESSSCHEDULER_H_ */
