#include<iostream>
#include<cstring>

using namespace std;

struct E
{
	int v;
	int next;
}edge[20];//用链式前向星存储边

int head[9] , sume , n , m;//n点，m边，sume当前边插入的位置
bool visit[9];

void add_edge(int u ,int v)//插入一条边
{
	edge[sume].v = v;
	edge[sume].next = head[u];
	head[u] = sume++;
}

void DFS(int x)//深度优先搜索
{
	visit[x] = true;

	cout<< x <<" ";
	for(int i = head[x] ; i != -1 ; i = edge[i].next)
	{
		if(! visit[edge[i].v])
		{
			DFS(edge[i].v);
		}
	}
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt", "r", stdin);
	while(cin >> n >> m)
	{
		sume = 0;
		memset(visit , false , sizeof(visit));
		memset(head , -1 ,sizeof(head));
		for(int i = 0 ; i < m ; i++)
		{
			int u , v;
			cin >> u >> v;
			add_edge(u , v);//插入为无向边
			add_edge(v , u);
		}

		for(int j = 1 ; j <= n ; j++)
		{
			if(! visit[j])
			{
				DFS(j);
			}
		}
	}
	return 0;
}
