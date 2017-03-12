#include<iostream>
#include<cstring>

using namespace std;
/**============================**\
�㷨������
�㷨������������������ѵ�һ���µ�
���Ͱ�����������һ�����ϣ�Ȼ��
�����ѵ�ǰ�ڵ�������������һ����
��u����v���v���ѵ����������������
����<u , v>������һ����v���ڼ��ϵ�
���ȣ�������һ���ڵ��������Ͱ�����
�γɵļ��ϵ�������Ϊ��ǰ��u
\**============================**/
struct Q//����һ��ѯ�ʵ����ݽṹ
{
	int v;
	int lca;//<u,v>������
	bool out;//�ж�<u,v>�������Ƿ������
	int next;
}query[9];

struct E//�������ߵļ���
{
	int v ;
	int next;
}edge[18];

int ehead[11] , qhead[11];
int pre[11] , tol;
bool visit[11];
int n , m , k;//n������,m��ѯ�ʣ�k����

int findset(int x)//���鼯�Ĳ��Ҹ���㲢·��ѹ��
{
	if(x != pre[x])
		pre[x] = findset(pre[x]);
	return pre[x];
}

void LCA(int u)//Ѱ������
{
	pre[u] = u;//�ѵ�ǰ�ڵ�����һ������
	visit[u] = true;//��ǰ�ڵ��Ѿ�������

	for(int k = ehead[u] ; k != -1 ; k = edge[k].next)//ɨ��������u���ڵĵ�
	{
		if(!visit[edge[k].v])//��u���ڵĵ���
		{
			LCA(edge[k].v);
			pre[edge[k].v] = u;//����u��һ��������u��Ϊ����������
		}
	}

	for(int k = qhead[u] ; k != -1 ; k = query[k].next)//��ѯ��u�йصĲ���
	{
		if(visit[query[k].v])//���v��������˵�������ҵ�<u,v>�������ˣ����vû�б����ʾ͵�v���ѵ�ʱu�Ѿ�������
		{
			query[k].lca = findset(query[k].v);//<u,v>������Ϊv���ڼ��ϵ�����
			query[k ^ 1].lca = query[k].lca;//��һ����ҲҪ���
		}
	}
}

void addedge(int u , int v)//������ı�
{
	edge[tol].v = v;
	edge[tol].next = ehead[u];
	ehead[u] = tol++;
}

void addquery(int u , int v)//���ѯ��
{
	query[tol].v = v;
	query[tol].next = qhead[u];
	query[tol].out = false;
	qhead[u] = tol++;

	query[tol].v = u;
	query[tol].next = qhead[v];
	query[tol].out = false;
	qhead[v] = tol++;
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt", "r", stdin);
	while(cin>>n>>m>>k)
	{
		tol = 0;
		memset(ehead , -1 , sizeof(ehead));

		for(int i = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v);
		}

		tol = 0;
		memset(qhead , -1 , sizeof(qhead));

		for(int i = 0 ; i < k ; i++)
		{
			int u , v;
			cin>>u>>v;
			addquery(u , v);
		}

		LCA(1);

		for(int i = 1 ; i <= n ; i++)//���ѯ�ʽ��
		{
			int t = qhead[i];
			while(t != -1)
			{
				if(!query[t].out)
				{
					cout<<i<<" "<<query[t].v<<" "<<query[t].lca<<endl;
					query[t].out = true;
					query[t^1].out = true;
				}
				t = query[t].next;
			}
		}
	}
	return 0;
}
