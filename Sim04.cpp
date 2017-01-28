// Program Information ////////////////////////////////////////////////////////
/**
 * @file PA01.cpp
 *
 * @brief Driver program to exercise OS simulation
 * 
 * @details Used to drive the OS simulation
 *
 * @version 1.10
 *			Paul Marshall(6 October 2016)
 *			Added timer output and IO threading
 *
 *			1.00 
 *         	Paul Marshall (14 September 2016)
 *          Original code
 *
 * @Note Requires iostream.h, cstring, metaData.h, confFile.h SimpleTimer.h Process.h
 *		 also is getting a bit messyjjnbjbn (next iteration will condense arguments and make pretty)
 */
#include "metaData.h"
#include "confFile.h"
#include "SimpleTimer.h"
#include "Process.h"
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <cstring>
#include <vector>


using namespace std;

void calculate(metaData &myMetaData,confFile &myConfFile, int* &storedResults, SimpleTimer &myTimer, Process &myProcess);
void metaDataToConfParser(char* Data, char* &dataReturned);
void processRunHelper(metaData &myMetaData, int* &storedResults, SimpleTimer &myTimer, Process &myProcess, confFile &myConfFile);
void metaDataToOutPutParser (char* Data, char* &dataReturned);
void* threadRun(void* argument);

int main(int argc, char** argv)
{
	int dummyInt = 0;
	int* storedResults = new int[1200];
	char* timerOutput = new char[50];
	metaData myMetaData;
	confFile myConfFile;
	SimpleTimer myTimer;
	Process myProcess;

	if (*argv == NULL)
	{
		return 0;
	}

	myTimer.start();
	myTimer.getCurrentTime(timerOutput);
	cout << timerOutput << " - Simulator program starting" << endl;

	myConfFile.getFile(argv[1]);
	myMetaData.getFile(myConfFile.getDataAtIndex(1,dummyInt));

	calculate(myMetaData,myConfFile,storedResults,myTimer,myProcess);

	delete[] storedResults;
	delete[] timerOutput;
	return 0;
}

/**
 * @brief calculate
 *
 * @details Used to calculate run time into storedResults
 *
 * @exception None
 *
 * @param myMetaData, myConfFile - used to fetch data to calculate runtime
 *		  storeResults - where results are stored.
 *		  myProcess, myTimer - 
 *
 * @return None
 *
 * @note got renamed to calcuate, still decently modular at this point in time
 *		 arguments are getting big. Might need cleaning on that end.
 */

void calculate(metaData &myMetaData, confFile &myConfFile, int* &storedResults, SimpleTimer &myTimer, Process &myProcess)
{
	int counter = 0;
	int resultIndex = 0;
	int cycleTime = 0;
	char* metaDataResult = new char[100];
	char* configParsed = new char[100];

	metaDataResult = myMetaData.getTypeAtIndex(counter);


	while (metaDataResult[0] != '\0')
	{
		//while(metaDataResult[2] != 'e')
		//{
			if (metaDataResult[0]=='S')
			{
				/* code */
			}
			else if (metaDataResult[0]=='A')
			{
				storedResults[counter] = 1;
			}
			else
			{
				metaDataToConfParser(metaDataResult, configParsed);
				resultIndex = myConfFile.getIndexOfString(configParsed);
				myConfFile.getDataAtIndex(resultIndex,cycleTime);
				storedResults[counter] = cycleTime * myMetaData.getCyclesAtIndex(counter);
				if (metaDataResult[0]=='M')
				{
					storedResults[counter] = 1;
			//	cout << "memory stored at: " << myProcess.AllocateMemory(cycleTime,blockSize) << endl;
				}
			}



			//counter++;
		//	metaDataResult = myMetaData.getTypeAtIndex(counter);
		//}/
		counter++;
		metaDataResult = myMetaData.getTypeAtIndex(counter);
	}

	processRunHelper(myMetaData,storedResults,myTimer,myProcess,myConfFile);
	delete[] configParsed;
	delete[] metaDataResult;
}



/**
 * @brief metaDataToConfFileParser
 *
 * @details Coonverts metadata input into useable confFile input
 *
 * @exception S does not not have a confFile data
 *
 * @param data - metadata styled char* to convert to confFile
 *		  dataReturned - used to get around returning a char*
 *
 * @return None
 *
 * @note None
 */
