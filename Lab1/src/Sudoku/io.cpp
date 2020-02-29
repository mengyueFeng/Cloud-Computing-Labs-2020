#include "io.h"

#define MAX 81
#define NUM_CONSUMER 5
#define MAX_NUM_OF_FILES 20

sem_t empty;
sem_t full;
sem_t mutex;

char buffer[MAX];
stack<string> resultBuffer;

int flag=0;//reach the end of file
int pos=0;//position to begain read file
int num_files=0;
string files[MAX_NUM_OF_FILES];

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

void Sem_inite(){
    sem_init(&empty,0,1);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
}

string ProblemReader() {
    string tem;
	while (flag==0)
	{
        sem_wait(&full);
        sem_wait(&mutex);
		tem.clear();
		if(flag==0){
			//get problem
		    for(int j=0;j<81;j++){
				tem+=buffer[j];
			}
			std::cout<<"消费者线程" << std::this_thread::get_id()<<"消费"<<tem<<std::endl;
			
		}
    	
        sem_post(&mutex);
        sem_post(&empty);   
		if(flag==0){
			SudokuSolverThread(tem);
		}
	} 

    return tem;
}

void ProblemWriter(string file_path) {
    //open the file
    std::ifstream file(file_path, std::ios::in);
    if (!file.good()) {
        std::cout <<"failed to open file"<< "\n";
		flag=1;
		sem_post(&mutex);
        sem_post(&full);
    }
    else if(file.peek() == EOF)
	 {
	  std::cout << "file is empty."<<std::endl;
	 	flag=1;
		sem_post(&mutex);
        sem_post(&full);
	 }
    //begain to read
    string problem;
	int i=1;
    while(flag==0)
	{
		sem_wait(&empty);
        sem_wait(&mutex);

        file.seekg(pos, std::ios::beg);
        if (file.peek() == EOF)
        {
            flag=1;
        }
        else{
            file.getline(buffer,MAX+1);
            pos+=82;
			std::cout<<"生产第"<<i<<"个产品:"<<buffer<<std::endl;
			i++;
        }
        
        sem_post(&mutex);
        sem_post(&full);
	}
    
	file.close();
	pos=0;
    //kill all consumers
	for(int j=1;j<NUM_CONSUMER;j++){
		sem_post(&mutex);
        sem_post(&full);
	}
	return;
}

// each file read by a thread 
void ReadThread(){
    int no=0;//which file to read
	std::string tfile_path;
	while(no<num_files){
        tfile_path=files[no];
		Sem_inite();
		flag=0;

        thread producer(ProblemWriter,tfile_path); //creat producter threads
        
        std::vector<thread> thread_vector;
        for (int i = 0; i != NUM_CONSUMER; ++i)
        {
            thread_vector.push_back(thread(ProblemReader));//creat consumer threads
        }
        
        for (auto &thr : thread_vector)
        {
            thr.join();
        }
		producer.join();
        no++;
    }
}
/*
void Read(){
    Filename();
    ReadThread();
}
*/
