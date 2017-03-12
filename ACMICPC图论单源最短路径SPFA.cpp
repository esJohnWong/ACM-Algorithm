#include<iostream>
#include<cstring>
#include<queue>

using namespace std;
/**================================**\
算法分析：
SPFA是对bellmanFord的改进，算法首先将
源点到所有点的最短距离设为无穷大，源
点到自己的距离为0，将源点放入一个先进
先出的队列，每次弹出队首的元素，松弛
与队首点u相邻的节点v的dist，必须有从
u到v的路径。如果v的dist被改且不再队列
中就将v放入队列。如果某个点的出队次数
大于总点数，则存在负权回路，否则不存在
负权回路。
\**================================**/
const int MAX = 0xfffffff;

struct E
{
	int v , c , next;
}edge[12];
//dist为源点到每个点的最短路径估计，pre为每个点的父结点
int head[6] , dist[6] , source , pre[6];
bool inq[6];//标记一个点是否在队中
int n , m , outq[6];//outq为一个点出队的次数

void addedge(int u , int v , int c , int &num)
{
	edge[num].c = c;
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;
}

bool SPFA()
{
	queue<int> Q;
	for(int i = 1 ; i <= n ; i++)//初始化
	{
		dist[i] = MAX;
		pre[i] = 0;
		inq[i] = false;
	}
	dist[source] = 0;
	Q.push(source);
	inq[source] = true;

	memset(outq , 0 , sizeof(outq));

	while(!Q.empty())//每次弹出一个队首的点
	{
		int u = Q.front();
		Q.pop();

		inq[u] = false;
		outq[u]++;
		if(outq[u] > n) return false;//如果出队次数大于n

		int k = head[u];
		while(k != -1)//修改从u出来的边的v点的dist
		{
			int v = edge[k].v;
			if(dist[v] > dist[u] + edge[k].c)
			{
				dist[v] = dist[u] + edge[k].c;
				pre[v] = u;

				if(!inq[v])//如果没在队列中就放入队列
				{
					inq[v] = true;
					Q.push(v);
				}
			}
			k = edge[k].next;
		}
	}
	return true;
}

int main()
{
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 1 , num = 0 ; i <= m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			addedge(u , v , c , num);
		}

		source = 5;
		bool f = SPFA();
		if(f)
			cout<<"true"<<endl;
			else cout<<"false"<<endl;

		for(int i = 1 ; i <= n ; i++)
			cout<<dist[i]<<endl;
	}
	return 0;
}
