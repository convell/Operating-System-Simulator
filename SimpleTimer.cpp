// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleTimer.cpp
 * 
 * @brief Implementation file for SimpleTimer class
 * 
 * @author Michael Leverington
 *
 * @details Implements member methods for timing
 *
 * @version 1.10 (6 October 2016)
 *          Modified for purpose of OS
 *          Paul Marshall 
 *
 *          1.00 (11 September 2015)
 *          Micheal Leverington
 *
 * @Note Requires SimpleTimer.h.
 * 
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef SIMPLETIMER_CPP
#define SIMPLETIMER_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "SimpleTimer.h"
#include <iostream>

using namespace std;

/**
 * @brief Default constructor
 *
 * @details Constructs Timer class
 *          
 * @param None
 *
 * @note set running flag to false
 */
SimpleTimer::SimpleTimer
       (
        // no parameters
       )
   {
    running = false;
   }

SimpleTimer::SimpleTimer(const SimpleTimer &timerToCopy)
{
  timeToDelay = timerToCopy.getTimeToDelay();
}

/**
 * @brief Default constructor
 *
 * @details Destructs Timer class
 *          
 * @param None
 *
 * @note No data to clear
 */
SimpleTimer::~SimpleTimer
       (
        // no parameters
       )
   {
    // no action here 
   }

/**
 * @brief Start control
 *
 * @details Takes initial time data
 *          
 * @param None
 *
 * @note None
 */
bool SimpleTimer::start
       (
        // no parameters
       )
   {
    if (running==true) //if already running dont restart
    {
      return false;
    }
    gettimeofday( &startData, NULL );

    running = true;

    dataGood = false;
    return true;
   }

/**
 * @brief Stop control
 *
 * @details Takes final time data, calculates duration
 *          
 * @param None
 *
 * @note None
 */
void SimpleTimer::stop
       (
        // no parameters
       )
   {
    if( running )
       {
        gettimeofday( &endData, NULL );

        running = false;

        dataGood = true;
       }

    else
       {
        dataGood = false;
       }
   }

/**
 * @brief total time between start and stoped timer
 *
 * @details nice for switiching between timers
 *          
 * @param None
 *
 * @note time in milli
 */
void SimpleTimer::getElapsedTime
       (
        char *timeStr
       )
   {
    int low, high, index = 0;
    char temp;

    if( dataGood )
       {
        secTime = endData.tv_sec - startData.tv_sec;
        microSecTime = endData.tv_usec - startData.tv_usec;

        if( microSecTime < 0 )
           {
            microSecTime += 1000000;

            secTime -= 1;
           }

        while( microSecTime > 0 )
           {
            timeStr[ index ] = char( microSecTime % 10 + '0' );

            microSecTime /= 10;
    
            index++;
           }

        while( index < 6 )
           {
            timeStr[ index ] = '0';

            index++;
           }

        timeStr[ index ] = RADIX_POINT;

        index++;

        if( secTime == 0 )
           {
            timeStr[ index ] = '0';
    
            index++;
           }

        while( secTime > 0 )
           {
            timeStr[ index ] = char( secTime % 10 + '0' );

            secTime /= 10;

            index++;
           }

        timeStr[ index ] = NULL_CHAR;

        low = 0; high = index - 1;

        while( low < high )
           {
            temp = timeStr[ low ];
            timeStr[ low ] = timeStr[ high ];
            timeStr[ high ] = temp;

            low++; high--;
           }
       }

    else
       {
        strcpy( timeStr, "No Data" );
       }
   }

/**
 * @brief gets current time
 *
 * @details 
 *          
 * @param timeStr - returns a string of current time
 *
 * @note time is in milli
 */

void SimpleTimer::getCurrentTime
       (
        char *timeStr
       )
   {
    int low, high, index = 0;
    char temp;

    gettimeofday( &midData, NULL );

        secTime = midData.tv_sec - startData.tv_sec;
        microSecTime = midData.tv_usec - startData.tv_usec;

        if( microSecTime < 0 )
           {
            microSecTime += 1000000;

            secTime -= 1;
           }

        while( microSecTime > 0 )
           {
            timeStr[ index ] = char( microSecTime % 10 + '0' );

            microSecTime /= 10;
    
            index++;
           }

        while( index < 6 )
           {
            timeStr[ index ] = '0';

            index++;
           }

        timeStr[ index ] = RADIX_POINT;

        index++;

        if( secTime == 0 )
           {
            timeStr[ index ] = '0';
    
            index++;
           }

        while( secTime > 0 )
           {
            timeStr[ index ] = char( secTime % 10 + '0' );

            secTime /= 10;

            index++;
           }

        timeStr[ index ] = NULL_CHAR;

        low = 0; high = index - 1;

        while( low < high )
           {
            temp = timeStr[ low ];
            timeStr[ low ] = timeStr[ high ];
            timeStr[ high ] = temp;

            low++; high--;
           }
   }

/**
 * @brief delay function
 *
 * @details used to simulate running of instructions
 *          
 * @param None
 *
 * @note time is in milliseconds
 */

void SimpleTimer::delay( int time )
   {
    long int waitTime;
    long int secondWait;
    int index = 0;

    gettimeofday( &delayData, NULL );

    waitTime = ( delayData.tv_usec + ( time ) * 1000 );

    while( waitTime > 1000000 )
       {
        waitTime -= 1000000;
        index++;
       }

    secondWait = index + delayData.tv_sec;

    while( delayData.tv_sec < secondWait )
       {
        gettimeofday( &delayData, NULL );
       }

    while( delayData.tv_usec < waitTime )
       {
        gettimeofday( &delayData, NULL );
       }

   }

void SimpleTimer::setTimeToDelay(int timeDelay)
{
  timeToDelay=0;
  timeToDelay = timeDelay;

}

/**
 * @brief getTimeToDelay
 *
 * @details returns timeToDelay
 *          
 * @param None
 *
 * @note 
 */
int SimpleTimer::getTimeToDelay() const
{
  return timeToDelay;
}


#endif // ifndef SIMPLETIMER_CPP