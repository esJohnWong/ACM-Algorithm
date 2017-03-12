#include<iostream>
#include<queue>

using namespace std;
/**===============================**\
�㷨������
���������Ƕ������޻�·ͼ��˵�ģ���
��˵����һ���ߵ����Ҫ�����յ�����
�㷨��ʼ��ʱ���ͼ��ѡ��һ�����Ϊ0
�ĵ㣬Ȼ����ͼ��ɾ���õ㣨��ʵʵ��
�������ǰѴ����������ıߵ��յ��
��ȼ�һ�Ϳ����ˣ��������ŵ�����
�����У��ظ�����Ĳ��裬ֱ��������
û��ǰ���ĵ�Ϊֹ�����õ����о�������
���������
\**===============================**/
struct E//����ߵ����ݽṹ
{
	int v;
	int next;
}edge[22];

int head[11] , n , m , sume;
int indegree[11];//ÿ��������

void addedge(int u , int v)//���һ����
{
	edge[sume].v = v;
	edge[sume].next = head[u];
	head[u] = sume++;
	indegree[v]++;//����v�����
}

void topsort()//��������������
{
	queue<int> Q;

	for(int i = 1 ; i <= n ; i++)//�Ƚ��������Ϊ0�ĵ�ѹ�����
	{
		if(!indegree[i])
			Q.push(i);
	}

	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();cout<<u<<" ";

		int e = head[u];
		while(e != -1)
		{
			int v = edge[e].v;
			indegree[v]--;//�޸��������յ�v������൱��ɾ��u
			if(!indegree[v])//������Ϊ0��ѹ�����
				Q.push(v);
			e = edge[e].next;
		}
	}
	cout<<endl;
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt", "r", stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		memset(indegree , 0 , sizeof(indegree));
		sume = 0;

		for(int i = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v);
		}

		topsort();
	}
	return 0;
}
