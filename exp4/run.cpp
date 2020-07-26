/*
dijkstra求单源最短路
https://blog.csdn.net/qq_35644234/article/details/60870719
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

void dijkstra(int s){
	int* visited = (int*)malloc(sizeof(int)*nodeNum);
	memset(visited,0,sizeof(int)*nodeNum);
	int* dist = (int*)malloc(sizeof(int)*nodeNum);
	for(int k = 0 ; k < nodeNum ; k++){dist[k] = -1;}
	printf("dijkstra : ");
	dist[s] = 0;
	for(int i = 0 ; i < nodeNum ; i++){
		int curNode = -1;
		for(int j = 0 ; j < nodeNum ; j++){
			if((visited[j] == 0) && (curNode == -1 || (dist[curNode] == -1 || dist[curNode] > dist[j]))){
				curNode = j;
			}
		}
		visited[curNode] = 1;
		Side* curSide = mapList[curNode];
		while(curSide != NULL){
			if(dist[curSide->e] == -1 || dist[curNode] + curSide->d < dist[curSide->e]){
				dist[curSide->e] = dist[curNode] + curSide->d;
			}
			curSide = curSide->next;
		}
	}
	
	for(int k = 0 ; k < nodeNum ; k++){
		printf("%2d ",dist[k]);
		
	}
	printf("\n");
	
}


int main(){

	readMapList();
	outputMapList();
	printf("\n");
	printf("\n");
	dijkstra(0);
	return 0;
}