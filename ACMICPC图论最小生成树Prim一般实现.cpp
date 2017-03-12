#include<iostream>
#include<cstring>

using namespace std;
/**===========================================**\
算法分析：
算法将图中所有的点分为两部分属于最小生成树当前已
经找到的点的集合，不在当前找到的最小生成树的点的
集合如果找到一个点v在最小生成树当前点集合S中就把
这个点标记为在S中，算法维护了一个dist数组，如果点
v在S中则dist[v]表示v与v的前驱u的边的权值map[u][v]
且dist[v]不可能再更改，如果v不在S中则dist[v]表示
所有在S中的点u与v相连的边的最小权值，算法每次从
不在S中的点里寻找一个点其dist值最小，找到后将这
个点放入S并修改与v相连但不在S中的点t的dist的值
然后又从不在S中的点中找一个dist最小的点，直到所
有的点全部在S中结束程序，dist的和就为最小生成树
的权值和，时间复杂度o(n^2)，空间复杂度o(n^2)
\**===========================================**/
const int MAX = 0xfffffff;

int map[10][10];
int n , m;
int dist[10] , pre[10];
bool ins[10];

void prim(int source)
{
	for(int i = 1 ; i <= n ; i++)
	{
		ins[i] = false;
		dist[i] = map[source][i];
		pre[i] = source;
	}

	dist[source] = 0;
	ins[source] = true;

	for(int i = 1 ; i < n ; i++)
	{
		int min = MAX;
		int k = 0 ;
		for(int j = 1 ; j <= n ; j++)
		{
			if(!ins[j] && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}

		if(k == 0) return ;

		ins[k] = true;
		for(int j = 1 ; j <= n ; j++)
		{
			if(!ins[j] && map[k][j] != MAX && dist[j] > map[k][j])
			{
				dist[j] = map[k][j];
				pre[j] = k;
			}
		}
	}
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt", "r", stdin);
	while(cin>>n>>m)
	{
		for(int i = 1 ; i <= n ; i++)
		{
			for(int j = 1 ; j <= n ; j++)
				map[i][j] = MAX;
		}

		for(int i = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			map[u][v]= map[v][u] = c;
		}

		prim(3);

		int ans = 0;
		for(int i = 1 ; i <= n ; i++)
		{
			cout<<dist[i]<<endl;
			ans +=  dist[i];
		}

		cout<<ans<<endl;
	}
	return 0;
}
