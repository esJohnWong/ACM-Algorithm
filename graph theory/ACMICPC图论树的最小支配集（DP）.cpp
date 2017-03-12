#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
/**======================================**\
算法分析:
树的最小支配集是从V中取尽量少的点组成一个集
合，使得V中剩余的点都与取出来的点有边相连。
这个算法是基于树形动态规划的。
dp[u][0]表示点u属于支配集，且以点u为根的子树
都被覆盖了的情况下支配集中包含的最少点的个数
dp[u][1]表示u不属于支配集，且以点u为根的子树
都被覆盖了，u被其中不少于一个子节点覆盖情况
下支配集中所包含的最少点的个数。
dp[u][2]表示u不属于支配集，且以u为根的子树都
被覆盖，且没有子节点覆盖u情况下支配集所包含
的最少的点数。
则：对u的所有子节点，E表示取和
dp[u][0] = 1 + E(pre[v] = u)min(dp[v][0] , dp[v][1] , dp[v][2])
dp[u][2] = E(pre[v] = u)dp[v][1]
如果u没有子节点则dp[u][1] = INF
否则dp[u][1] = E(pre[v] = u)min(dp[v][1] , dp[v][2]) + inc
如果dp[u][1]中包含了某个dp[v][0]则inc = 0
否则inc = min(pre[v] = u)(dp[v][0] - dp[v][1])
即强制把某个点（dp[v][0]最小）的dp[v][0]加
到dp[u][1]中以使点u被覆盖。
最后的结果为min(dp[root][0] , dp[root][1])
\**======================================**/
const int MAX = 0xfffffff;//定义无穷大

struct E
{
	int v;
	int next;
}edge[20];

int head[10] , dp[10][3];

void mds(int u , int pre)
{
	dp[u][2] = 0;//初始化
	dp[u][0] = 1;

	bool flag = false;
	int sum = 0 , inc = MAX;

	for(int k = head[u] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(v == pre) continue;
		mds(v , u);

		dp[u][0] += min(dp[v][0] , min(dp[v][1] , dp[v][2]));

		if(dp[v][0] <= dp[v][1])
		{
			sum += dp[v][0];
			flag = true;
		}
		else
		{
			sum += dp[v][1];
			inc = min(inc , dp[v][0] - dp[v][1]);
		}

		if(dp[v][1] != MAX && dp[u][2] != MAX)
			dp[u][2 ] += dp[v][1];
			else dp[u][2] = MAX;
	}

	if(inc == MAX && !flag)
		dp[u][1] = MAX;
		else
		{
			dp[u][1] = sum;
			if(!flag) dp[u][1] += inc;
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
		for(int  i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v , num);
		}

		int root = 1;
		mds(1 , 1);
		cout<<min(dp[root][0] , dp[root][1])<<endl;
	}
	return 0;
}
