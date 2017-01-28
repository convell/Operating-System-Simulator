CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LDFLAGS= -pthread

Sim04 : Sim04.o metaData.o confFile.o SimpleTimer.o Process.o
	$(CC) $(LFLAGS) Sim04.o metaData.o confFile.o SimpleTimer.o Process.o -o Sim04 -lpthread

Sim04.o : Sim04.cpp metaData.h metaData.cpp confFile.h confFile.cpp -lpthread
	$(CC) $(CFLAGS) Sim04.cpp -pthread

confFile.o : confFile.h confFile.cpp
	$(CC) $(CFLAGS) confFile.cpp -lpthread

metaData.o : metaData.h metaData.cpp
	$(CC) $(CFLAGS) metaData.cpp -lpthread

SimpleTimer.o : SimpleTimer.h SimpleTimer.cpp
	$(CC) $(CFLAGS) SimpleTimer.cpp -lpthread

Process.o : Process.h Process.cpp
	$(CC) $(CFLAGS) Process.cpp -lpthread

clean:
	\rm *.o Sim04 
	delete titles;