#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
/**=======================================**\
算法分析：
树的最小点覆盖是指从V中取尽量少的点组成一个
集合，使得E中所有的边都与取出来的点相连。
算法基于树形动态规划的思想。E表示取和。
dp[u][0]表示点u属于点覆盖，且以u为根的子树所
连接的边都被覆盖的情况下点覆盖集中所包含的最
少点个数。
dp[u][1]表示点u不属于点覆盖，且以点u为根的子
树中所连接的边都被覆盖的情况下点覆盖集中所包
含的最少点个数。
则：
dp[u][0] = 1 + E(pre[v] = u)min(dp[v][1] , dp[v][0])
dp[u][1] = E(pre[v] = u)dp[v][0]
\**=======================================**/
struct E
{
	int v;
	int next;
}edge[20];

int head[10] , dp[10][2];

void mpc(int u , int pre)
{
	dp[u][0] = 1;//每个点都要初始化，当是叶子节点时也成立
	dp[u][1] = 0;

	for(int k = head[u] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(v == pre) continue;
		mpc(v , u);
		dp[u][0] += min(dp[v][1] , dp[v][0]);
		dp[u][1] += dp[v][0];
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
		mpc(root , root);
		cout<<min(dp[root][0] , dp[root][1])<<endl;
	}
	return 0;
}
