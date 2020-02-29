#ifndef _IO_H_
#define _IO_H_


#include "global.h"
#include "thread_solver.h"


//cin file name thread
void Filename_thread();

//join Filename_thread thread
void Filename();

//inite Semaphores
void Sem_inite();

// read the problem from the buffer
string ProblemReader();

// set the problem in the stack buffer
void ProblemWriter(string file_path);

// each file read by a thread 
void ReadThread();

//read file name and each file with multi-thread
void Read();

#endif
