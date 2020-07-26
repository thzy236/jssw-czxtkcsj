/*
图的最小生成树 prime Kruskal算法 并比较时间复杂度 和空间复杂度
https://segmentfault.com/a/1190000012565380?utm_source=tag-newest
*/

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<algorithm>
using namespace std;
#define MAXN 15

//邻接链表
typedef struct ListSide{
	int s,e,d;
	int selected;
	struct ListSide* next;
}Side;
int nodeNum,sideNum;
Side *mapList[MAXN];

void readMapList(){
	freopen("input.txt","r",stdin);
	scanf("%d%d",&nodeNum,&sideNum);
	int s,e,d;
	for(int i = 0 ; i < sideNum ; i++){
		scanf("%d%d%d",&s,&e,&d);
		Side*s1 = (Side*)malloc(sizeof(Side));
		s1->s = s;
		s1->e = e;
		s1->d = d;
		s1->selected = 0;
		s1->next = mapList[s];
		mapList[s] = s1;
		Side*s2 = (Side*)malloc(sizeof(Side));
		s2->s = e;
		s2->e = s;
		s2->d = d;
		s2->selected = 0;
		s2->next = mapList[e];
		mapList[e] = s2;
	}
}

void outputMapList(){
	for(int i = 0 ; i < nodeNum ; i++){
		printf("%2d ",i);
		Side* curSide = mapList[i];
		
		while(curSide != NULL){
			printf("%2d[%2d] ",curSide->e,curSide->d);
			curSide = curSide->next;
		}
		printf("\n");
	}
}

void outputMinCreateTree(int reset){
	int sumDist = 0;
	for(int i = 0 ; i < nodeNum ; i++){
		printf("%2d ",i);
		Side* curSide = mapList[i];
		
		while(curSide != NULL){
			if(curSide->selected){
				printf("%2d[%2d] ",curSide->e,curSide->d);
				sumDist+=curSide->d;
			}
			if(reset)
				curSide->selected = 0;
			curSide = curSide->next;
		}
		printf("\n");
	}
	printf("SumDist : %d\n\n",sumDist);
}

//prime算法
void prime(){
	int* visited = (int*)malloc(sizeof(int)*nodeNum);
	memset(visited,0,sizeof(int)*nodeNum);
	printf("prime :\n");
	visited[0] = 1;
	for(int i = 0 ; i < nodeNum-1;i++){
		Side* curMinSide = NULL;
		for(int j = 0 ; j < nodeNum ; j++){
			if(visited[j] == 0)continue;
			Side* curSide = mapList[j];
			while(curSide != NULL){
				if(curMinSide == NULL || (visited[curSide->e] == 0 && (curSide->d < curMinSide->d)) ){
					curMinSide = curSide;
				}
				curSide = curSide->next;
			}
		}
		curMinSide->selected = 1;
		visited[curMinSide->e] = 1;
	}
	outputMinCreateTree(1);
}

//Kruskal算法
void kruskal(){
	int* visited = (int*)malloc(sizeof(int)*nodeNum);
	memset(visited,0,sizeof(int)*nodeNum);
	for(int k = 0 ; k < nodeNum ; k++){visited[k] = k;}
	printf("kruskal :\n");
	for(int i = 0 ; i < nodeNum-1;i++){
		Side* curMinSide = NULL;
		for(int j = 0 ; j < nodeNum ; j++){
			Side* curSide = mapList[j];
			while(curSide != NULL){
				if((curMinSide == NULL && (visited[curSide->e] != visited[curSide->s])) || ((visited[curSide->e] != visited[curSide->s]) && (curSide->d < curMinSide->d)) ){
					curMinSide = curSide;
				}
				curSide = curSide->next;
			}
		}
		curMinSide -> selected = 1;
		int sc = visited[curMinSide->s],ec = visited[curMinSide->e];
		for(int k = 0 ; k < nodeNum ; k++){
			if(visited[k] == ec)
				visited[k] = sc;
		}
		//for(int k = 0 ; k < nodeNum ; k++){printf("%d ",visited[k]);}
		//printf("now select %d -> %d dis[%d]\n",curMinSide->s,curMinSide->e,curMinSide->d);
	}
	
	outputMinCreateTree(1);
}


int main(){

	readMapList();
	outputMapList();
	printf("\n");
	printf("\n");
	prime();
	kruskal();
	return 0;
}