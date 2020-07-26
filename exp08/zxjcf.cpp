#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include<semaphore.h>     
#include <time.h>

#define philosopherNUM 15

sem_t chopsticks[philosopherNUM];//1 is availiable 0is unaviliable
pthread_t philosopher[philosopherNUM];
	time_t timep;
	struct tm *p;
void printCurrentTime(){
	time (&timep);
	p=gmtime(&timep);
	printf("[%d:%d:%d]",(p->tm_hour+8)%24,p->tm_min,p->tm_sec);
}

void* philosopherBehavior(void* ptr){

	int index = *(int*)ptr;
	printCurrentTime();printf("philosopher_%d stand by!\n",index);
	while(true){
		int actionRandom = rand()%10;
		if(actionRandom < 3){
			//he wants to eat
			//printCurrentTime();printf("philosopher_%d wants to eat!\n",index);
			int sem_check_left,sem_check_right;
			do{
				usleep(1000*50);
				sem_getvalue(&chopsticks[index],&sem_check_left);
				sem_getvalue(&chopsticks[(index+1)%philosopherNUM],&sem_check_right);
			}while(!(sem_check_left==1&& sem_check_left==1));
			
			int eatTimeMS = rand()%2000;
			sem_wait(&chopsticks[index]);
			sem_wait(&chopsticks[(index+1)%philosopherNUM]);
			printCurrentTime();printf("philosopher_%d eat %d ms!\n",index,eatTimeMS);
			usleep(1000*eatTimeMS);
			printCurrentTime();printf("philosopher_%d eated!\n",index);
			sem_post(&chopsticks[index]);
			sem_post(&chopsticks[(index+1)%philosopherNUM]);
		}
		usleep(1000*100);
	}
}


int main(){
	//initialize the whole program
	 srand((unsigned int)time(NULL));
	for(int i = 0 ; i < philosopherNUM;i++){
		sem_init(&chopsticks[i],0,1);
	}
	for(int i = 0 ; i < philosopherNUM;i++){
		pthread_create(&philosopher[i] , NULL, philosopherBehavior, (void *) &i);
		sleep(1);
	}
	
	
	//block the program
	while(true){
		char command;
		scanf("%c",&command);
		if(command == 'q'){
			break;
		}
	}
	
	return 0;
}