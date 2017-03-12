#include<iostream>
#include<cstring>

using namespace std;
/**===============================**\
算法分析：
求有向图的强连通分支，先把原图深度优
先搜索一遍，得到每个点的结束时间，即
每个点的子点都被搜完时这个点的结束搜
索时间。然后按照结束搜索时间递减的顺
序，把原图反向再搜索一遍，这时从某个
点可达的全部点组成了原图的一个强连通
分支。
\**===============================**/
struct E
{
	int v , c , next;
}edge[15] , tedge[15];//原图的边，反向边

int head[10] , thead[10];
int tim[10] , scc[10];//tim第一次搜索的结束时间，scc强连通分支
int n , m;
bool vist[10];//标记一个点是否被搜到

void dfsone(int cur , int &t)//对原图进行的深度优先搜索
{
	vist[cur] = true;
	for(int k = head[cur] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(!vist[v]) dfsone(v , t);
	}
	tim[++t] = cur;//当一个点的子点被搜索完成后，就计算这个点搜索完成时间
}

void dfstwo(int cur , int num)//第二次对反向图的搜索
{
	vist[cur] = true;
	scc[cur] = num;//num为对每个点属于哪个强连通分支的编号
	for(int k = thead[cur] ; k != -1 ; k = tedge[k].next)
	{
		int v = tedge[k].v;
		if(!vist[v]) dfstwo(v , num);
	}
}

int Kosaraju()
{
	memset(vist , false , sizeof(vist));
	int t = 0;
	for(int i = 1 ; i <= n ; i++)//第一遍原图的搜索得到结束时间
	{
		if(!vist[i]) dfsone(i , t);
	}

	int num = 0;
	memset(vist , false , sizeof(vist));
	for(int i = t ; i >= 1 ; i--)//第二遍反向图的搜索确定每个点属于哪个连通分支
	{
		int u = tim[i];//取得第i时间结束的点
		if(!vist[u]) dfstwo(u , num++);
	}
	return num;
}

void addedge(int u , int v , int &num)//压入边
{
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num;

	tedge[num].v = u;
	tedge[num].next = thead[v];
	thead[v] = num++;
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		memset(thead , -1 , sizeof(thead));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v , num);
		}

		int num = Kosaraju();
		cout<<num<<endl;
		for(int i = 1 ; i <= n ; i++)
			cout<<i<<" "<<scc[i]<<endl;
	}
	return 0;
}
