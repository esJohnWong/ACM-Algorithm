#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
/**=========================================**\
算法分析：
无向图的全局最小割即为将图G(V)中的点划分为两个
部分S,T使得任意一条从S到T的边的权值之和最小。
stoer_wanger算法和prim算法相似.
1初始化最小割ans为无穷大，T中为图的全部点。
2从图中任选一个点s放到集合S中定义dist[p]为S中
的点到T中一点p的权值总和。
3根据所选的s更新图中的dist[p]。
4从dist[p]中选出值最大的点作为新的s，若S！=G(v)
则继续3.
5最后进入S的两个点记为s，t。用dist[t]更新ans。
6新建点c边权w[c] = w[s,v]+w[t,v]。删除所有与t
和s相连的边。
7若|V|！=1则继续步骤2.
这个算法和prim算法相似。
如果S包含了|V|-1个点则最小割就是这个割，因为每
次都把dist最大的一个点放到S中最后一个点一定是
dist最小的点，而这时有正好构成了一个割。当最后
只剩下两个点的时候这条边绝对是最小的割，别无他
选。
\**=========================================**/
const int MAX = 0xfffffff;
//map图的信息，node包存每个点的编号，dist如上述
int map[10][10] , node[10] , dist[10];
int n , m;
bool vist[10];//vist标志一个点访问没有

int stoerWanger()//求最小割的算法
{//pre为上一个dist最大的点，maxj为当前dist最大的点
	int ans = MAX , N = n , pre , maxj;
	for(int i = 1 ; i <= N ; i++)
		node[i] = i;//把点的编号放进node中

	while(N > 1)
	{
		int m = -MAX;//保存dist的最大值
		for(int i = 2 ; i <= N ; i++)//第一次选node[1]为dist最大的点
		{
			dist[node[i]] = map[node[1]][node[i]];
			vist[node[i]] = false;
			if(dist[node[i]] > m)//找下一个dist最大的点
			{
				m = dist[node[i]];
				maxj = i;
			}
		}

		pre = 1;
		vist[node[1]] = true;

		for(int j = 2 ; j <= N ; j++)
		{
			vist[node[maxj]] = true;//把当前dist最大的点放入S中

			if(j != N)//不是最后的两个点
			{
				pre = maxj;
				m = -MAX;
				for(int i = 1 ; i <= N ; i++)//更新dist
				{
					if(!vist[node[i]])
					{
						dist[node[i]] += map[node[pre]][node[i]];
						if(dist[node[i]] > m)
						{
							m = dist[node[i]];
							maxj = i;
						}
					}
				}
			}
			else
			{
				ans = min(ans , m);//ans和最后的点的dist比较
				for(int i = 1 ; i <= N ; i++)//将c点设为pre点
				{
					map[node[pre]][node[i]] += map[node[maxj]][node[i]];
					map[node[i]][node[pre]] += map[node[maxj]][node[i]];
				}
				node[maxj] = node[N--];//把最后一个点放到maxj的位置，maxj被覆盖掉
			}
		}
	}
	return ans;
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		for(int i = 1 ; i <= n ; i++)
		{
			for(int j = 1 ; j <= n ; j++)
			{
				map[i][j] = 0;//赋值为0方便后面的计算，
				//0可以表示[i,j]权值为0，或是不存在边<i,j>
			}
		}

		for(int i = 1 ; i <= m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			map[u][v] = map[v][u] = c;
		}

		int ans = stoerWanger();
		cout<<ans<<endl;
	}
	return 0;
}
