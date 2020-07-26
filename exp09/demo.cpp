#include<stdio.h>
#include<unistd.h>

char buffer[256];

int main(){
	
	pid_t pid = fork();
	 if(pid<0){
	   printf("Create child process failure ...\n");
 
	}else if(pid==0){
	   //子进程执行体
	  printf("Hi i am child process ,my processId is %i \n",getpid());
	 
	   for(int i = 0 ; i < 20 ; i++){
		    FILE * reader = fopen("balabala.txt","r");
		   fscanf(reader,"%s",buffer);
		   printf("reader:%s|\n",buffer);
		   sleep(2);
	   }
	}
	else{
	   //父进程执行体
	   printf("parent process is run ,myid is %i \n",getpid());
	   FILE * writer = fopen("balabala.txt","w");
	   for(int i = 0 ; i < 20 ; i++){
		     printf("writer :%d\n",i);
		   fprintf(writer,"%d",i);
		   fflush(writer);
		   sleep(1);
	   }
	}
 
 
   // 执行体结束标志
   if(pid==0)
   {
	  printf("pid=%i child process end ... \n",getpid());
   }
   else{
	   // 睡眠5s,等待子先进程结束
	   sleep(21);
	   printf("pid=%i Parent process End ... \n",getpid());
   }

	return 0;
}