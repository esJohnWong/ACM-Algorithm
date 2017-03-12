#include<iostream>
#include<cstring>

using namespace std;
/**===============================================**\
算法分析：
欧拉图即为从图上的一点出发经过所有的边一次且仅一次最
终回到起点
无向图的欧拉图要满足两个条件
1 不存在孤立的点，即图要是连通图
2 度数为奇数的点的个数为0（对有向图则是每个点的入度
要等于出度）

如果不回到原点但依然是经过所有边一次且仅一次即一笔画
问题为欧拉路径
无向图的欧拉路径要满足两个条件
1 不能有孤立的点存在
2 度数为奇数的点的个数为2，且这两个点一个是路径的起点
一个是路径的终点（对有向图只存在两个点，其中一个点的出
度比入度大1，为起点，另一个点入度比出度大一，为终点）

对无向图的欧拉回路如果找到一条边的序列，当从当前点出发
不能再找到一条没有访问的边，则这个点一定是这条边的序列
的始点，用深度优先搜索回溯就得到了欧拉回路
\**===============================================**/
struct E//定义边的数据结构
{
	int v;
	int num;//对边进行编号
	int next;
}edge[20];

int head[8] , n , m;
bool visit[8];//记录边是否被搜过
int path[8] , ansi , sume;
int degree[8];//每个点的度

void addedge(int u , int v , int i)//添加一条边并编号计算点的度
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

void  euler(int now)//寻找欧拉回路
{
	int e = head[now];
	while(e != -1)
	{
		if(!visit[e])
		{
			visit[e] = visit[e^1] = true;
			euler(edge[e].v);
			path[ansi++] = edge[e].num;//将找到的边放进最终的数组保存
		}
		e = edge[e].next;
	}
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt", "r", stdin);
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

		bool flag = true;//判断有不有欧拉回路
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