void metaDataToConfParser (char* Data, char* &dataReturned)
{
	if (Data[0] == 'P')
	{
		strcpy(dataReturned,"Processor cycle time (msec)");
	}
	else if (Data[0] == 'M')
	{

		strcpy(dataReturned,"Memory cycle time (msec)");
	}
	else if ((Data[0]=='I') || (Data[0] =='O'))
	{

		if(Data[2] == 'h')
		{
			strcpy(dataReturned,"Hard drive cycle time (msec)");
		}
		else if(Data[2] == 'p')
		{
			strcpy(dataReturned,"Printer cycle time (msec)");
		}
		else if (Data[2] == 'm')
		{
			strcpy(dataReturned,"Monitor display time (msec)");
		}
		else if (Data[2] == 'k')
		{
			strcpy(dataReturned,"Keyboard cycle time (msec)");
		}
	}
	else
	{
	}
}

/**
 * @brief metaDataToOutputFileParser
 *
 * @details Coonverts metadata input into a human readable output
 *
 * @exception N/A
 *
 * @param data - metadata styled char* to convert to confFile
 *		  dataReturned - used to get around returning a char*
 *
 * @return None
 *
 * @note None
 */
void metaDataToOutputParser (char* Data, char* &dataReturned)
{

	if (Data[0] == 'P')
	{
		strcpy(dataReturned,"processing action");
	}
	else if (Data[0] == 'M')
	{
		strcpy(dataReturned,"allocating memory");
	}
	else if (Data[0] == 'A')
	{
		if (Data[2] == 's')
		{
			strcpy(dataReturned,"OS: preparing process");
		}
		else
		{
			strcpy(dataReturned,"OS: removing process");
		}
	}
	else if ((Data[0]=='I'))
	{
		if(Data[2] == 'h')
		{
			strcpy(dataReturned,"hard drive input");
		}
		else if (Data[2] == 'k')
		{
			strcpy(dataReturned,"keyboard input");
		}
	}
	else if (Data[0] =='O')
	{
		if(Data[2] == 'h')
		{
			strcpy(dataReturned,"hard drive output at HDD 0");
		}
		else if(Data[2] == 'p')
		{
			strcpy(dataReturned,"printer output at PRNTR 0");
		}
		else if (Data[2] == 'm')
		{
			strcpy(dataReturned,"monitor output");
		}
	}
}

/**
 * @brief threadRun
 *
 * @details runs a threaded I/O instruction
 *
 * @par None 
 * 
 * @exception None
 *
 * @param void* argument- takes the timer to simulate "running" an instruction, and delays the timer by that much.
 *		  if it gets any bigger will need to pass it a struct sadly
 *
 * @return void* NULL (shouldnt need the return just yet but is needed for pthread reasons)
 *
 * @note will need a struct at one point, but works for now.
 */
void* threadRun(void* argument)
{
	SimpleTimer mytimer1;
	if (mytimer1.start()) //stops multiple timer starts
	{

	}
	mytimer1 = *(SimpleTimer *)argument;
	mytimer1.delay(mytimer1.getTimeToDelay());
	*(SimpleTimer *)argument = mytimer1;
	return NULL;
}

/**
 * @brief calcuateProcessesStart
 *
 * @details figures out where proccesses start in the metaData
 *
 * @par None 
 * 
 * @exception None
 *
 * @param myMetaData & myConfFile - needed for finding proccesses starts
 *
 * @return None
 *
 * @note None
 */
void calculateProcessesStart(metaData &myMetaData, int* processesLeftOffAt)
{
	int iterator = 0;
	int numberOfProcess = 0;
	char* metaDataResult = myMetaData.getTypeAtIndex(0);

	while (metaDataResult != NULL) 
	{
		if (metaDataResult[0] == 'A')
		{
			if (metaDataResult[2] == 's')
			{
				processesLeftOffAt[numberOfProcess] = iterator;
				numberOfProcess++;
			}
		}
		iterator++;
		metaDataResult = myMetaData.getTypeAtIndex(iterator);
	}

}

/**
 * @brief calcuateNumOfProcesses
 *
 * @details figures out how many proccesses are in the code
 *
 * @par None 
 * 
 * @exception None
 *
 * @param myMetaData & myConfFile - needed for finding proccesses
 *
 * @return None
 *
 * @note None
 */
int calcuateNumOfProcesses(metaData &myMetaData)
{
	int iterator = 0;
	int numberOfProcess = 0;
	char* metaDataResult = myMetaData.getTypeAtIndex(0);
	while (metaDataResult != NULL) 
	{
		if (metaDataResult[0] == 'A')
		{
			if (metaDataResult[2] == 's')
			{
				numberOfProcess++;
			}
		}
		iterator++;
		metaDataResult = myMetaData.getTypeAtIndex(iterator);
	}
	return numberOfProcess;
}

