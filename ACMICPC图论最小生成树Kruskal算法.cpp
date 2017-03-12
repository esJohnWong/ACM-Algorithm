#include<iostream>
#include<algorithm>

using namespace std;
/**==============================================**\
�㷨������
��С������kruskal�㷨�������˲��鼯�������Ͳ���Ҫ��
ͼ���˲������㷨ά��һ������A��A��װ�Ѿ����ҵ���
��С�������ıߡ��㷨��ʼʱ��ͼ�е�ÿ���㽨��һ����
�ϣ�Ȼ�����еı߰���Ȩֵ�Ĵ�С��С��������Ȼ��
���������Ľ����ÿ���ߵ���������м�飬�������
���㲻��һ����������������߼���A��ֱ���ҵ�n-1����
�ͽ�������Ϊ����n�������С���������ֻ��n-1���ߡ�
��Ϊ���һ���ߵ���������һ�������ڣ��������߼ӵ�A��
��ô��С�����������˻�·����Ҫ�����ǲ����л�·�ġ�
\**==============================================**/

int rank[16] , pre[12];//���鼯��ÿ����ĸ�����Լ�����
int n , m , se;//seΪA�бߵ�����

struct E//����ߵ����ݽṹ
{
	int u , v;
	int w;
}edge[16];

struct set//���弯��A
{
	int u , v;
	int w;
}A[12];

bool cmp(E e1 , E e2)//����ȽϺ���
{
	return e1.w < e2.w;
}

void makeset(int x)
{
	pre[x] = x;
	rank[x] = 0;
}

int findset(int x)
{
	if(pre[x] != x)
		pre[x] = findset(pre[x]);
	return pre[x];
}

void link(int x , int y)
{
	if(rank[x] > rank[y])
		pre[y] = x;
		else
		{
			pre[x] = y;
			if(rank[x] == rank[y])
				rank[y]++;
		}
}

void Union(int x , int y)
{
	link(findset(x) , findset(y));
}

void kruskal()
{
	for(int i = 1 ; i <= n ; i++)//�Ƚ�ÿ������һ������
		makeset(i);

	sort(edge , edge + m , cmp);//�Ա�����

	se = 0;
	for(int i = 0 ; i < m ; i++)//ÿ��ѭ���жϵ�ǰ���Ƿ�Ϸ�
	{
		if(se == n - 1)	break;//����ҵ�n-1�������������

		int u = edge[i].u;
		int v = edge[i].v;
		if(findset(u) != findset(v))//һ���ߵ������㲻���Ѿ���ͬһ������
		{
			Union(u , v);
			A[se].u = u;
			A[se].v = v;
			A[se].w = edge[i].w;
			se++;
		}
	}
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt", "r", stdin);
	while(cin>>n>>m)
	{
		for(int i = 0 ; i < m ; i++)
		{
			int u , v , w;
			cin>>u>>v>>w;
			edge[i].u = u;
			edge[i].v = v;
			edge[i].w = w;
		}

		kruskal();

		int res = 0;
		for(int i = 0 ; i < se ; i++)
		{
			res += A[i].w;
		}
		cout<<res<<endl;
	}
	return 0;
}
