/*
图的遍历
采用邻接链表数据结构，给出起始点，对图进行dfs bfs遍历，并输出

*/

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
using namespace std;
#define MAXN 15

//邻接链表
typedef struct ListSide{
	int e,d;
	struct ListSide* next;
}Side;
int nodeNum;
Side *mapList[MAXN];

void readMapList(){
	freopen("input.txt","r",stdin);
	int n;
	scanf("%d%d",&nodeNum,&n);
	int s,e,d;
	for(int i = 0 ; i < n ; i++){
		scanf("%d%d%d",&s,&e,&d);
		Side*s1 = (Side*)malloc(sizeof(Side));
		s1->e = e;
		s1->d = d;
		s1->next = mapList[s];
		mapList[s] = s1;
		Side*s2 = (Side*)malloc(sizeof(Side));
		s2->e = s;
		s2->d = d;
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

void doDfs4MapList(int cur,int* visited){
	if(visited[cur] == 1)return;
	visited[cur] = 1;
	printf("%d ",cur);
	Side* curSide = mapList[cur];
	while(curSide != NULL){
		doDfs4MapList(curSide->e,visited);
		curSide = curSide->next;
	}
}

void dfs4MapList(int s){
	int* visited = (int*)malloc(sizeof(int)*nodeNum);
	memset(visited,0,sizeof(int)*nodeNum);
	printf("dfs : ");
	doDfs4MapList(s,visited);
	printf("\n");
}

void bfs4MapList(int s){
	int* visited = (int*)malloc(sizeof(int)*nodeNum);
	memset(visited,0,sizeof(int)*nodeNum);
	queue<int>que;
	que.push(s);
	printf("bfs : ");
	while(!que.empty()){
		int cur = que.front();que.pop();
		printf("%d ",cur);
		visited[cur] = 1; 
		Side* curSide = mapList[cur];
		while(curSide != NULL){
			if(visited[curSide->e] == 0){
				que.push(curSide->e);
				visited[curSide->e] = 2; 
			}
			curSide = curSide->next;
		}
	}
	printf("\n");
}

int main(){

	readMapList();
	outputMapList();
	printf("\n");
	printf("\n");
	dfs4MapList(0);
	bfs4MapList(0);
	return 0;
}