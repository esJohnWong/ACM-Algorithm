#include<iostream>
#include<cstring>

using namespace std;
/**===============================**\
算法分析：
DAG图即有向无回路图，它的最短距离总
是存在的，因为不可能有负权回路。
首先对图进行拓扑排序，然后按照拓扑排
序的顺序对每个点出去的边进行松弛操作。
\**===============================**/
const int MAX = 0xfffffff;

struct E
{
	int v, c , next;
}edge[12];
//queue为拓扑排序的结果，indegree为点的入度,dist为最后的结果，pre为每个点的前驱结点
int head[7] , queue[7] , indegree[7] , dist[7] , pre[7];
int n , m , source;//source为源点

int  topsort()//拓扑排序
{
	int iq = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		if(indegree[i] == 0)
		queue[iq++] = i;
	}

	for(int i = 0 ; i < iq ; i++)
	{
		for(int k = head[queue[i]] ; k != -1 ; k = edge[k].next)
		{
			indegree[edge[k].v]--;
			if(indegree[edge[k].v] == 0)//每次寻找入度为0的点
			{
				queue[iq++] = edge[k].v;
			}
		}
	}
	return iq;
}

void DAG()
{
	for(int i = 1 ; i <= n ; i++)//初始化操作
	{
		dist[i] = MAX;
		pre[i] = 0;
	}
	dist[source] = 0;

	int iq = topsort();//进行拓扑排序

	for(int i = 0 ; i < iq ; i++)//按照拓扑排序对每个点的出边进行松弛操作
	{
		for(int k = head[queue[i]] ; k != -1 ; k = edge[k].next)
		{
			int v = edge[k].v;
			if(dist[v] > dist[queue[i]] + edge[k].c)//可以松弛
			{
				dist[v] = dist[queue[i]] + edge[k].c;
				pre[v] = queue[i];
			}
		}
	}
}

void addedge(int u , int v , int c , int &num)
{
	edge[num].v = v;
	edge[num].c = c;
	edge[num].next = head[u];
	head[u] = num++;
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

		source = 2;
		DAG();

		for(int i = 1 ; i <= n ; i++)
		{
			if(dist[i] == MAX)
				cout<<"M"<<" ";
				else cout<<dist[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
