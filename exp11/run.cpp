#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include<semaphore.h>     
#include <time.h>
#include <string.h>
#include<sys/time.h>
#include<algorithm>

#define possesed 1
#define unpossesed 0

const int algorithmSwitch = 2;//FF:0  BF:1 WF:2
const int FOFlag = 0;//0:LIFO  1:FIFO

typedef struct MemoryBlock{
	char data[10];
	struct MemoryBlock* next;
	int status;
	long time;
}Block;

typedef struct DataPackage{
	sem_t enable;
	int index;
	char buffer[50];
}Pkg;

long getMSTime(){
	 struct timeval time;
    gettimeofday(&time, NULL);
	return time.tv_usec + time.tv_sec*1000000;
}

Block*blockPool;
Block** blockList;
int unionSet[10];

void updateUnionSet(){
	
	for(int i = 0 ; i < 10	 ; i++){
		//printf("%d",blockList[i]->status);
		unionSet[i] = blockList[i]->status;
	}
	//printf("|UpdUnionSet\n");
}

Block* myMAllocFF(int size){
	int blockNum = (size/10+ (size%10 !=0));
	int len = 0;
	int once = 1;
	while(true){
		int first = -1;
		int len = 0;
		updateUnionSet();
		for(int i = 0 ; i < 10 ;i++){
			if(unionSet[i] == unpossesed){
				if(first == -1)first = i;
				len++;
				if(len >= blockNum){
					break;
				}
			}else{
				first = -1;
				len = 0;
			}
		}
		updateUnionSet();	
		if(first != -1 && len >= blockNum){
			Block* blockPtr = blockList[first];
			long possesedTime = getMSTime();
			for(int i = 0 ; i < blockNum ;i++){
				blockPtr->status = possesed;
				blockPtr->time = possesedTime;
				blockPtr = blockPtr->next;
			}
			return blockList[first];
		}
		
		
		if(once){
			once--;
			printf("not enough memory! waiting for %d bytes memory!\n",size);
		}
		usleep(1000);
	}
}

Block* myMAllocBF(int size){
	int blockNum = (size/10+ (size%10 !=0));
	int once = 1;
	while(true){
		int first = -1;
		int len = 0;
		int maxFirst = -1;
		int maxlen = 999;
		updateUnionSet();
		for(int i = 0 ; i < 10 ;i++){
			if(unionSet[i] == unpossesed){
				if(first == -1)first = i;
				len++;
				if(len < maxlen && len >blockNum){
					maxFirst = first;
					maxlen = len;
				}
			}else{
				first = -1;
				len = 0;
			}
		}
		
		updateUnionSet();	
		if(maxFirst != -1 && maxlen >=blockNum){
			Block* blockPtr = blockList[maxFirst];
			long possesedTime = getMSTime();
			for(int i = 0 ; i < blockNum ;i++){
				blockPtr->status = possesed;
				blockPtr->time = possesedTime;
				blockPtr = blockPtr->next;
			}
			return blockList[maxFirst];
		}
		
		
		if(once){
			once--;
			printf("not enough memory! waiting for %d bytes memory!\n",size);
		}
		usleep(1000);
	}
}

Block* myMAllocWF(int size){
	int blockNum = (size/10+ (size%10 !=0));
	int len = 0;
	int once = 1;
	while(true){
		int first = -1;
		int len = 0;
		int maxFirst = -1;
		int maxlen = 0;
		updateUnionSet();
		for(int i = 0 ; i < 10 ;i++){
			if(unionSet[i] == unpossesed){
				if(first == -1)first = i;
				len++;
				if(len > maxlen){
					maxFirst = first;
					maxlen = len;
				}
			}else{
				first = -1;
				len = 0;
			}
		}
		
		updateUnionSet();	
		if(maxFirst != -1 && maxlen > blockNum){
			Block* blockPtr = blockList[maxFirst];
			long possesedTime = getMSTime();
			for(int i = 0 ; i < blockNum ;i++){
				blockPtr->status = possesed;
				blockPtr->time = possesedTime;
				blockPtr = blockPtr->next;
			}
			return blockList[maxFirst];
		}
		
		if(once){
			once--;
			printf("not enough memory! waiting for %d bytes memory!\n",size);
		}
		usleep(1000);
	}
}

//自定义的内存分配函数 当内存不足时会自动挂起

Block* myMAlloc(int size){
	switch(algorithmSwitch){
		case 0://FF
			return myMAllocFF(size);//zhe li bu xie return jv ran neng pao! amazing!
			break;
		case 1://BF
			return myMAllocBF(size);
			break;
		case 2://WF
			return myMAllocWF(size);
			break;
	}
}

void MemoryFree(Block* ptr){
	int endOfChunk = 0;
	while(true){
		ptr->status = unpossesed;
		char* dataPtr = ptr->data;
		for(int i = 0 ; i < 10 ; i++){
			//printf("[%c]",*dataPtr);
			if(*dataPtr == '\0'){
				endOfChunk = 1;
				break;
			}
			dataPtr++;
		}
		if(endOfChunk)break;
		ptr = ptr->next;
	}
	if(algorithmSwitch >0){
		//add chunk
	}
}

