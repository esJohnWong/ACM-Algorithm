#include<iostream>
#include<cstring>

using namespace std;
/**===============================**\
�㷨������
DAGͼ�������޻�·ͼ��������̾�����
�Ǵ��ڵģ���Ϊ�������и�Ȩ��·��
���ȶ�ͼ������������Ȼ����������
���˳���ÿ�����ȥ�ı߽����ɳڲ�����
\**===============================**/
const int MAX = 0xfffffff;

struct E
{
	int v, c , next;
}edge[12];
//queueΪ��������Ľ����indegreeΪ������,distΪ���Ľ����preΪÿ�����ǰ�����
int head[7] , queue[7] , indegree[7] , dist[7] , pre[7];
int n , m , source;//sourceΪԴ��

int  topsort()//��������
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
			if(indegree[edge[k].v] == 0)//ÿ��Ѱ�����Ϊ0�ĵ�
			{
				queue[iq++] = edge[k].v;
			}
		}
	}
	return iq;
}

void DAG()
{
	for(int i = 1 ; i <= n ; i++)//��ʼ������
	{
		dist[i] = MAX;
		pre[i] = 0;
	}
	dist[source] = 0;

	int iq = topsort();//������������

	for(int i = 0 ; i < iq ; i++)//�������������ÿ����ĳ��߽����ɳڲ���
	{
		for(int k = head[queue[i]] ; k != -1 ; k = edge[k].next)
		{
			int v = edge[k].v;
			if(dist[v] > dist[queue[i]] + edge[k].c)//�����ɳ�
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
