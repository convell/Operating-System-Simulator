/**
 * @file confFile.cpp
 *
 * @brief Implementation file for conFile class
 * 
 * @details Implements the methods of the confFile class
 *
 * @version 1.00 
 *          Paul Marshall (14 September 2016)
 *          Initial development
 *			(did not change)
 *
 * @Note Requires confFile.h
 **/

// Header files ///////////////////////////////////////////////////////////////
#include "confFile.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

/**
 * @brief Default constructor
 *
 * @details Constructs default values
 *
 * @par None 
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 */
confFile::confFile()
{
	titles = NULL;
	data = NULL;
	titles = new char*[21];
	data = new char*[21];
	for (int i = 0; i < 21; i++)
	{
		titles[i] = new char[50];
		data[i] = new char[25];
	}
}
/**
 * @brief Default copy constructor
 *
 * @details Constructs confFile with copiedVector data
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 */
confFile::confFile(const confFile &copied)
{
	int counter = 0;
	while(titles[counter!= '\0'])
	{
		strcpy(titles[counter],copied.titles[counter]);
		data[counter] = copied.data[counter];
		counter++;
	}
}

/**
 * @brief Default destructor
 *
 * @details destructor confFile by deleting all dynamic varibles
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 */

confFile::~confFile()
{
	for (int i = 0; i < 21; i++)
	{
		delete titles[i];
		delete data[i];
	}
	delete titles;
	delete data;
	titles = NULL;
	data = NULL;
}

/**
 * @brief getFile
 *
 * @details Loads all class values from file
 * 
 * @exception None
 *
 * @param fileName is used for fin.open
 *
 * @return None
 *
 * @note None
 */

void confFile::getFile (char* fileName)
{
	//varible decleration
	int counter = 0;
	char *temp = new char[50];
 	ifstream file;

 	file.open(fileName);
 	file.getline( temp, 50 );

	if (!strcmp(temp,"Start Simulator Configuration File"))
	{
		while(!file.eof())
		{
			file.getline(titles[counter],50,':');

			if(!strcmp(titles[counter],"End Simulator Configuration File"))
			{
				//cout << titles[5] << endl;
				break;
			}

			if (file.peek() == 32)
			{
				file.get();
			}

			file.getline(data[counter],100);

			counter++;
			//file.getline(*data,50);
		}
	}
	else
	{
		cout << "Config file not initilized correctly" << endl;
	}
	file.close();
	delete[] temp;
}

/**
 * @brief getTitleAtIndex
 *
 * @details returns title at dimension[index]
 * 
 * @exception None
 *
 * @param index is used to figure out which varible the user wants
 *
 * @return title[index]
 *
 * @note None
 */
char* confFile::getTitleAtIndex(int index)
{	
	if (index == -1)
	{
		cout << "Out of bounds, Check Index passed." << endl;
		return NULL;
	}

 return titles[index];
}
/**
 * @brief getDataAtIndex
 *
 * @details returns data at dimension[index]
 * 
 * @exception None
 *
 * @param returnedInt is used when the
 *		  char* is actually an int in disguise and needs to be converted to int
 *
 * @return data[index]
 *
 * @note None
 */
char* confFile::getDataAtIndex(int index, int &returnedInt)
{
	int depth = 0;

	if (index == -1)
	{
		cout << "Out of bounds, Check Index passed." << endl;
		return NULL;
	}

	if (data[index][depth] >=48 && data[index][depth] <=57) //if an int and not a string
	{
		returnedInt = (data[index][depth]-48);
		depth++;
		while(data[index][depth]!='\0')
		{
			returnedInt = returnedInt*10;
			returnedInt = returnedInt+(data[index][depth]-48);
			depth++;
		}
	}
	
	return data[index];
}

/**
 * @brief getIndexOfString
 *
 * @details used to lookup a strings index
 * 
 * @exception None
 *
 * @param stringToFind is the string need to be found
 *
 * @return returns index if found, if not -1;
 *
 * @note None
 */

int confFile::getIndexOfString(const char* stringToFind)
{
	
	for (int i = 0; i < 21; i++)
	{
		if (!strcmp(titles[i],stringToFind))
		{
			return i;
		}
	}

	cout << "String not found:" << stringToFind << endl;
	return -1; //if not found return error
}