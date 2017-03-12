#include<iostream>
#include<cstring>

using namespace std;
/**====================================**\
算法分析：
树的最大独立集是指从V中取尽量多的点，使得
这些点之间没有边相连。对于边<u,v>，u，v不
能同时在独立集中，甚至u，v都不在独立集中。
这个算法基于贪心策略，首先按照深度优先搜索
的顺序排列点，然后按照反序的反向对每个点
进行检查，如果当前点没有被覆盖，则将当前
点加入独立集，并标记当前点和其父结点都被
覆盖。根节点要检查。
\**====================================**/
struct E
{
	int v;
	int next;
}edge[20];

int head[10] , newpos[10] , now , pre[10];
bool select[10] , cover[10] , set[10];
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

int mis()
{
	int res = 0;
	memset(cover , false , sizeof(cover));
	memset(set , false , sizeof(set));

	for(int i = n - 1 ; i >= 0 ; i--)
	{
		int tmp = newpos[i];
		if(!cover[tmp])//如果当前点没有被覆盖则加入集合，并标记当前点和其父结点
		{
			set[tmp] = true;
			cover[tmp] = cover[pre[tmp]] = true;
			res++;
		}
	}
	return res;
}

void addedge(int u , int v , int &num)
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
			int u ,v;
			cin>>u>>v;
			addedge(u , v , num);
		}

		int root = 1;
		memset(select , false , sizeof(select));
		select[root] = true;
		now = 0;
		pre[root] = root;
		dfs(root);

		int res = mis();
		cout<<res<<endl;
		for(int i = 1 ; i <= n ; i++)
			if(set[i]) cout<<i<<" ";
		cout<<endl;
	}
	return 0;
}
