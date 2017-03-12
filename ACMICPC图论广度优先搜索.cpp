#include<iostream>
#include<cstring>
#include<queue>

using namespace std;
/**============================**\
图的广度优先算法不解释 太简单了
\**============================**/
struct E//边的数据结构
{
	int v;
	int next;
}edge[20];

int n , m , head[8] ,sume;
bool visit[8];

void addedge(int u , int v)//压入一条边
{
	edge[sume].v = v;
	edge[sume].next = head[u];
	head[u] = sume++;

	edge[sume].v = u;
	edge[sume].next = head[v];
	head[v] = sume++;
}

void BFS(int x)
{
	queue<int> Q;
	memset(visit , false , sizeof(visit));
	Q.push(x);
	visit[x] = true;

	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();cout<<u<<endl;

		int e = head[u];
		while(e != -1)
		{
			int v = edge[e].v;
			if(!visit[v])
			{
				Q.push(v);
				visit[v] = true;
			}
			e = edge[e].next;
		}
	}
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt", "r", stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		sume = 0;
		for(int i = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v);
		}

		BFS(1);
	}
	return 0;
}
