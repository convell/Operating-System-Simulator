/**
 * @file Process.cpp
 *
 * @brief Implementation file for Process class
 * 
 * @details Implements the methods of the Process class
 *
 * @version 1.00 
 *          Paul Marshall (30 September 2016)
 *          Initial development
 *			
 *
 * @Note Requires SimpleTimer for running programs
 **/
#include "SimpleTimer.h"
#include "Process.h"
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

/**
 * @brief Default constructor
 *
 * @details Constructs process class
 *          
 * @param None
 *
 * @note N/A
 */
Process::Process()
{
	pid = 0;
	
	processStatus = new char[13];
	previousMemory = -1;

	strcpy(processStatus,"ENTER");
}
/**
 * @brief Default copy constructor
 *
 * @details Constructs process class
 *          
 * @param copied is the copied class
 *
 * @note N/A
 */
Process::Process(const Process &copied)
{
 copied.getPCB(pid,processStatus);
}
/**
 * @brief Default destructor
 *
 * @details deletes processStatus
 *          
 * @param N/A
 *
 * @note N/A
 */
Process::~Process()
{
 //delete[] processStatus; doublefrees for some reason
 processStatus = NULL;
}

/**
 * @brief Read Process
 *
 * @details sets status to ready and increases PID by one
 *          
 * @param N/A
 *
 * @note N/A
 */
void Process::readyProcess()
{
 pid = pid + 1;	
 strcpy(processStatus,"READY");
}

/**
 * @brief Run Process
 *
 * @details sets status to RUNNING
 *          
 * @param N/A
 *
 * @note N/A
 */
void Process::runProcess()
{
 strcpy(processStatus,"RUNNING");
}

/**
 * @brief Waiting Process
 *
 * @details sets status to WAITING
 *          
 * @param N/A
 *
 * @note N/A
 */
void Process::waitProcess()
{
 strcpy(processStatus,"WAITING");
}

/**
 * @brief Terminate Process
 *
 * @details sets status to TERMINATING
 *          
 * @param N/A
 *
 * @note N/A
 */
void Process::terminateProcess()
{
 strcpy(processStatus,"TERMINATING");
}

/**
 * @brief run instruction
 *
 * @details simulates an instruction being ran by delaying the timer
 *          
 * @param a timer, and the delay time for the timer
 *
 * @note N/A
 */
void Process::runInstruction(SimpleTimer myTimer, int timeToDelay)
{

 myTimer.delay(timeToDelay);
}

/**
 * @brief set pid
 *
 * @details did not use yet, but might be useful down the line
 *          
 * @param  setPID - pid to use
 *
 * @note N/A
 */
void Process::setPID(int setPID)
{
 pid = setPID;
}

/**
 * @brief getPCB
 *
 * @details returns PID and process status
 *          
 * @param  returnedPID - pid to be returned 
 *		   processStatusOut - ProcessStatus return
 *
 * @note N/A
 */

void Process::getPCB(int &ReturnedPID, char* &processStatusOut) const
{
 ReturnedPID = pid;
 processStatusOut = processStatus; 
}

/**
 * @brief Allocate memory
 *
 * @details was provided to us, used sprintF to make it return HEX
 *          
 * @param totalMemory
 *
 * @note N/A
 */
char * Process::AllocateMemory( int totMem, int blockSize)
{
	char * buffer = new char[50];
	int currentMemory = 0;

	if (previousMemory == -1)
	{
		previousMemory = 0;
		currentMemory = previousMemory;
	}
	else
	{
		currentMemory = previousMemory + blockSize;
	}

	if (currentMemory > totMem)
	{
		currentMemory = 0;
	}

	sprintf(buffer,"%x",currentMemory);
	previousMemory = currentMemory;
	return buffer;
}