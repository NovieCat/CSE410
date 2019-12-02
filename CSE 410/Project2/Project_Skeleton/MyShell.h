/*
 * File    : MyShell.h
 *
 * Header for the MyShell class for Project2.
 *
 * Class   : MyShell.h
 * Impl    : MyShell.cpp
 * Created : Jan 10, 2012
 * Author  : CSE410 Spring 2012
 *
 * Notes   : You have to implement some functions in this class
 */

#ifndef MYSHELL_H_
#define MYSHELL_H_
#include <string>
#include <list>

#include <stdlib.h>
class CShellParser;
class MyShellParser;
class MyShell
{
public:
	MyShell(char ** params);
	virtual ~MyShell();

	// for handling the command invoked by "./myShell -c <command>"
	void ExecuteCShellCommand(CShellParser* u);

	// set the value of mIsquit
	void SetIsQuit(const bool b) {mIsQuit = b;}

	// the prompt function
	void Prompt();

	// functions for internal commands
	void PrintHistory(); 							// hist
	std::string GetTime(); 							// date
	std::string GetCurrentDirectory(); 				// curr
	void ChangeCurrentDirectory(const char* dir); 	     // cd Dir
     std::string PrintEnv();                                // environmental variables

private:

     MyShell();
	// get the user name for prompt
	std::string GetUserName();

	// get the name of the machine for prompt
	std::string GetHostName();

	// return the value of mIsQuit
	bool IsQuit() const {return mIsQuit;}

	// wait for all the running child processes
	// before exiting our shell
	void WaitForChildProcess();

	// for displaying the message of <1 arctic:userName> in our shell
	void PrintPromptInfo();

	// update our commandline history
	void UpdateHistory(const std::string& h);

	// functions for executing commands
	void ExecuteMyShellCommand(MyShellParser *parser);
	void ExecuteInternalCommand(MyShellParser *parser);
	void ExecuteExternalCommand(MyShellParser *parser);

	// host name shown in the prompt
	std::string mHostName;

	// user name shown in the prompt
	std::string mUserName;

	// sequence number shown in the prompt
	int mSequenceNumber;

	// should we quit the current shell?
	bool mIsQuit;
     
     // pointer to environmental variable list
     char ** ParamPtrList;

	// storing the command line history
	std::list<std::string>mHistory;

	// the sequence number for commands stored in the history
	int mHistoryCounter;
};

#endif /* MYSHELL_H_ */
