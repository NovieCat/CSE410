/*
 * File: ProcessScheduler.cpp
 *
 * The class for scheduling the processes read from input file
 *
 * Header:  ProcessScheduler.h
 * Author: CSE410 Spring 2018
 *
 */

#include "ProcessScheduler.h"
#include "Process.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
using namespace std;

// options
const string sFCFS = "-FCFS";
const string sSPN = "-SPN";
const string sHRRN = "-HRRN";
const string sSRT = "-SRT";
const string sRR = "-RR";

// sort processes according to the ServiceTime increasingly
bool CompareServiceTime(Process* p1, Process* p2)
{
	if((p1->GetServiceTime()) == (p2->GetServiceTime()))
	{
		return ((p1->GetID()) < (p2->GetID()));
	}
	else
	{
		return ((p1->GetServiceTime()) < (p2->GetServiceTime()));
	}
}

// sort processes according to the Process ID increasingly
bool CompareProcessID(Process* p1, Process* p2)
{
	return ((p1->GetID()) < (p2->GetID()));
}

// sort processes according to the RemainingTime increasingly
bool CompareRemainingTime(Process* p1, Process* p2)
{
	if((p1->GetRemainingTime()) == (p2->GetRemainingTime()))
	{
		return ((p1->GetID()) < (p2->GetID()));
	}
	else
	{
		return ((p1->GetRemainingTime()) < (p2->GetRemainingTime()));
	}
}

/*
 * Name :        ProcessScheduler::ProcessScheduler()
 * Description : Constructor that takes a string (command line input) and
 *  			 an int for number of arguments as input
 */
ProcessScheduler::ProcessScheduler(const int argc, const char** args)
{
	// get file names
	mInputFileName = args[1];
	mOutputFileName = args[2];

	// get the option
	// initialize the option to NA (not available)
	mOption = NA;
	string option = args[3];
	SetOption(option);

	// if there is an argument, we store it
	if(argc > 4)
	{
		mQuantum = args[4];
	}

	// read in all the information from the file
	ReadInputFile(mInputFileName);
}

/*
 * Name :        ProcessScheduler::~ProcessScheduler()
 * Description : Default destructor
 */
ProcessScheduler::~ProcessScheduler()
{
	// clean up after ourselves
	for(unsigned int i = 0; i<mProcesses.size(); i++)
	{
		delete mProcesses[i];
	}
}

/*
 * Name :        ProcessScheduler::ReadInputFile()
 * Description : read in the process information
 * Parameters :  string of the file name
 * Returns:      void
 *
 */
void ProcessScheduler::ReadInputFile(const std::string file)
{
	ifstream inFile;

	// open the file
	inFile.open(file.c_str());

	// if the file is opened successfully
	if(inFile.is_open())
	{
		// keep reading the data from the file
		while(inFile.good())
		{
			// aTime for arrival time
			// sTime for service time
			string aTime, sTime;

			// get the data from the file
			inFile >> aTime;
			inFile >> sTime;

			if(inFile.eof())
			{
				break;
			}

			// add process to the process container
			AddProcess(aTime, sTime);
		}

		// set up ID's for processes
		if(mProcesses.size() > 0)
		{
			for(unsigned int i = 0; i<mProcesses.size(); i++)
			{
				mProcesses[i]->SetID(i+1);
			}
		}

		// close the file after using it
		inFile.close();
	}
	// if the file cannot be opened
	else
	{
		cout<<"Cannot open "<<mInputFileName<<endl;
		return;
	}
}

/*
 * Name :        ProcessScheduler::AddProcess()
 * Description : create and add a new process to the process container
 * Parameters :  arrival - the arrival time of the process
 * 				 service - the service time of the process
 * Returns:      void
 *
 */
void ProcessScheduler::AddProcess(const std::string arrival, const std::string service)
{
	// create and configure the new process according to the parameters passed in
	Process* p = new Process();
	p->SetArrivalTime(atoi(arrival.c_str()));
	p->SetServiceTime(atoi(service.c_str()));

	// store the process in the container
	mProcesses.push_back(p);
}

/*
 * Name :        ProcessScheduler::WriteToFile()
 * Description : write the scheduling result to the file
 * Parameters :  a file name for storing the result
 * Returns :     void
 * Note :        You have to implement this function
 */
void ProcessScheduler::WriteToFile()
{
	cout<<"ProcessScheduler::WriteToFile()"<<endl;
}

/*
 * Name :        ProcessScheduler::SetOption()
 * Description : set up the mOption value according to the user input
 * Parameters :  string of the option from the user
 * Returns:      true if everything works fine
 *
 */
