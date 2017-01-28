#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int timePassed( struct timeval reference );

int main()
{
    int seconds, microseconds;
    struct timeval refTime, currentTime;

    gettimeofday( &refTime, NULL );

    while( timePassed(refTime) < 5500000 );

    gettimeofday( &currentTime, NULL );
    seconds = currentTime.tv_sec - refTime.tv_sec;
    microseconds = currentTime.tv_usec - refTime.tv_usec;

    if( microseconds < 0 )
    {
        microseconds += 1000000;
        seconds -= 1;
    }

    printf( "%i.%6.6i\n", seconds, microseconds );
}

int timePassed( struct timeval refTime )
{
   struct timeval currentTime;
   int microsec, seconds;

   gettimeofday( &currentTime, NULL );
   seconds = currentTime.tv_sec - refTime.tv_sec;
   microsec = currentTime.tv_usec - refTime.tv_usec;

   if( microsec < 0 )
   {
       microsec += 1000000;
       seconds -= 1;
   }

   if( seconds > 0 )
   {
       microsec = microsec + ( seconds * 1000000 );
   }

   //printf("%i\n", microsec);

   return microsec;
}
