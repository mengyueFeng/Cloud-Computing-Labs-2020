#include "thread_solver.h"

//void num of threads
int num_th(){
	int cpu_num=sysconf(_SC_NPROCESSORS_CONF);
    int consumer_num=2;
	if(cpu_num-3>0){
		consumer_num=cpu_num-3;
	}
	std::cout<<"num of cpu:"<<cpu_num<<std::endl;
	std::cout<<"num of consumer:"<<consumer_num<<std::endl;
    return consumer_num;
}


void SolveThreadControler() {
	while(1){	
	    string problem = ProblemReader();
	    SudokuSolverThread(problem);
	}
}
