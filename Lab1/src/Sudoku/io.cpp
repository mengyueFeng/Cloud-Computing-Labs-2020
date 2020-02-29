#include "io.h"

#define MAX_NUM_OF_FILES 20

sem_t empty;
sem_t full;
sem_t mutex;

stack<string> problemBuffer;
stack<string> resultBuffer;

int num_files=0;
string files[MAX_NUM_OF_FILES];

void Sem_inite(){
    sem_init(&empty,0,PROBLEM_BUFFER_LEN);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
}

string ProblemReader() {
    sem_wait(&full);
    sem_wait(&mutex);

    string tem = problemBuffer.top();
    problemBuffer.pop();
    std::cout<<"read from problem buffer:"<<tem<<std::endl;

    sem_post(&mutex);
    sem_post(&empty);

    return tem;
}

void ProblemWriter(string problem) {
    sem_wait(&empty);
    sem_wait(&mutex);

    std::cout<<"Writer problem:"<<problem<<std::endl;
    problemBuffer.push(problem);

    sem_post(&mutex);
    sem_post(&full);
}


// each file read by a thread 
void ReadThread(string file_path){

    std::ifstream file(file_path,std::ios::in);
    if (!file.good()) {
        std::cout <<"failed to open file"<< "\n";
        return;
    }
    else if(file.peek() == EOF)
	 {
	    std::cout << "file is empty."<<std::endl;
	 	return;
	 }


    string problem;
    int pos=0;

    while(file.peek() != EOF){
        file.seekg(pos, std::ios::beg);
        std::getline(file,problem);
        ProblemWriter(problem);    
        pos+=82;
    }

}

// a dedicated thread hold the program for reading content from files
void ReadController_thread(){
    int no=0;//which file to read
	std::string tfile_path;
	while(no<num_files){
        tfile_path=files[no];
        std::cout<<"filename:"<<tfile_path<<std::endl;
        ReadThread(tfile_path); //creat producter threads
        no++;
    }
}

void ReadController(){
    std::thread t(ReadController_thread);
    t.join();
}

void Filename_thread(){
    std::string file_path;
    while(std::cin>>file_path){
        if(num_files>=MAX_NUM_OF_FILES){
            std::cout<<"too many files!"<<std::endl;
            return;
        }
        files[num_files]=file_path;
        num_files++;
		//sleep(1);
    }
}

void Filename(){
    std::thread filename(Filename_thread);
	filename.join();
}
