#include<iostream>

using namespace std;
/**========================**\
算法分析：
floyd算法基于动态规划的思想但
是要求图中没有负权回路。
[i,j]的最短简单路径，至多只包
含n个点所以经过n次循环便可求得
每次向路径中添加一个点k，如果
k在这条路径上则原来的dist[i][j]满足
dist[i][j] > dist[i][k] + dist[k][j]
就将dist[i][j]更新，否则不变。
相应的pre[i][j]（表示从i到j的最
短路径上j的父结点）改为pre[k][j]
否则不变。
\**========================**/
const int MAX = 0xfffffff;
//map为图的信息，dist为最终的结果，pre[i][j]表示从i到j的最短路径上j的父结点
int map[6][6] , dist[6][6] , pre[6][6];
int n , m;

void init()
{
	for(int i = 1 ; i <= n ; i++)//初始化map
		for(int j = 1 ; j <= n ; j++)
		{
			map[i][j] = MAX;
			if(i == j)//如果i=j则将i到自己的路径权值赋为0否则初始化为无穷大
				map[i][j] = 0;
		}

	for(int i = 0 ; i < m ; i++)
	{
		int u , v , c;
		cin>>u>>v>>c;
		map[u][v] = c;
	}
}

void floyd()
{
	for(int i = 1 ; i <= n ; i++)//初始化dist及pre
		for(int j = 1 ; j <= n ; j++)
		{
			if(i == j || map[i][j] == MAX)//如果点i到自己或到j无路径pre[i][j]为0否则为i
				pre[i][j] = 0;
				else pre[i][j] = i;
			dist[i][j] = map[i][j];//i到j之间没有其他的点时dist为图的权值
		}

	for(int k = 1 ; k <= n ; k++)//依次向[i,j]这条路径中加一个点k
	{
		for(int i = 1 ; i <= n ; i++)
			for(int j = 1 ; j <= n ; j++)
			{
				if(dist[i][k] == MAX || dist[k][j] == MAX)
					continue;
				if(dist[i][j] > dist[i][k] + dist[k][j])//k在[i,j]的最短路径上
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					pre[i][j] = pre[k][j];
				}
			}
	}
}

void printpath(int i , int j)//打印路径
{
	if(i == j) printf("%d" , i);
		else if(pre[i][j] == 0) printf("no path from %d to %d\n" , i , j);
		else
		{
			printpath(i , pre[i][j]);
			printf("->%d" , j);
		}
}


int main()
{
	while(cin>>n>>m)
	{
		init();
		floyd();

		for(int i = 1 ; i <= n ; i++)
			for(int j = 1 ; j <= n ;j++)
			{
				printf("%d " , dist[i][j]);
				printpath(i , j);
				printf("\n");
			}
	}
	return 0;
}
