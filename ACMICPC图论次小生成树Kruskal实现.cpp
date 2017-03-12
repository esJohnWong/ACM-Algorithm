#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
/**=================================================**\
�㷨������
Ҫ����С������֮��Ĵ�С���������������ҵ�һ�ô�С��
����������ڵ�x,y֮���ټ�һ����[x,y]��ô�ض��γ���
һ����,�����x,y֮��ı߳����¼ӵ�[x,y]��������һ��
��ɾ�����γ���һ�ô�С�������������е�û������С������
�߶������滻�������Ӧ�Ĵ�С������Ȩֵ�����ȡ����Ȩֵ
��С�ľ���Ҫ��Ĵ�С������,��Ҫע���������Ĵ�С����
����Ȩֵ���ܺ���С����������ȣ�˵����С��������Ψһ
\**=================================================**/
const int MAX = 0xfffffff;

struct E//����ߵ����ݽṹ
{
	int u , v;
	int w;
	bool select;//����������Ƿ�����С��������
}edge[30];

struct S//����һ�����ϵ����ݽṹ�����еĵ��ǵ�ǰ����С�������еĵ�
{
	int v;
	int next;
}set[12];

int pre[12] , rank[12];
int head[12] , tail[12];
int length[12][12];//���ÿ�����������ߵ�Ȩֵ
int n , m;

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
	if(rank[x] < rank[y])
		pre[x] = y;
		else
		{
			pre[y] = x;
			if(rank[x] == rank[y])
				rank[x]++;
		}
}

void Union(int x , int y)
{
	link(findset(x) , findset(y));
}

void init()//��ʼ��
{
	memset(head , -1 , sizeof(head));
	for(int i = 0 ; i < n ; i++)//�Ȱ�ÿ���㶼�ŵ�������
	{
		set[i].v = i + 1;
		set[i].next = head[i + 1];
		head[i + 1] = i;//������set�еĴ洢�߽�
		tail[i + 1] = i;
	}

	for(int i = 0 ; i < m ; i++)
	{
		int u , v , w ;
		cin>>u>>v>>w;
		edge[i].u = u;
		edge[i].v = v;
		edge[i].w = w;
		edge[i].select = false;
	}
}

bool cmp(E e1 , E e2)
{
	return e1.w < e2.w;
}

void kruskal()
{
	for(int  i = 1 ; i <= n ; i++)
		makeset(i);

	int k = 0;
	sort(edge , edge + m , cmp);

	for(int i = 0 ; i < m ; i++)
	{
		if(k == n - 1) break;
		int x = findset(edge[i].u);
		int y = findset(edge[i].v);

		if(x != y)//һ����������xΪ����㣬��һ������yΪ�����
		{//��ǰ����ı�һ����[x,y]������
			for(int e1 = head[x] ; e1 != -1 ; e1 = set[e1].next)
			{
				for(int e2 = head[y] ; e2 != -1 ; e2 = set[e2].next)
				{
					int u = set[e1].v , v = set[e2].v;
					length[u][v] = length[v][u] = edge[i].w;
				}
			}

			Union(x , y);
			set[tail[y]].next = head[x];//�ϲ������㼯
			tail[y] = tail[x];
			head[x] = head[y];//��Ϊ��֪���ϲ���x��y˭�Ǹ����Ծ���yΪ׼���head[x],head[y]ָ��ͬһ���ط�
			k++;//��¼��ѡ�ߵ�����
			edge[i].select = true;
		}
	}
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt", "r", stdin);
	while(cin>>n>>m)
	{
		init();
		int mst = 0 , secmst = MAX;
		kruskal();

		for(int i = 0 ; i < m ; i++)//�����С��������Ȩֵ
		{
			if(edge[i].select) mst += edge[i].w;
		}

		for(int i = 0 ; i < m ; i++)
		{
			if(!edge[i].select)//�����ǰ��û�б�ѡ��ͼ�����С��������ɾ��������
			{
				int u = edge[i].u , v = edge[i].v;
				int tmst = mst + edge[i].w - length[u][v];
				secmst = min(secmst , tmst);
			}
		}

		cout<<secmst<<endl;
	}
	return 0;
}
