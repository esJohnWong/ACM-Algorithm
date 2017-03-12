/**=======================================================**\
�㷨������
��С���������������������ͬʱʹ�����õ������ķ�����С����
Ѱ������·����ͬʱ���ǰ���ÿ��Ѱ�ҵ���·���ķ���������С��
��ô�������õ�������ķ���Ҳһ������С�ġ���Ϊ����ߵķ�
���Ǹ�ֵ���Բ���SPFA�㷨������·����
\**=======================================================**/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

const int MAX = 0xfffffff;

struct unit
{//expΪÿ���ߵķ��ã�cΪ����
	int v , c , exp , next;
}edge[22];
//castΪ��ÿ���㵽Դ�����С���ã�routeΪ����·���ߣ�preΪÿ�����ǰ��
int head[8] , cast[8] , route[8] , pre[8];
int n , m , source , sink;//�㣬�ߣ�Դ����
bool inqueue[8];//��־һ�����Ƿ��ڶ�������
//���һ����
void addEdge(int u , int v , int c , int exp , int &num)
{
	edge[num].c = c;
	edge[num].exp = exp;
	edge[num].next = head[u];
	edge[num].v = v;
	head[u] = num++;

	edge[num].c = 0;
	edge[num].exp = -exp;//����ߵķ�����Ϊԭ�ߵ��෴��
	edge[num].next = head[v];
	edge[num].v = u;
	head[v] = num++;
}

bool SPFA()//����һ��������С������·��
{
	queue<int> Q;
	memset(inqueue , false , sizeof(inqueue));
	memset(pre , -1 , sizeof(pre));
	for(int i = 1 ; i <= n ; i++)
		cast[i] = MAX;
	Q.push(source);
	cast[source] = 0;
	inqueue[source] = true;

	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		inqueue[u] = false;

		for(int k = head[u] ; k != -1 ; k = edge[k].next)
		{
			if(edge[k].c)//�ߴ���
			{
				int v = edge[k].v;
				if(cast[v]-edge[k].exp > cast[u])//�����ɳ�����
				{
					cast[v] = cast[u]+edge[k].exp;
					pre[v] = u;
					route[v] = k;
					if(!inqueue[v])
					{
						Q.push(v);
						inqueue[v] = true;
					}
				}
			}
		}
	}

	if(cast[sink] == MAX)
		return false;
	return true;
}

int minCastFlow(int &maxFlow)
{
	int minCast = 0;
	maxFlow = 0;
	while(SPFA())
	{
		int u = sink;
		int minf = MAX;
		while(pre[u] != -1)//�ҵ�����·���ϵ�ƿ����
		{
			if(minf > edge[route[u]].c)
				minf = edge[route[u]].c;
			u = pre[u];
		}

		u = sink;
		while(pre[u] != -1)//�޸�����·���ϵ�Ȩֵ
		{
			edge[route[u]].c -= minf;
			edge[route[u]^1].c += minf;
			u = pre[u];
		}

		maxFlow += minf;//�޸�������ͷ���
		minCast += minf*cast[sink];
	}
	return minCast;
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v , c , exp;
			cin>>u>>v>>c>>exp;
			addEdge(u , v , c , exp , num);
		}

		source = 1 , sink = 4;
		int maxFlow ;
		int minCast = minCastFlow(maxFlow);
		cout<<maxFlow<<" "<<minCast<<endl;
	}
	return 0;
}