/**
 * @brief processRunHelper
 *
 * @details runs and outputs 
 *
 * @par None 
 * 
 * @exception None
 *
 * @param myMetaData & myConfFile - needed for printing off relevant information
 *		  storedResults - used from calculate function that calculated runTime
 *		  myProcess - used to "simulate" running instructions and creating processes
 *		  myTimer - used to time the running and output for the running instruction 
 *		 (timer may be absorbed into the process class down the line to make this function cleaner)
 *
 * @return None
 *
 * @note Interrupt system works, and the idea of RR works in this code, but the for loop is placed weird and the counters keep throwing me off
 *		 
 */
void processRunHelper(metaData &myMetaData, int* &storedResults, SimpleTimer &myTimer, Process &myProcess, confFile &myConfFile)
{
	int counter = 0,PID = 0, dummyInt, totMem, blockSize, numberOfProcess = 3,workingTime,qTime,processCounter = 0,instructionCounter =0;
	bool printToMonitor = false, printToFile = false;
	char* metaDataResult = myMetaData.getTypeAtIndex(0);
	char* outputString = new char[50], *timeOutput = new char[50], *fileOutput = new char[50], *dummyout = new char[50], *timeComp = new char[50];
	pthread_t thread1;
	pthread_mutex_t theMutex;
	pthread_mutex_init(&theMutex, NULL);
	SimpleTimer processTimmer;
	ofstream fout;
	myConfFile.getDataAtIndex(4,qTime);

	int processesLeftOffAt[calcuateNumOfProcesses(myMetaData)];
	cout << sizeof(processesLeftOffAt) << endl;

	calculateProcessesStart(myMetaData,processesLeftOffAt);


	myProcess.getPCB(PID,dummyout);
	//If blocks check where to print and sets a flag
	if (!strcmp(myConfFile.getDataAtIndex(14,dummyInt),"Log to Both")||
		!strcmp(myConfFile.getDataAtIndex(14,dummyInt),"Log to File")) 
	{
		printToFile = true;
		strcpy(fileOutput,myConfFile.getDataAtIndex(15,dummyInt));
		fout.open(fileOutput);
	}

	if (!strcmp(myConfFile.getDataAtIndex(14,dummyInt),"Log to Both")||
		!strcmp(myConfFile.getDataAtIndex(14,dummyInt),"Log to Monitor"))
	{
		printToMonitor = true;
	}

	//loop that goes through each metaDataResult
	//Then "runs" that instruction and prints it
	while (metaDataResult != NULL) 
	{
		//instructionCounter = processesLeftOffAt[processCounter];
		if (processCounter > numberOfProcess)
		{
			processCounter = 0;
		}
		for (int i = processCounter; i < numberOfProcess; ++i)
		{
			instructionCounter = processesLeftOffAt[processCounter];
			while (true) //while an interrupt for this process is not true
			{
				if (storedResults[instructionCounter] > 1) //if a process instruction
				{
					
					if (instructionCounter >= myMetaData.getSize())
					{
						processCounter = processCounter + 1;
						break;
					}
					metaDataToOutputParser(myMetaData.getTypeAtIndex(counter),outputString);
					myTimer.getCurrentTime(timeOutput);

					if (printToMonitor && printToFile)
					{
						cout << timeOutput << " Process " << PID <<": - start " << outputString << endl;
						fout << timeOutput << " Process " << PID <<": - start " <<outputString << endl;

						if (metaDataResult[0]=='I'||metaDataResult[0]=='O') //IO threading
						{
							myTimer.setTimeToDelay(storedResults[instructionCounter]);
							pthread_create(&thread1,NULL,threadRun,(void*)&myTimer);
							pthread_mutex_trylock(&theMutex);
							pthread_join(thread1,NULL);
							pthread_mutex_unlock(&theMutex);
							cout << timeOutput << " Process " << PID << ": - end " << outputString << endl;
							fout << timeOutput << " Process " << PID << ": - end " << outputString << endl;
						}
						else //everything else is ran with out a thread
						{
							processTimmer.getCurrentTime(timeComp);
							sscanf(timeComp, "%d", &workingTime);
							if ((workingTime+storedResults[instructionCounter]) > qTime)
							{
								cout << timeOutput << " Process: " << PID << "interrupt processing action" << endl;
								processesLeftOffAt[i] = instructionCounter;
								processCounter = processCounter + 1;
								break;
							}
							else
							{
								myProcess.runInstruction(myTimer,storedResults[instructionCounter]);
								myTimer.getCurrentTime(timeOutput);
								cout << timeOutput << " Process " << PID << ": - end " << outputString << endl;
								fout << timeOutput << " Process " << PID << ": - end " << outputString << endl;
							}
						}
					}
					else if (printToMonitor)
					{
						cout << timeOutput << " - start " << outputString << endl;
						if (metaDataResult[0]=='I'||metaDataResult[0]=='O') //IO threading
						{
							myTimer.setTimeToDelay(storedResults[instructionCounter]);
							pthread_create(&thread1,NULL,threadRun,(void*)&myTimer);
							pthread_join(thread1,NULL); //still not 100% on how pthreads work. Think this is fine
						}
						else //everything else is ran with out a thread
						{
							myProcess.runInstruction(myTimer,storedResults[instructionCounter]);
							myTimer.getCurrentTime(timeOutput);
						}
						cout << timeOutput << " - end " << outputString << endl;
					}
					else if (printToFile)
					{
						fout << timeOutput << " - start " << outputString << endl;
						if (metaDataResult[0]=='I'||metaDataResult[0]=='O') //IO threading
						{
							myTimer.setTimeToDelay(storedResults[instructionCounter]);
							pthread_create(&thread1,NULL,threadRun,(void*)&myTimer);
							pthread_join(thread1,NULL); //still not 100% on how pthreads work. Think this is fine
						}
						else //everything else is ran with out a thread
						{
							myProcess.runInstruction(myTimer,storedResults[instructionCounter]);
							myTimer.getCurrentTime(timeOutput);
						}
						fout << timeOutput << " - end " << outputString << endl;
					}
				}
					instructionCounter++;
					metaDataResult = myMetaData.getTypeAtIndex(instructionCounter);
				}
				if (instructionCounter >= myMetaData.getSize())
				{
					processCounter = processCounter + 1;
					break;
				}
				if ((workingTime+storedResults[instructionCounter]) > qTime)
				{
					cout << timeOutput << " Process: " << PID << "interrupt processing action" << endl;
					processesLeftOffAt[i] = instructionCounter;
					processCounter = processCounter + 1;
					break;
				}
			}
			if(storedResults[instructionCounter]==1) //if a new process creation
			{
				metaDataToOutputParser(myMetaData.getTypeAtIndex(instructionCounter),outputString);

				if (myMetaData.getTypeAtIndex(instructionCounter)[2] == 's')
				{
					myProcess.readyProcess();
					processTimmer.start();

				}

				if (printToMonitor)
				{
					myProcess.getPCB(PID,dummyout);
					if (myMetaData.getTypeAtIndex(instructionCounter)[2] == 's')
					{
						myTimer.getCurrentTime(timeOutput);
						cout << timeOutput << " - " << outputString << " "<< PID << endl;
						cout << timeOutput << " - " << outputString << " starting process " << PID << endl;
						myProcess.runProcess();
					}
					else
					{
						myTimer.getCurrentTime(timeOutput);
						if (metaDataResult[0]=='M')
						{
							//metaDataToConfParser(metaDataResult, dummyout);
							//resultIndex = myConfFile.getIndexOfString(dummyout);
							myConfFile.getDataAtIndex(8,totMem);
							myConfFile.getDataAtIndex(8+1,blockSize);
							//storedResults[counter] = totMem * myMetaData.getCyclesAtIndex(counter);
							//storedResults[counter] = 1;
							cout << timeOutput << " Process " << PID << ": "<< outputString << endl;
							cout << timeOutput << " Process " << PID << ": " << " Memory allocated at: " << myProcess.AllocateMemory(totMem,blockSize) << endl;
						}
						else
						{
							cout << timeOutput << " - " << outputString << " "<< PID << endl;
						}
					}
				}
				if (printToFile)
				{
					myProcess.getPCB(PID,dummyout);
					if (myMetaData.getTypeAtIndex(instructionCounter)[2] == 's')
					{
						fout << timeOutput << " - " << outputString << " "<< PID << endl;
						fout << timeOutput << " - " <<  outputString << " starting process " << PID << endl;
						myProcess.runProcess();
					}
					else
					{
						myTimer.getCurrentTime(timeOutput);
						fout << timeOutput << " - " << outputString << " "<< PID << endl;
					}
				}
			}
		instructionCounter++;
		processesLeftOffAt[numberOfProcess] = instructionCounter;
		metaDataResult = myMetaData.getTypeAtIndex(instructionCounter);
	}
	delete[] fileOutput;
	delete[] timeOutput;
	delete[] outputString;
	delete[] dummyout;
}
