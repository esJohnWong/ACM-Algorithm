#include<iostream>
#include<cstring>

using namespace std;
/**========================================**\
�㷨������
bellmanFord�㷨�������и�Ȩ�ߵ�ͼ�����·����
����и�Ȩ��·���㷨����false�����򷵻�true��
�㷨��ʼʱ��dist��Ϊ�����Դ���distΪ0��
�㷨����n-1��ѭ������ÿ�ζ������еı��ɳ�һ��
��Ϊn������ļ����·��Ҳ��n-1���ߡ��ɳ�
����Ϊ���dist[v] > dist[u] + w[u][v]�����
dist[v] = dist[u] + w[u][v]��
���ͼ�д��ڸ�Ȩ��·��������һ����
dist[v] > dist[u] + w[u][v]
\**========================================**/
const int MAX = 0xffffff;

struct E//�ߵ����ݽṹ
{
	int v , c , next;//cΪ�ߵ�Ȩֵ
}edge[12];
//distΪԴ�㵽ÿ�������̾���
int head[6] , dist[6] , pre[6];
int source , n , m;//n�ǵ�ĸ�����m�Ǳߵĸ���

void addedge(int u , int v , int c , int &num)//ѹ��һ����
{
	edge[num].c = c;
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;
}

bool bellmanFord()
{
	for(int i = 1 ; i <= n ; i++)//��ʼ��
	{
		dist[i] = MAX;
		pre[i] = 0;
	}
	dist[source] = 0;//Դ�㵽�Լ��ľ���Ϊ0

	for(int i = 1 ; i < n ; i++)//n-1�β���
	{
		for(int u = 1 ; u <= n ; u++)//ÿ���ɳ����еı�
		{
			if(dist[u] == MAX) continue;
			int k = head[u];
			while(k != -1)
			{
				int v = edge[k].v;
				if(edge[k].c != MAX && dist[v] > dist[u] + edge[k].c)//�ɳڲ���
				{
					dist[v] = dist[u] + edge[k].c;
					pre[v] = u;
				}
				k = edge[k].next;
			}
		}
	}

	for(int u = 1 ; u <= n ; u++)//�ж��Ƿ��и�Ȩ��·
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
