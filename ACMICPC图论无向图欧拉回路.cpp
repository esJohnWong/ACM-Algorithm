#include<iostream>
#include<cstring>

using namespace std;
/**===============================================**\
�㷨������
ŷ��ͼ��Ϊ��ͼ�ϵ�һ������������еı�һ���ҽ�һ����
�ջص����
����ͼ��ŷ��ͼҪ������������
1 �����ڹ����ĵ㣬��ͼҪ����ͨͼ
2 ����Ϊ�����ĵ�ĸ���Ϊ0��������ͼ����ÿ��������
Ҫ���ڳ��ȣ�

������ص�ԭ�㵫��Ȼ�Ǿ������б�һ���ҽ�һ�μ�һ�ʻ�
����Ϊŷ��·��
����ͼ��ŷ��·��Ҫ������������
1 �����й����ĵ����
2 ����Ϊ�����ĵ�ĸ���Ϊ2������������һ����·�������
һ����·�����յ㣨������ͼֻ���������㣬����һ����ĳ�
�ȱ���ȴ�1��Ϊ��㣬��һ������ȱȳ��ȴ�һ��Ϊ�յ㣩

������ͼ��ŷ����·����ҵ�һ���ߵ����У����ӵ�ǰ�����
�������ҵ�һ��û�з��ʵıߣ��������һ���������ߵ�����
��ʼ�㣬����������������ݾ͵õ���ŷ����·
\**===============================================**/
struct E//����ߵ����ݽṹ
{
	int v;
	int num;//�Ա߽��б��
	int next;
}edge[20];

int head[8] , n , m;
bool visit[8];//��¼���Ƿ��ѹ�
int path[8] , ansi , sume;
int degree[8];//ÿ����Ķ�

void addedge(int u , int v , int i)//���һ���߲���ż����Ķ�
{
	edge[sume].v = v;
	edge[sume].num = i;
	edge[sume].next = head[u];
	head[u] = sume++;

	edge[sume].v = u;
	edge[sume].num = i;
	edge[sume].next = head[v];
	head[v] = sume++;

	degree[u]++;
	degree[v]++;
}

void  euler(int now)//Ѱ��ŷ����·
{
	int e = head[now];
	while(e != -1)
	{
		if(!visit[e])
		{
			visit[e] = visit[e^1] = true;
			euler(edge[e].v);
			path[ansi++] = edge[e].num;//���ҵ��ı߷Ž����յ����鱣��
		}
		e = edge[e].next;
	}
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt", "r", stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		memset(visit , false , sizeof(visit));
		memset(degree , 0 , sizeof(degree));
		ansi = sume = 0;

		for(int i = 1 ; i <= m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v , i);
		}

		bool flag = true;//�ж��в���ŷ����·
		for(int j = 1 ; j <= n ; j++)
			if(degree[j] == 0 || degree[j] % 2 != 0)
			{
				flag = false;
				break;
			}

		if(flag)
		{
			euler(1);
			for(int j = 0 ; j < ansi ; j++)
				cout<<path[j]<<" ";
			cout<<endl;
		}
		else cout<<"no this path\n";
	}
	return 0;
}
