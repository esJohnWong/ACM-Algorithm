#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
/**======================================**\
算法分析：
树的最大独立集是指从V中取尽量多的点组成一个
集合，使得这些点之间没有边相连。
算法基于树形动态规划的策略。E表示取和。
dp[u][0]表示点u属于独立集时最大独立集中点的
个数
dp[u][1]表示点u不属于独立集时最大独立集中点
的个数
则：
dp[u][0] = 1 + E(pre[v] = u)dp[v][1]
dp[u][1] = E(pre[v] = u)max(dp[v][1] , dp[v][0])
最终的结果取max(dp[root][0] , dp[root][1])
\**======================================**/
struct E
{
	int v;
	int next;
}edge[20];

int head[10] , dp[10][2];

void mds(int u , int pre)
{
	dp[u][0] = 1;//初始化，叶子节点时也成立
	dp[u][1] = 0;

	for(int k = head[u] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(v == pre) continue;
		mds(v , u);
		dp[u][0] += dp[v][1];
		dp[u][1] += max(dp[v][1] , dp[v][0]);
	}
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
	int n , m;

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
		mds(root , root);
		cout<<max(dp[root][0] , dp[root][1])<<endl;
	}
	return 0;
}
