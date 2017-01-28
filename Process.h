// Program Information ////////////////////////////////////////////////////////
/**
 * @file Process.h
 *
 * @brief Definition file for Process
 * 
 * @details Specifies all member methods of the Process
 *
 * @version 1.00 
 *          Paul Marshall (30 September 2016)
 *          Original code
 *
 * @Note None
 */
class Process
   {

    public:
    //constructors and destructors
    Process();
    Process(const Process &copied);
    ~Process();


    void readyProcess();
    void runProcess();
    void runInstruction(SimpleTimer myTimer, int timeToDelay);
    void setPID(int PID);
    void getPCB(int &PID, char* &processStatus) const;
    void printProcess();
    void terminateProcess();
    void waitProcess();
    char* AllocateMemory( int totalMem ,int blockSize);
    //gets
	private:
	char* processStatus;
	int pid; 
    unsigned int previousMemory;
    };