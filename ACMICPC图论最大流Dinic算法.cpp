/**==================================================**\
�㷨������
Dinic�㷨��SAP�㷨������ͬ��֮����Ѳ�����·��ɷֲ�
���磬ÿ��Ѱ�Ҷ�����̵�·��ȥ���㡣�ڲ���������ÿ����
����һ�����ţ�ÿ�ζ�����level[v]=level[u]+1�ı�<u,v>
���㡣����ڲ����������ÿ������ʱ�޷��Ի������˵
���Ѿ�û������·�ˡ�
\**==================================================**/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX = 0xffffff;

struct unit
{
	int v , c , next;
}edge[25];
//levelΪÿ����Ĳ������
int head[10] , level[10];
int  n , m , source , sink;

void addEdge(int u , int v , int c , int &num)//���һ����
{
	edge[num].v = v;
	edge[num].c = c;
	edge[num].next = head[u];
	head[u] = num++;

	edge[num].c = 0;
	edge[num].v = u;
	edge[num].next = head[v];
	head[v] = num++;
}

bool searchLevel()//��bfs��ÿ������
{
	memset(level , -1 , sizeof(level));
	queue<int> Q;
	Q.push(source);
	level[source] = 0;

	while(!Q.empty())
	{
		int u = Q.front();
		if(u == sink) return true;
		Q.pop();

		for(int k = head[u] ; k != -1 ; k = edge[k].next)
		{
			int v = edge[k].v;
			if(edge[k].c && level[v] == -1)
			{
				level[v] = level[u]+1;
				Q.push(v);
			}
		}
	}
	return false;
}

int DinicDfs(int u , int minf)
{//minfΪ��ǰ����·����ƿ���ߵ�����
	if(u == sink)
		return minf;

	int ret = 0;//�ӵ�ǰ���������ҵ�����������֮��
	for(int k =  head[u] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(edge[k].c && level[v] == level[u]+1)
		{//min(minf-ret , edge[k].c)����˼���޸�����·����ƿ���ߵ�����
			int f = DinicDfs(v , min(minf-ret , edge[k].c));
			edge[k].c -= f;
			edge[k^1].c += f;
			ret +=f;
			//ƿ���ߵ����������Ĵ���˵���ӵ�ǰ�����û������·�ˣ�Ҫ��˷
			if(ret == minf) return ret;
		}
	}
	return ret;
}

int Dinic()
{
	int maxFlow = 0;
	while(searchLevel())//�������绹���Էֲ�˵����Դ�㵽��㻹����������·��
	{
		maxFlow += DinicDfs(source , MAX);
	}
	return maxFlow;
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			addEdge(u , v , c , num);
		}

		source = 1 , sink = 4;
		int maxFlow = Dinic();
		cout<<maxFlow<<endl;
	}
	return 0;
}
