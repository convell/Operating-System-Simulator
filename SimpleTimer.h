// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleTimer.h
 *
 * @brief Definition file for simple timer class
 * 
 * @author Michael Leverington
 * 
 * @details Specifies all member methods of the SimpleTimer
 *
 * @version 1.00 (11 September 2015)
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H

// Header files ///////////////////////////////////////////////////////////////

#include <sys/time.h>
#include <cstring>

using namespace std;

// Class definition  //////////////////////////////////////////////////////////

class SimpleTimer 
   {
    public:

       // constant
       static const char NULL_CHAR = '\0';
       static const char RADIX_POINT = '.';

       // Constructor
       SimpleTimer();
       SimpleTimer(const SimpleTimer &timerToCopy);

       // Destructor
       ~SimpleTimer();
    
       // accessors
       bool start(); 
       void stop(); 
       void getElapsedTime( char *timeStr );
       void getCurrentTime( char *timeStr );
       void delay( int time );
       void setTimeToDelay(int time);
       int getTimeToDelay() const;

    private:
       struct timeval startData, endData, midData, delayData;
       long int beginTime, endTime;
       long int secTime, microSecTime;
       bool running, dataGood;
       int timeToDelay;
   };

#endif // ifndef SIMPLETIMER_H

