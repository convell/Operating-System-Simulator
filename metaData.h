// Program Information ////////////////////////////////////////////////////////
/**
 * @file metaData.h
 *
 * @brief Definition file for metaData
 * 
 * @details Specifies all member methods of the metaData
 *
 * @version 1.00 
 *          Paul Marshall (14 September 2016)
 *          Original code
 *          (did not change)
 *
 * @Note None
 */
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>

class metaData
   {

    public:
    metaData();
    metaData(const metaData &copiedMetaData);
    ~metaData();

    void getFile (char* fileName);
    char* getTypeAtIndex(int index);
    int getCyclesAtIndex(int index);
    int getSize();

	private:
		char** type;
		int* cycles;
    };