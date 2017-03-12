#include<iostream>
#include<cstring>
#include<queue>

using namespace std;
/**============================**\
�㷨������
��Դ�㵽������̾���Ϊ��1�̾���
���е�2�̣���3�̾��롭���k�̾���
��������A*�㷨��˼�룬��
���ۺ��� = ��ǰֵ + ��ǰλ�õ��յ�ľ���
f(p) = g(p) + h(p)��ÿ����չ���ۺ���
ֵ��С��һ����
g(p)Ϊ��Դ�㵽p�����߹���ʵ�ʾ���
h(p)Ϊp�㵽�յ�ľ��롣h(p)ͨ����
ͼ�������յ�ΪԴ�㣬Դ��Ϊ�յ㣬ͨ
��SPFA�����̾��롣
��һ�����ȼ������Ƚ�Դ��ѹ����С�
ÿ�ε���һ��fֵ��С�ĵ㣬���յ��
���Ӵ����ﵽkʱ��ʱ��gֵ��Ϊ����
����ɨ���뵱ǰ�����ڵĵ㡣
\**============================**/
const int MAX = 0xfffffff;

struct node
{
	int v;
	int g , f ;
	bool operator<(const node & a) const
	{
		if(a.f == f) return a.g < g;
		return a.f < f;
	}
};

struct E
{
	int v , c , next;
}edge[12] , reedge[12];//reedgeΪͼ�ķ����

int head[7] , rehead[7] , h[7];//hΪ�߷���ʱ����ľ���
int start , end , n , m , K;

bool SPFA()//spfa�㷨
{
	queue<int> Q;
	bool inq[6];
	int outq[6];
	for(int i = 1 ; i <= n ; i++)
	{
		inq[i] = false;
		outq[i] = 0;
		h[i] = MAX;
	}
	inq[end] = true;
	h[end] = 0;
	Q.push(end);

	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		inq[u] = false;
		outq[u]++;

		if(outq[u] > n) return false;

		for(int k = rehead[u] ; k != -1 ; k = reedge[k].next)
		{
			int v = reedge[k].v;
			if(h[v] > h[u] + reedge[k].c)
			{
				h[v] = h[u] + reedge[k].c;
				if(!inq[v])
				{
					inq[v] = true;
					Q.push(v);
				}
			}
		}
	}
	return true;
}

int Astar()//A*�㷨
{
	priority_queue<node> Q;
	node s , t;
	int cnt = 0;//�����յ���ӵĴ���

	if(start == end) K++;//ȥ��Դ�㵽Դ��Ϊ0����������
	if(h[start] == MAX) return -1;

	s.v = start;//���Ƚ�Դ��ѹ�����
	s.g = 0;//��ǰ���ߵľ���Ϊ0
	s.f = h[start];//���ϵ��յ�ľ���Ϊh[start]
	Q.push(s);

	while(!Q.empty())
	{
		s = Q.top();//����fֵ��С�ĵ�
		Q.pop();

		if(s.v == end) cnt++;
		if(cnt == K) return s.g;//�ѵõ���k��·
		//����s.v���ڵĵ�Ҳѹ�����
		for(int k = head[s.v] ; k != -1 ; k = edge[k].next)
		{
			t.v = edge[k].v;
			t.g = s.g + edge[k].c;//��ǰ���ߵľ���Ϊǰһ�������ߵľ������ǰһ�㵽��ǰ��ľ���
			t.f = t.g + h[t.v];//·�����ۺ���Ϊ���ߵľ�����ϵ�ǰ�㵽�յ�ľ���
			Q.push(t);//�������ѹ�����
		}
	}
	return -1;
}

void addedge(int u , int v , int c , int &num)
{//ѹ�������
	edge[num].c = c;
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num;
//ѹ�뷴���
	reedge[num].c = c;
	reedge[num].v = u;
	reedge[num].next = rehead[v];
	rehead[v] = num;
	num++;
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		memset(rehead , -1 , sizeof(rehead));

		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			addedge(u , v , c , num);
		}

		start = 1 , K = 1 , end = 5;

		SPFA();
		int ans = Astar();
		cout<<ans<<endl;
	}
	return 0;
}
