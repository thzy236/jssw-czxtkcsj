/*
图的存入和输出
输入样例： 第一行 m n表示 m个顶点 n条边
10 14
1 2 5
3 5 7
1 4 6
2 5 8
5 7 6
4 5 3
2 8 9
4 9 7
0 1 5
0 8 3
0 9 1
7 8 9
6 0 7
6 2 3
*/

#include<cstdio>
#include<cstdlib>

#define MAXN 15
//邻接矩阵
int nodeNum;
int mapMartix[MAXN][MAXN];

void readMapMartix(){
	for(int i = 0 ; i < MAXN ; i++){
		for(int j = 0 ; j < MAXN ; j++){
			mapMartix[i][j] = -1;
		}
	}
	freopen("input.txt","r",stdin);
	int n;
	scanf("%d%d",&nodeNum,&n);
	int s,e,d;
	for(int i = 0 ; i < n ; i++){
		scanf("%d%d%d",&s,&e,&d);
		//printf("[%d %d %d]\n",s,e,d);
		mapMartix[s][e] = d;
		mapMartix[e][s] = d;
	}
}

void outputMapMartix(){
	printf("   ");
	for(int i = 0 ; i < nodeNum ; i++){
		printf("%2d ",i);
	}
	printf("\n");
	for(int i = 0 ; i < nodeNum ; i++){
		printf("%2d ",i);
		for(int j = 0 ; j < nodeNum ; j++){
			printf("%2d ",mapMartix[i][j]);
		}
		printf("\n");
	}
	
}

//邻接链表
typedef struct ListSide{
	int e,d;
	struct ListSide* next;
}Side;

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

int main(){
	readMapMartix();
	outputMapMartix();
	printf("\n");
	printf("\n");
	readMapList();
	outputMapList();
	return 0;
}