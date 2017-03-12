#include<iostream>
#include<cstring>

using namespace std;
/**======================================**\
算法分析：
floyd求最小环其思想的核心是，在求每对点间的
距离时如果从u到v的最短路径在一个环中，那么在
松弛这个环中与最大点相关的边之前，即在u到v的
路径中加入点z之前可以发现这个环。
例如路径1->2->5->3->8->1那么在8还未加入之前，
则可检查dist[1,3] + w[3,8] + w[8,1]是否为无穷
大，如果不为无穷大则这是一个环。由于采用了
floyd算法是把点从小到大加入的所以在某一回路
中的最大点加入这个路径之前可以发现这个回路。
\**======================================**/
const int MAX = 0xfffffff;
//map为图，dist为每对点间的距离
int map[6][6] , dist[6][6];
int n , m;

int floyd()
{
	int mincircle = MAX;//最小环的权值

	for(int i = 1 ; i <= n ; i++)//初始化
	{
		for(int j = 1 ; j <= n ; j++)
			dist[i][j] = map[i][j];
	}

	for(int k = 1 ; k <= n ; k++)//k次循环，每次向路径中加入一个点k
	{
		for(int i = 1 ; i <= n ; i++)
		{
			for(int j = 1 ; j <= n ; j++)
			{
				if(i == j) continue;//避免自环
				if(map[j][k] != MAX && map[k][i] != MAX && dist[i][j] != MAX)//发现一个环，且加入的k点与i，j直接相连
				{
					if(dist[i][j] + map[k][i] + map[j][k] < mincircle)
					{
						mincircle = dist[i][j] + map[k][i] + map[j][k] ;//更新最小环的值
						cout<<i<<" "<<j<<" "<<k<<" "<<mincircle<<endl;
					}

				}
			}
		}

		for(int i = 1 ; i <= n ; i++)//算每对点间的距离
		{
			for(int j = 1 ; j <= n ; j++)
			{
				if(dist[i][k] != MAX && dist[k][j] != MAX)
				{
					if(dist[i][j] > dist[i][k] + dist[k][j])
						dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	return mincircle;
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
				if(i == j)
					map[i][j] = 0;
					else map[i][j] = MAX;
			}
		}

		for(int i = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			map[u][v] = c;
		}

		int mincircle = floyd();

		cout<<mincircle<<endl;
	}
	return 0;
}
