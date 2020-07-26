#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include<semaphore.h>     
#include <time.h>

sem_t runingNum;

time_t timep;
struct tm *p;
void printCurrentTime(){
	time (&timep);
	p=gmtime(&timep);
	printf("[%d:%d:%d]",(p->tm_hour+8)%24,p->tm_min,p->tm_sec);
}

typedef struct datapkg{
	sem_t enable;
	char sign;
}Data;



void* running(void* ptr){
	Data* data = (Data*)ptr;
	while(true){
		sem_wait(&(data->enable));
		int sleepTimeMS = rand()%7000;
		printCurrentTime();printf("I'm number %c thread,I will running %d ms!\n",data->sign,sleepTimeMS);
		usleep(1000 * sleepTimeMS);
		printCurrentTime();printf("Number %c thread over!\n",data->sign);
		sem_post(&(data->enable));
		sem_wait(&runingNum);
	}
}

void* command(void* ptr){
	Data* datas = (Data*)ptr;
	while(true){
		int checkrunning;
		int once = 1;
		do{
			sem_getvalue(&runingNum,&checkrunning);
			if(once==1){
				once--;
				printCurrentTime();
				printf("There is %d threads are running!",checkrunning);
				if(checkrunning>=3){
					printf("I will waiting for any thread runs over!\n");
				}else{
					printf("Iwill run a new threads!\n");
				}
			}
		}while(checkrunning>=3);
		sem_post(&runingNum);
		sem_post(&((datas+rand()%10)->enable));
		sleep(1);
	}
}

int main(){
	srand((unsigned int)time(NULL));
	pthread_t pool[10];
	Data datas[10];
	pthread_t commander;
	
	sem_init(&runingNum,0,0);
	
	for(int i = 0 ; i < 10 ;i++){
		sem_init(&(datas[i].enable),0,0);
		datas[i].sign = '0'+i;
		pthread_create(&pool[i] , NULL, running, (void *)&(datas[i].enable));
	}
	pthread_create(&commander , NULL, command, datas);
	
	while(true){
		char command;
		scanf("%c",&command);
		if(command == 'q'){
			break;
		}
	}
	
	return 0;
}