/**===========================================**\
算法分析：
最大流EK算法的基本思想是在网络中找增广路径，找到
一条增广路径就计算这条路径可已通过的最大流，即瓶
颈边的容量。然后修改这条路径上的每条边的容量，如
果<u,v>在路径上就减去刚求出来的流量<v,u>加上流量
其他的边的容量不变。然后在这个残留网路上在搜一条
增广路径，直到没有增广路径为止。
\**===========================================**/

#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>

using namespace std;

const int N = 8 , MAX = 0xfffffff;

int map[N][N] , pre[N];//map为网路，pre为每个点的前驱
int source , sink , n , m;//source为源点，sink为汇点，n是点数，m是边数
bool vist[N];//标志一个点是否被访问

bool EKBfs()//搜索增广路径
{
	queue<int> Q;
	memset(pre , -1 , sizeof(pre));
	memset(vist , false , sizeof(vist));
	Q.push(source);//先将源点压入队列
	vist[source] = true;

	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		if(u == sink) return true;//找到一条增广路径

		for(int v = 1 ; v <= n ; v++)
		{
			if(map[u][v] && !vist[v])//边存在且v没被访问
			{
				vist[v] = true;
				pre[v] = u;
				Q.push(v);
			}
		}
	}
	return false;//没找到增广路径
}

int EK()
{
	int maxFlow = 0 , minf;//minf为找到增广路径后路径上可以通过的最大流量

	while(EKBfs())
	{
		minf = MAX;
		int v = sink;
		while(pre[v] != -1)//从从汇点到源点找瓶颈边
		{
			minf = min(minf , map[pre[v]][v]);
			v = pre[v];
		}

		maxFlow += minf;//最大流加上刚找到的流量
		v = sink;
		while(pre[v] != -1)//修改这条路上的容量
		{
			int u = pre[v];
			map[u][v] -= minf;
			map[v][u] += minf;
			v = u;
		}
	}
	return maxFlow;
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		for(int i = 1 ; i <= n ; i++)//初始化
			for(int j = 1 ; j <= n ; j++)
				map[i][j] = 0;

		for(int i = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			map[u][v] = c;
		}

		source = 1 , sink = 4;
		int maxFlow = EK();
		printf("%d\n" , maxFlow);
	}
 	return 0;
}
