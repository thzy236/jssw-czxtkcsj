/*
floyd求任意两点间的最短路，并输出路径
https://www.cnblogs.com/wangyuliang/p/9216365.html
*/

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
int main()
{
	freopen("input.txt","r",stdin);
	int e[10][10],k,i,j,n,m,t1,t2,t3;
	int inf=99999999; 
	scanf("%d %d",&n,&m);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(i==j) e[i][j]=0;
			else e[i][j]=inf;
	for(i=0;i<m;i++){
		scanf("%d %d %d",&t1,&t2,&t3);
		e[t1][t2]=t3;
		e[t2][t1]=t3;
	}
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			for(k=0;k<n;k++)
			if(e[i][j]>e[i][k]+e[k][j]){
				e[i][j]=e[i][k]+e[k][j];
				e[j][i]=e[i][k]+e[k][j];
			}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%10d",e[i][j]);
		}
		printf("\n");
	}
	return 0;
}
