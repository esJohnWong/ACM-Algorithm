/**=======================================================**\
算法分析：
最小费用流就是在求最大流的同时使得所得到的流的费用最小，在
寻找增广路径的同时我们按照每次寻找到的路径的费用总是最小的
那么最后所求得的最大流的费用也一定是最小的。因为反向边的费
用是负值所以采用SPFA算法求增广路径。
\**=======================================================**/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

const int MAX = 0xfffffff;

struct unit
{//exp为每条边的费用，c为容量
	int v , c , exp , next;
}edge[22];
//cast为从每个点到源点的最小费用，route为增广路径边，pre为每个点的前驱
int head[8] , cast[8] , route[8] , pre[8];
int n , m , source , sink;//点，边，源，汇
bool inqueue[8];//标志一个点是否在队列里面
//添加一条边
void addEdge(int u , int v , int c , int exp , int &num)
{
	edge[num].c = c;
	edge[num].exp = exp;
	edge[num].next = head[u];
	edge[num].v = v;
	head[u] = num++;

	edge[num].c = 0;
	edge[num].exp = -exp;//反向边的费用置为原边的相反数
	edge[num].next = head[v];
	edge[num].v = u;
	head[v] = num++;
}

bool SPFA()//搜索一条费用最小的增广路径
{
	queue<int> Q;
	memset(inqueue , false , sizeof(inqueue));
	memset(pre , -1 , sizeof(pre));
	for(int i = 1 ; i <= n ; i++)
		cast[i] = MAX;
	Q.push(source);
	cast[source] = 0;
	inqueue[source] = true;

	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		inqueue[u] = false;

		for(int k = head[u] ; k != -1 ; k = edge[k].next)
		{
			if(edge[k].c)//边存在
			{
				int v = edge[k].v;
				if(cast[v]-edge[k].exp > cast[u])//满足松弛条件
				{
					cast[v] = cast[u]+edge[k].exp;
					pre[v] = u;
					route[v] = k;
					if(!inqueue[v])
					{
						Q.push(v);
						inqueue[v] = true;
					}
				}
			}
		}
	}

	if(cast[sink] == MAX)
		return false;
	return true;
}

int minCastFlow(int &maxFlow)
{
	int minCast = 0;
	maxFlow = 0;
	while(SPFA())
	{
		int u = sink;
		int minf = MAX;
		while(pre[u] != -1)//找到增广路径上的瓶颈边
		{
			if(minf > edge[route[u]].c)
				minf = edge[route[u]].c;
			u = pre[u];
		}

		u = sink;
		while(pre[u] != -1)//修改增广路径上的权值
		{
			edge[route[u]].c -= minf;
			edge[route[u]^1].c += minf;
			u = pre[u];
		}

		maxFlow += minf;//修改最大流和费用
		minCast += minf*cast[sink];
	}
	return minCast;
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v , c , exp;
			cin>>u>>v>>c>>exp;
			addEdge(u , v , c , exp , num);
		}

		source = 1 , sink = 4;
		int maxFlow ;
		int minCast = minCastFlow(maxFlow);
		cout<<maxFlow<<" "<<minCast<<endl;
	}
	return 0;
}
