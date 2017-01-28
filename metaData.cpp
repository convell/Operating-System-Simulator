/**
 * @file metaData.cpp
 *
 * @brief Implementation file for metaData class
 * 
 * @details Implements the methods of the metaData class
 *
 * @version 1.00 
 *          Paul Marshall (14 September 2016)
 *          Initial development
 *			(did not change)
 *
 * @Note Requires metaData.h
 **/

// Header files ///////////////////////////////////////////////////////////////
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include "metaData.h"

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
metaData::metaData()
{
	type = NULL;
	cycles = NULL;
	type = new char*[1200];
	cycles = new int[1200];
	for (int i = 0; i < 1200; ++i)
	{
		type[i] = new char[25];
	}
}

/**
 * @brief Default copy constructor
 *
 * @details Constructs metaData with copiedVector data
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 */
metaData::metaData(const metaData &copiedMetaData)
{
	int counter = 0;
	type = new char*[1200];
	cycles = new int[1200];
	for (int i = 0; i < 1200; ++i)
	{
		type[i] = new char[25];
	}
	while(type[counter] != '\0')
	{
		strcpy(type[counter],copiedMetaData.type[counter]);
		cycles[counter] = copiedMetaData.cycles[counter];
		counter++;
	}
}

/**
 * @brief Default destructor
 *
 * @details destructor metaData by deleting all dynamic varibles
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 */
metaData::~metaData()
{
	for (int i = 0; i < 1200; ++i)
	{
		delete type[i];
	}
	delete type;
	delete cycles;
	type = NULL;
	cycles = NULL;

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

void metaData::getFile (char* fileName)
{
	int counter = 0;
	char buffer;
	char *temp = new char[50];
 	ifstream file;

 	file.open(fileName);
 	file.getline( temp, 100 );

 	if (!strcmp(temp,"Start Program Meta-Data Code:"))
	{
		while(!file.eof())
		{
			if(file.peek()==10) //if next line is /n throwaway
			{
				file.get();
			}

			if(!file.getline(type[counter],20,')'))
			{
				break;
			}

			file >> buffer;//gets next digit
			cycles[counter] = buffer-48;

			if (file.peek() >= 48 && file.peek() <= 57) //if double digits get both digits
			{
				cycles[counter] = cycles[counter]*10;
				file >> buffer;
				cycles[counter] = cycles[counter] + (buffer-48);
			}

			file >> temp;

			if(file.peek() == 32) //if next line is a space throwaway
			{
				file.get();
			}

			//cout << type[counter] << cycles[counter] <<endl;
			counter++;
			//file.getline(*data,50);
		}
	}
	else
	{
		cout << "Meta file not initilized correctly" << endl;
	}
	delete[] temp;
}

/**
 * @brief getTypeAtIndex
 *
 * @details returns type at dimension[index]
 * 
 * @exception None
 *
 * @param index is used to figure out which varible the user wants
 *
 * @return type[index]
 *
 * @note None
 */

char* metaData::getTypeAtIndex(int index)
{
	if (index == -1)
	{
		cout << "Out of bounds, Check Index passed." << endl;
		return NULL;
	}
 return type[index];
}

/**
 * @brief getCyclesAtIndex
 *
 * @details returns cycles at dimension[index]
 * 
 * @exception None
 *
 * @param index is used to figure out which varible the user wants
 *
 * @return cycles[index]
 *
 * @note None
 */
int metaData::getCyclesAtIndex(int index)
{
	if (index == -1)
	{
		cout << "Out of bounds, Check Index passed." << endl;
		return -1;
	}

 return cycles[index];
}

int metaData::getSize()
{
	return sizeof(cycles);
}