void *MemoryAllocateThread(void* pkgptr){
	Pkg* ptr = (Pkg*)pkgptr;
	int workTimes = 0;
	while(true){
			//sem_wait(&(ptr->enable));
			//随机生成一个8位的学号 和 一个4～12位的英文字符串作为姓名
			//printf("Allocater[ %d ]  I'm generating ID and name!\n",ptr->index);
			char* buffer = ptr->buffer;
			for(int i = 0 ;i < 8;i++){
				*buffer = rand()%10+'0';
				buffer++;
			}
			*buffer = ':';buffer++;
			int nameLength = rand()%8 + 4;
			for(int i = 0 ; i < nameLength ; i++){
				*buffer = rand()%10+'A';
				buffer++;
			}
			*buffer = '\0';
			
			//申请内存
			int fullLength = nameLength + 8 +2;
			//printf("Allocater[ %d ]  try to allocate %d bytes memory\n",ptr->index,fullLength);
			Block* blocks = myMAlloc(fullLength);
			printf("Allocater[%d][%d]@%x->%s\n",ptr->index,++workTimes,blocks,ptr->buffer);
			//printf("Allocater[ %d ]  allocate memory successfully,%x\n",ptr->index,blocks);
			//写入数据
			buffer = ptr->buffer;
			char* dest;
			int blockNum = (fullLength/10+ (fullLength%10 !=0));
			//printf("Allocater[ %d ]  blockNum %d\n",ptr->index,blockNum);
			for(int i = 0 ; i < blockNum;i++){
				dest = blocks->data;
				for(int j = 0; j < 10 ; j++){
					*dest = *buffer;
					if(*buffer == '\0')
						break;
					dest++;
					buffer++;
				}
				blocks = blocks->next;
			}
			//printf("Allocater[ %d ]  write data successfully\n",ptr->index);
			sleep(1);
			//xieruwancheng
			//sem_post(&(ptr->enable));
	}
}

void outputInfo(Block* first){
	printf("ID : ");
	for(int i = 0 ; i < 8 ; i++)
		printf("%c",*((first->data)+i));
	printf("   Name : ");
	int charFlag = 9;
	while(true){
		char c = *((first->data) + charFlag);
		if(c == '\0')break;
		printf("%c",c);
		charFlag++;
		if(charFlag > 9){
			first = first->next;
			charFlag = 0;
		}
	}
	printf("\n");
}


void* OutputThread(void* ptr){
	while(true){
		sleep(2);
		Block* lastStorage=NULL;
		Block* firstStorage=NULL;
		Block* blockPtr = blockPool;
		while(blockPtr != NULL){
			if(blockPtr->status == unpossesed){
				blockPtr = blockPtr->next;
				continue;
			}
			if(lastStorage == NULL || blockPtr->time > lastStorage->time){
				lastStorage = blockPtr;
			}
			if(firstStorage == NULL || blockPtr->time < firstStorage->time){
				firstStorage = blockPtr;
			}
			blockPtr = blockPtr->next;
		}
		Block* operatorBlock = FOFlag ? firstStorage :lastStorage;
		printf("outputInfo : ");
		outputInfo(operatorBlock);
		//printf("try to free memory!\n");
		MemoryFree(operatorBlock);
		printf("%x free over!\n",operatorBlock);
		updateUnionSet();
	}
}


int main(){
	printf("Initlizing memory block!\n");
	blockPool = NULL;
	Block* p1;
	for(int i = 0 ; i < 10 ; i++){
		p1 = (Block*)malloc(sizeof(Block));
		p1->status = unpossesed;
		p1->next = blockPool;
		blockPool = p1;
	}
	p1 = blockPool;
	blockList = (Block**)malloc(sizeof(Block*)*10);
	for(int i = 0 ; i < 10 ; i++){
		blockList[i] = p1;
		printf("block[%d] -> %x , next->%x poss:%d\n",i,p1,p1->next,p1->status);
		p1 = p1->next;
	}
	printf("Initlizing data package!\n");
	Pkg* pkg[2];
	pkg[0] = (Pkg*)malloc(sizeof(Pkg));
	pkg[0]->index = 0;
	pkg[1] = (Pkg*)malloc(sizeof(Pkg));
	pkg[1]->index = 1;
	
	printf("creating threads!\n");
	pthread_t MAT0,MAT1,OT0;
	pthread_create(&MAT0, NULL, MemoryAllocateThread, (void *) pkg[0]);
	pthread_create(&MAT1, NULL, MemoryAllocateThread, (void *) pkg[1]);
	pthread_create(&OT0, NULL, OutputThread, NULL);

	printf("threads created successfully!\n");
	while(true){
		char command;
		scanf("%c",&command);
		if(command == 'q'){
			break;
		}
	}
	
	return 0;
}