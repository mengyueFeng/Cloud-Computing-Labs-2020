#ifndef _IO_H_
#define _IO_H_


#include "global.h"
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

//inite Semaphores
void Sem_inite();

// read the problem from the buffer
string ProblemReader();

// set the problem in the stack buffer
void ProblemWriter(string problem);

// each file read by a thread 
void ReadThread(string file_path);

// a dedicated thread hold the program for reading content from files
void ReadController_thread();

void ReadController();

//cin file name thread
void Filename_thread();

//join Filename_thread thread
void Filename();


#endif
