#include<iostream>
#include<cstring>

using namespace std;
/**==================================**\
算法分析:
树的最小点覆盖就是从V中取尽量少的点使得
E中所有的边都与取出来的点相连。
这个算法也是基于贪心思想，首先按照对树的
深度优先次序的反序进行，如果当前点和其父
节点都没有被覆盖，则将父结点加入到最小点
覆盖集合，标记当前点和其父结点都被覆盖。
但是对于根节点是不可以检查的。
\**==================================**/
struct E//边的数据结构
{
	int v;
	int next;
}edge[20];
//newpos为深度优先时的点的次序，now为已经有多少点被访问，pre为每个点的父结点
int head[10] , newpos[10] , now , pre[10];
bool select[10] , cover[10] , set[10];//selec为判断某个点是否被访问了，cover标记某个点是否被覆盖，set为最小点覆盖集合
int n , m;

void dfs(int x)
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

int mpc()
{
	int res = 0;
	memset(cover , false , sizeof(cover));
	memset(set , false , sizeof(set));

	for(int i = n - 1 ; i >= 1 ; i--)
	{
		int tmp = newpos[i];
		if(!cover[tmp] && !cover[pre[tmp]])//如果当前点和其父结点都没被覆盖，则将父结点加入集合
		{
			set[pre[tmp]] = true;
			cover[tmp] = cover[pre[tmp]] = true;
			res++;
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

		int root = 1;
		memset(select , false , sizeof(select));
		select[root] = true;//标记根节点已被访问
		pre[root] = root;//根节点的父结点为自身
		now = 0;
		dfs(root);

		int res = mpc();
		cout<<res<<endl;
		for(int i = 1 ; i <= n ; i++)
			if(set[i]) cout<<i<<" ";
		cout<<endl;
	}
	return 0;
}
