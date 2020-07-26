#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/shm.h>
#include <unistd.h>    
#include <time.h>
#include<semaphore.h> 
#include <sys/wait.h>

#define testSemKey 1131

const char* fileName = "exp9-3data.txt";
sem_t* isWriteAvaliable;
sem_t* isReaderAvaliable;
sem_t* quitSignal;

time_t timep;
struct tm *p;

void fprintCurrentTime(FILE* file){
	time (&timep);
	p=gmtime(&timep);
	fprintf(file,"[%d:%d:%d]",(p->tm_hour+8)%24,p->tm_min,p->tm_sec);
	fflush(file);
}

void printCurrentTime(){
	fprintCurrentTime(stdout);
}

int getWriterStatus(){//0 is unavaliable
	int temp;
	sem_getvalue(isWriteAvaliable,&temp);
	return temp;
}

int getReadingNum(){
	int temp;
	sem_getvalue(isReaderAvaliable,&temp);
	return temp;
}

pid_t createWriter(char* name,char* id){
	pid_t pid = fork();
	if(pid > 0){
		return pid;
	}else if(pid == 0){
		srand((unsigned int)time(NULL));
		FILE* file = fopen(fileName,"a+");
		printCurrentTime();printf("%s-%s is created as a writer.[pid = %d]\n",id,name,getpid());
		//fprintCurrentTime(file);fprintf(file,"%s-%s is created as a writer.[pid = %d]\n",id,name,getpid());
		while(true){
			int quitSignalValue;
			sem_getvalue(quitSignal,&quitSignalValue);
			if(quitSignalValue == 1){
				break;
			}
			//writer behavior
			int behavior = rand()%10;
			//printCurrentTime();printf("%s has a random number %d.\n",name,behavior);
			if(behavior < 3){
				//sleep
				sleep(rand()%5);
			}else{
				//write
				int charNum = rand()%15+1;
				int i;
				printCurrentTime();printf("%s wants to write %d characters.\n",name,charNum);
				
				int check;
				do{
					usleep(100);
					check = getReadingNum();
				}while(!(check==0));
				do{
					usleep(100);
					check = getWriterStatus();
				}while(!(check!=0));
				sem_wait(isWriteAvaliable);
				
				
				FILE* file = fopen(fileName,"a+");
				fprintCurrentTime(file);
				fprintf(file,"%s-%s[%d]:",id,name,charNum);
				fflush(file);
				for(i = 0 ; i < charNum;i++){
					fprintf(file,"%c",rand()%26 + 'A');
					fflush(file);
					usleep(1000*200);
				}
				fprintf(file,"\n");
				fflush(file);
				printCurrentTime();printf("%s write over!\n",name);
				sem_post(isWriteAvaliable);
			}
			sleep(2);
		}
		printCurrentTime();
		printf("%s exited!\n",name);
		return 0;
	}
}

pid_t createReader(char* name,char* id){
	pid_t pid = fork();
	if(pid > 0){
		return pid;
	}else if(pid == 0){
		srand((unsigned int)time(NULL));
		printCurrentTime();printf("%s-%s is created as a reader.[pid = %d]\n",id,name,getpid());
		while(true){
			int quitSignalValue;
			sem_getvalue(quitSignal,&quitSignalValue);
			if(quitSignalValue == 1){
				break;
			}
			//reader behavior
			int behavior = rand()%10;
			if(behavior < 8){
				//sleep
				sleep(rand()%5);
			}else{
				//reader
				int readTimeMS = rand()%5000;
				printCurrentTime();printf("%s wants to read %d ms.\n",name,readTimeMS);
				int check;
				do{
					usleep(1);
					check = getWriterStatus();
				}while(!(check!=0));
				
				sem_post(isReaderAvaliable);
				usleep(1000*readTimeMS);
				printCurrentTime();printf("%s read over!\n",name);
				sem_wait(isReaderAvaliable);
			}
			sleep(2);
		}
		printCurrentTime();
		printf("%s exited!\n",name);
		return 0;
	}
}

int  main(){
	//init
	srand((unsigned int)time(NULL));
	int shmid = shmget((key_t)testSemKey, sizeof(sem_t)*3, 0666|IPC_CREAT);
	sem_t* shm = (sem_t*)shmat(shmid,0,0);//malloc(sizeof(sem_t)*3);//
	isWriteAvaliable = shm;
	quitSignal = shm+1;
	isReaderAvaliable = shm+2;
	sem_init(shm,0,1);
	sem_init(shm+1,0,0);
	sem_init(shm+2,0,0);

	int childPid[6] ;
	int idx = 0;
	//create wirters
	int pid = createWriter("DouglasY","20180718");
	if(pid == 0) return 0;
	else childPid[idx++] = pid;
	sleep(1);
	pid =  createWriter("AliceF","20181004");
	if(pid == 0) return 0;
	else childPid[idx++] = pid;
	sleep(1);
	pid = createWriter("HuaweiP10","20000310");
	if(pid == 0) return 0;
	else childPid[idx++] = pid;
	sleep(1);
	//createReaders
	pid = createReader("Tom","20010606");
	if(pid == 0) return 0;
	else childPid[idx++] = pid;
	sleep(1);
	pid =  createReader("Jerry","04260729");
	if(pid == 0) return 0;
	else childPid[idx++] = pid;
	sleep(1);
	pid = createReader("Mask","09190834");
	if(pid == 0) return 0;
	else childPid[idx++] = pid;
	sleep(1);
	//wait quit command
	while(true){
		char command;
		scanf("%c",&command);
		if(command == 'q'){
			sem_post(quitSignal);
			for(int i = 0 ; i < idx ; i++){
				waitpid(childPid[i],NULL,0);
			}
			break;
		}
	}
	
	shmdt(shm);
	shmctl(shmid,IPC_RMID,0);
	return 0;
}