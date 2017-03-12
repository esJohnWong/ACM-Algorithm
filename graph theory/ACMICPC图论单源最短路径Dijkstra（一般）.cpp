#include<iostream>

using namespace std;
/**=======================================**\
算法分析：
单源点最短路Dijkstra算法维护了两个集合Sa,Sb
以及一个dist。算法开始时Sa为空，Sb中为全部图
的点。Sa为源点到点v的距离确定了的点的集合，而
Sb为圆点到v点最短距离还没确定的点的集合。每一
次都从Sb中选一个到源点距离最短的点v加到Sa中，
然后将与v相连在Sb中的点的距离修改，即源点到v
的距离加上v到这点的距离小于这点源点到这点的
距离就将这点的dist修改。时间复杂度为o(n^2)。
\**=======================================**/
const int MAX = 0xfffffff;
//map为图，dist为源点到各点的距离，pre为个点的父结点
int map[6][6]  , dist[6] , pre[6];
bool insp[6];//标志一个点是否在集合Sa中
int source , n , m;//source为源点，n为图中点的个数，m为边的个数

void Dijkstra()
{
	for(int i = 1 ; i <= n ; i++)//初始化
	{
		dist[i] = map[source][i];
		pre[i] = source;
		insp[i] = false;
	}
	dist[source] = 0;//源点到自己的距离为0且在Sa中
	insp[source] = true;

	for(int i = 1 ; i <= n - 1 ; i++)//每次都要找出一个到源点最短距离确定了的点
	{
		int min = MAX;
		int k = 0;
		for(int j = 1 ; j <= n ; j++)//找出Sb中到源点距离最小的点
		{
			if(!insp[j] && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}

		if(k == 0) break;//如果没找到就退出计算

		insp[k] = true;//将找到的点k放到Sa中

		for(int j = 1 ; j <= n ; j++)//修改在Sb中与k相连的点的dist值
		{
			if(!insp[j] && map[k][j] != MAX && dist[j] > dist[k] + map[k][j])
			{
				dist[j] = dist[k] + map[k][j];
				pre[j] = k;
			}
		}
	}
}

int main()
{
	while(cin>>n>>m)
	{
		for(int i = 1 ; i <= n ; i++)//初始化图
			for(int j = 1 ; j <= n ; j++)
				map[i][j] = MAX;

		for(int i = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			map[u][v] = c;
		}

		source = 1 ;
		Dijkstra();

		int res = 0;
		for(int i = 1 ; i <= n ; i++)
			cout<<dist[i]<<endl;
	}
	return 0;
}