bool ProcessScheduler::SetOption(const std::string option)
{
	bool flag = true;

	// assign a proper value to mOption
	if(option == sFCFS) mOption = FCFS;
	else if (option == sSPN) mOption = SPN;
	else if (option == sHRRN) mOption = HRRN;
	else if(option == sSRT) mOption = SRT;
	else if(option == sRR) mOption = RR;
	else
	{
		mOption = NA;
		flag = false;
	}
	return flag;
}

/*
 * Name :        ProcessScheduler::Execute()
 * Description : start scheduling according to the option
 * Parameters :  void
 * Returns :     void
 */
void ProcessScheduler::Execute()
{
	// start scheduling according to the option from command line input
	switch(mOption)
	{
	case FCFS:
		ExecuteFCFS();
		break;
	case SPN:
		ExecuteSPN();
		break;
	case SRT:
		ExecuteSRT();
		break;
	case HRRN:
		ExecuteHRRN();
		break;
	case RR:
		ExecuteRR();
		break;
	case NA:
		cerr<<"No such option!"<<endl;
		cout<<"Options: -FCFS, -SPN, -SRT, -HRRN, -RR"<<endl;
		break;
	}

	// after finishing scheduling, write the information into the output file
	WriteToFile();
}

/*
 * Name :        ProcessScheduler::ExecuteFCFS()
 * Description : schedule the process based on "first come first serve"
 * Parameters :  void
 * Returns :     void
 * Note :        You have to implement this function
 */
void ProcessScheduler::ExecuteFCFS()
{
	cout<<"ExecuteFCFS()"<<endl;
}

/*
* Name :        ProcessScheduler::ExecuteSPN()
* Description : schedule the process based on "shortest process next"
* Parameters :  void
* Returns :     void
* Note :        You have to implement this function
*/
void ProcessScheduler::ExecuteSPN()
{
	cout << "ProcessScheduler::ExecuteSPN()" << endl;
}

/*
* Name :        ProcessScheduler::ExecuteHRRN()
* Description : schedule the process based on "highest response ratio next"
* Parameters :  void
* Returns :     void
* Note :        You have to implement this function 
* THIS FUNCTION IS EXTRA CREDIT*****************************************************************************
*/
void ProcessScheduler::ExecuteHRRN()
{
	cout << "ProcessScheduler::ExecuteHRRN()" << endl;
}

/*
 * Name :        ProcessScheduler::ExecuteSRT()
 * Description : schedule the process based on "shortest remaining time"
 * Parameters :  void
 * Returns :     void
 * Note :        You have to implement this function
 */
void ProcessScheduler::ExecuteSRT()
{
	cout<<"ProcessScheduler::ExecuteSRT()"<<endl;
}

/*
 * Name :        ProcessScheduler::ExecuteRR()
 * Description : schedule the process based on "round robin"
 * Parameters :  void
 * Returns :     void
 * Note :        You have to implement this function
 */
void ProcessScheduler::ExecuteRR()
{
	if(GetQuantum() <= 0)
	{
		cerr<<"For -RR option, you need to provide a quantum value > 0"<<endl;
		return;
	}

	cout<<"ProcessScheduler::ExecuteRR()"<<endl;
}

/*
 * Name :        ProcessScheduler::PrintToScreen()
 * Description : print the time slices together with the ID of the process scheduled for
 * 				 each time slice on the screen chronologically
 * Parameters :  void
 * Returns :     void
 * Note :        You have to implement this function
 */
void ProcessScheduler::PrintToScreen()
{
	cout<<"ProcessScheduler::PrintToScreen()"<<endl;
}

/*
 * Name :        ProcessScheduler::SortByServiceTime()
 * Description : sort the processes by ServiceTime (increasingly)
 * Parameters :  void
 * Returns :     void
 */
void ProcessScheduler::SortByServiceTime()
{
	sort(mProcesses.begin(), mProcesses.end(), CompareServiceTime);
}

/*
 * Name :        ProcessScheduler::SortByProcessID()
 * Description : sort the processes by ProcessID (increasingly)
 * Parameters :  void
 * Returns :     void
 */
void ProcessScheduler::SortByProcessID()
{
	sort(mProcesses.begin(), mProcesses.end(), CompareProcessID);
}

/*
 * Name :        ProcessScheduler::SortByRemainingTime()
 * Description : sort the processes by RemainingTime (increasingly)
 * Parameters :  void
 * Returns :     void
 */
void ProcessScheduler::SortByRemainingTime()
{
	sort(mProcesses.begin(), mProcesses.end(), CompareRemainingTime);
}






