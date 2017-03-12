/**==================================================**\
算法分析：
Dinic算法和SAP算法有异曲同工之妙，它把残留网路变成分层
网络，每次寻找都找最短的路径去增广。在残留网络上每个点
都有一个层编号，每次都按照level[v]=level[u]+1的边<u,v>
增广。如果在残留网络里对每个点编号时无法对汇点编号则说
明已经没有增广路了。
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
//level为每个点的层数编号
int head[10] , level[10];
int  n , m , source , sink;

void addEdge(int u , int v , int c , int &num)//添加一条边
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

bool searchLevel()//用bfs对每个点编号
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
{//minf为当前增广路径中瓶颈边的容量
	if(u == sink)
		return minf;

	int ret = 0;//从当前这个点出发找到的所有流量之和
	for(int k =  head[u] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(edge[k].c && level[v] == level[u]+1)
		{//min(minf-ret , edge[k].c)的意思是修改增广路径中瓶颈边的容量
			int f = DinicDfs(v , min(minf-ret , edge[k].c));
			edge[k].c -= f;
			edge[k^1].c += f;
			ret +=f;
			//瓶颈边的容量被消耗殆尽说明从当前点出发没有增广路了，要回朔
			if(ret == minf) return ret;
		}
	}
	return ret;
}

int Dinic()
{
	int maxFlow = 0;
	while(searchLevel())//残留网络还可以分层说明从源点到汇点还可以找增广路径
	{
		maxFlow += DinicDfs(source , MAX);
	}
	return maxFlow;
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt" , "r" , stdin);
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
