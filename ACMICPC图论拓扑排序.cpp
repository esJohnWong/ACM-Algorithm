#include<iostream>
#include<queue>

using namespace std;
/**===============================**\
算法分析：
拓扑排序是对有向无回路图来说的，简单
的说就是一条边的起点要排在终点的左边
算法开始的时候从图中选择一个入度为0
的点，然后再图中删除该点（其实实际
操作就是把从这个点出发的边的终点的
入度减一就可以了）把这个点放到排序
队列中，重复上面的步骤，直到不存在
没有前驱的点为止，所得的序列就是拓扑
排序的序列
\**===============================**/
struct E//定义边的数据结构
{
	int v;
	int next;
}edge[22];

int head[11] , n , m , sume;
int indegree[11];//每个点的入度

void addedge(int u , int v)//添加一条边
{
	edge[sume].v = v;
	edge[sume].next = head[u];
	head[u] = sume++;
	indegree[v]++;//计算v的入度
}

void topsort()//拓扑排序主函数
{
	queue<int> Q;

	for(int i = 1 ; i <= n ; i++)//先将所有入度为0的点压入队列
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
			indegree[v]--;//修改这条边终点v的入度相当于删除u
			if(!indegree[v])//如果入度为0就压入队列
				Q.push(v);
			e = edge[e].next;
		}
	}
	cout<<endl;
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt", "r", stdin);
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
