#include<iostream>
#include<cstring>
#include<queue>

using namespace std;
/**================================**\
�㷨������
SPFA�Ƕ�bellmanFord�ĸĽ����㷨���Ƚ�
Դ�㵽���е����̾�����Ϊ�����Դ
�㵽�Լ��ľ���Ϊ0����Դ�����һ���Ƚ�
�ȳ��Ķ��У�ÿ�ε������׵�Ԫ�أ��ɳ�
����׵�u���ڵĽڵ�v��dist�������д�
u��v��·�������v��dist�����Ҳ��ٶ���
�оͽ�v������С����ĳ����ĳ��Ӵ���
�����ܵ���������ڸ�Ȩ��·�����򲻴���
��Ȩ��·��
\**================================**/
const int MAX = 0xfffffff;

struct E
{
	int v , c , next;
}edge[12];
//distΪԴ�㵽ÿ��������·�����ƣ�preΪÿ����ĸ����
int head[6] , dist[6] , source , pre[6];
bool inq[6];//���һ�����Ƿ��ڶ���
int n , m , outq[6];//outqΪһ������ӵĴ���

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
	for(int i = 1 ; i <= n ; i++)//��ʼ��
	{
		dist[i] = MAX;
		pre[i] = 0;
		inq[i] = false;
	}
	dist[source] = 0;
	Q.push(source);
	inq[source] = true;

	memset(outq , 0 , sizeof(outq));

	while(!Q.empty())//ÿ�ε���һ�����׵ĵ�
	{
		int u = Q.front();
		Q.pop();

		inq[u] = false;
		outq[u]++;
		if(outq[u] > n) return false;//������Ӵ�������n

		int k = head[u];
		while(k != -1)//�޸Ĵ�u�����ıߵ�v���dist
		{
			int v = edge[k].v;
			if(dist[v] > dist[u] + edge[k].c)
			{
				dist[v] = dist[u] + edge[k].c;
				pre[v] = u;

				if(!inq[v])//���û�ڶ����оͷ������
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
