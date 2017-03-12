#include<iostream>
#include<cstring>

using namespace std;
/**================================================**\
算法分析：
树的最小支配集是指从顶点V中取尽量少的点组成一个集合V'
使得V-V'中的所有点都与V'中的点有边相连。即剩下的所有
点都与取出的点有边相连，对一个点u要么在V’中要么与V'中
的点相邻。
求这个最小支配集要使用贪心的策略，先将这棵树用dfs搜索
一遍然后从搜索顺序的逆序开始对每个点进行判断，如果这
个点不在最小支配集中，也没有与支配集中的点相连，则如
果这个点的父结点不属于支配集，将这个点的父结点加入支
配集。对于根节点，其父结点就是自身。
\**================================================**/
struct E//定义边的数据结构
{
	int v;
	int next;
}edge[20];

int head[10] , pre[10];//pre为每个点的父结点
bool select[10];//判断一个点在深度优先时点是否被搜过
int newpos[10] , now;//newpos为深度优先时点的顺序，now为已搜索的点的个数
bool cover[10] , set[10];//cover为判断一个点是否被覆盖，set为最小支配集
int n , m;

void dfs(int x)//dfs搜索点的顺序
{
	newpos[now++] = x;
	for(int k = head[x] ; k != -1 ; k = edge[k].next)
	{
		if(!select[edge[k].v])
		{
			select[edge[k].v] = true;
			pre[edge[k].v] = x;
			dfs(edge[k].v);
		}
	}
}

int mds()
{
	memset(cover , false , sizeof(cover));
	memset(set , false , sizeof(set));

	int res = 0;//最小支配集点的个数

	for(int i = n - 1 ; i >= 0 ; i--)
	{
		int tmp = newpos[i];
		if(!cover[tmp])//如果一个点没有被覆盖
		{
			if(!set[pre[tmp]])//父结点不在支配集中
			{
				set[pre[tmp]] = true;//将父结点放入集合中
				res++;
			}
			//当前点，父结点，父结点的父结点都应该被覆盖
			cover[tmp] = cover[pre[tmp]] = cover[pre[pre[tmp]]] = true;
		}
	}
	return res;
}

void addedge(int u , int v , int &num)//添加一条边
{
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;

	edge[num].v = u;
	edge[num].next = head[v];
	head[v] = num++;
}

int main()
{
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v , num);
		}

		int source = 1;
		now = 0;
		pre[source] = source;
		memset(select , false , sizeof(select));
		select[source] = true;
		dfs(source);//从根节点开始搜

		int res = mds();//寻找最小支配集
		cout<<res<<endl;
		for(int i = 1 ; i <= n ; i++)//输出最小支配集
			if(set[i]) cout<<i<<" ";
		cout<<endl;
	}
	return 0;
}
