// Program Information ////////////////////////////////////////////////////////
/**
 * @file confFile.h
 *
 * @brief Definition file for confFile
 * 
 * @details Specifies all member methods of the confFile
 *
 * @version 1.00 
 *          Paul Marshall (14 September 2016)
 *          Original code
 *
 * @Note None
 */
#include <iostream>
#include <cstring>

class confFile
   {

    public:
    //constructors and destructors
    confFile();
    confFile(const confFile &copied);
    ~confFile();

    //gets
    void getFile (char* fileName);
    char* getTitleAtIndex(int index);
    char* getDataAtIndex(int index, int &returnedInt);
    int getIndexOfString(const char* stringToFind);


	private:
	char** titles;
	char** data;
    };