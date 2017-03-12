#include<iostream>
#include<cstring>

using namespace std;

struct E
{
	int v;
	int next;
}edge[20];//����ʽǰ���Ǵ洢��

int head[9] , sume , n , m;//n�㣬m�ߣ�sume��ǰ�߲����λ��
bool visit[9];

void add_edge(int u ,int v)//����һ����
{
	edge[sume].v = v;
	edge[sume].next = head[u];
	head[u] = sume++;
}

void DFS(int x)//�����������
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
	freopen("D:\\cruanjian\\����\\in.txt", "r", stdin);
	while(cin >> n >> m)
	{
		sume = 0;
		memset(visit , false , sizeof(visit));
		memset(head , -1 ,sizeof(head));
		for(int i = 0 ; i < m ; i++)
		{
			int u , v;
			cin >> u >> v;
			add_edge(u , v);//����Ϊ�����
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
