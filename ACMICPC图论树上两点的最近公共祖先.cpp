#include<iostream>
#include<cstring>

using namespace std;
/**============================**\
算法分析：
算法用深度优先搜索，当搜到一个新的
结点就把这个结点做成一个集合，然后
继续搜当前节点的子树，如果有一个结
点u，对v如果v被搜到，由于是深度优先
所以<u , v>的祖先一定是v所在集合的
祖先，当搜完一个节点的子树后就把子树
形成的集合的祖先置为当前的u
\**============================**/
struct Q//定义一个询问的数据结构
{
	int v;
	int lca;//<u,v>的祖先
	bool out;//判断<u,v>的祖先是否被输出了
	int next;
}query[9];

struct E//定义树边的集合
{
	int v ;
	int next;
}edge[18];

int ehead[11] , qhead[11];
int pre[11] , tol;
bool visit[11];
int n , m , k;//n个顶点,m个询问，k条边

int findset(int x)//并查集的查找父结点并路径压缩
{
	if(x != pre[x])
		pre[x] = findset(pre[x]);
	return pre[x];
}

void LCA(int u)//寻找最先
{
	pre[u] = u;//把当前节点做成一个集合
	visit[u] = true;//当前节点已经被访问

	for(int k = ehead[u] ; k != -1 ; k = edge[k].next)//扫描所有与u相邻的点
	{
		if(!visit[edge[k].v])//从u相邻的点搜
		{
			LCA(edge[k].v);
			pre[edge[k].v] = u;//搜完u的一棵子树把u置为子树的祖先
		}
	}

	for(int k = qhead[u] ; k != -1 ; k = query[k].next)//查询与u有关的操作
	{
		if(visit[query[k].v])//如果v被访问了说明可以找到<u,v>的祖先了，如果v没有被访问就当v被搜到时u已经被访问
		{
			query[k].lca = findset(query[k].v);//<u,v>的祖先为v所在集合的祖先
			query[k ^ 1].lca = query[k].lca;//另一条边也要标记
		}
	}
}

void addedge(int u , int v)//添加树的边
{
	edge[tol].v = v;
	edge[tol].next = ehead[u];
	ehead[u] = tol++;
}

void addquery(int u , int v)//添加询问
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
	freopen("D:\\cruanjian\\桌面\\in.txt", "r", stdin);
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

		for(int i = 1 ; i <= n ; i++)//输出询问结果
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
