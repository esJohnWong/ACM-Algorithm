#include<iostream>
#include<cstring>

using namespace std;
/**========================================**\
算法分析：
bellmanFord算法可以求有负权边的图的最短路径，
如果有负权回路则算法返回false，否则返回true。
算法开始时将dist赋为无穷大，源点的dist为0。
算法经过n-1次循环结束每次都把所有的边松弛一遍
因为n个点最长的简单最短路径也就n-1条边。松弛
技术为如果dist[v] > dist[u] + w[u][v]，则把
dist[v] = dist[u] + w[u][v]。
如果图中存在负权回路则至少有一条边
dist[v] > dist[u] + w[u][v]
\**========================================**/
const int MAX = 0xffffff;

struct E//边的数据结构
{
	int v , c , next;//c为边的权值
}edge[12];
//dist为源点到每个点的最短距离
int head[6] , dist[6] , pre[6];
int source , n , m;//n是点的个数，m是边的个数

void addedge(int u , int v , int c , int &num)//压入一条边
{
	edge[num].c = c;
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;
}

bool bellmanFord()
{
	for(int i = 1 ; i <= n ; i++)//初始化
	{
		dist[i] = MAX;
		pre[i] = 0;
	}
	dist[source] = 0;//源点到自己的距离为0

	for(int i = 1 ; i < n ; i++)//n-1次操作
	{
		for(int u = 1 ; u <= n ; u++)//每次松弛所有的边
		{
			if(dist[u] == MAX) continue;
			int k = head[u];
			while(k != -1)
			{
				int v = edge[k].v;
				if(edge[k].c != MAX && dist[v] > dist[u] + edge[k].c)//松弛操作
				{
					dist[v] = dist[u] + edge[k].c;
					pre[v] = u;
				}
				k = edge[k].next;
			}
		}
	}

	for(int u = 1 ; u <= n ; u++)//判断是否有负权回路
	{
		if(dist[u] == MAX) continue;
		for(int k = head[u] ; k != -1 ; k = edge[k].next)
		{
			int v = edge[k].v;
			if(edge[k].c != MAX && dist[v] > dist[u] + edge[k].c)
				return false;
		}
	}
	return true;
}

int main()
{
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			addedge(u , v , c , num);
		}

		source = 5;
		bool f = bellmanFord();

		if(f)
			cout<<"true"<<endl;
			else cout<<"false"<<endl;

		for(int i = 1 ; i <= n ; i++)
			cout<<dist[i]<<endl;
	}
	return 0;
}
