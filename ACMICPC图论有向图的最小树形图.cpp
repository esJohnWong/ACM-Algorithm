#include<iostream>
#include<cstring>

using namespace std;
/**===================================**\
算法分析：
有向图的最小树形图G要满足一下两条性质
1 G中没有环
2 G中有且仅有一个点v0不是任何边的终点，
而其他的点恰好是唯一一条边的终点
这个算法为朱刘算法 刘振宏 朱永津 1965年
发表
1' 对图中除了根节点外，取所有以点v为终点
的边中最小的一条加入到边集E0，如果有某一
点没有入边则原图不存在最小树形图，算法结
束
2' 检查E0中是否有收缩的点以及有向环，如果
没有则为原图的最小树形图
1'' 如果E0中有有向环，设v在环中，v'不在环
中则边把整个环缩成一个点u，w为环中为以v为
终点的边的权值，则新的w<v',u>=w<v',v>-w
2'' 如果最小树形图已经求出，则把收缩的点
展开去掉与最小树形图中有相同终点的边，得
到的就是最终的最小树形图
在整个计算的过程中所有的环的权值和加上最
后一个最小树形图的权值就是要求的最终最小
树形图的权值
\**===================================**/
const int MAX = 0xfffffff;

int map[8][8];
bool flag[8];//标志一个点是否被收缩掉
bool visit[8];
int pre[8];
int sum;
int n , m;

void zhuliu(int source)
{
	sum = 0;
	memset(flag , false , sizeof(flag));
	pre[source] = source;

	while(true)
	{//找以每个点为终点的最小边集E0
		for(int i = 1 ; i <= n ; i++)
		{
			if(i == source || flag[i]) continue;

			pre[i] = i;
			for(int j = 1 ; j <= n ; j++)
			{
				if(!flag[j] && map[j][i] < map[pre[i]][i])
					pre[i] = j;
			}

			if(pre[i] == i)//如果有一个点没有入边就退出计算
			{
				sum = -1;
				return;
			}
		}

		int i;
		for(i = 1 ; i <= n ; i++)//检查E0中是否有环
		{
			if(i == source || flag[i]) continue;
			memset(visit , false , sizeof(visit));

			visit[source] = true;
			int j = i;

			do
			{
				visit[j] = true;
				j = pre[j];
			}while(!visit[j]);

			if(j == source) continue;//找到根节点说明没有环

			i = j;//将环缩成点j

			do//计算最小树形图的值
			{
				sum += map[pre[j]][j];
				j = pre[j];
			}while(j != i);

			j = i;//把以环中的点为终点的边的权值修改
			do
			{
				for(int k = 1 ; k <= n ; k++)
				{// 点k没被收缩且边<k,j>存在，且k不在环中
					if(!flag[k] && map[k][j] < MAX && k != pre[j])
						map[k][j] -= map[pre[j]][j];
				}

				j = pre[j];
			}while(j != i);

			for(j = 1 ; j <= n ; j++)//将环收缩到i点把所有与环相连的边变成与i相连
			{
				if(j == i) continue ;

				int k = pre[i];
				while(k != i)
				{
					if(map[k][j] < map[i][j])//防止重边
						map[i][j] = map[k][j];

					if(map[j][k] < map[j][i])
						map[j][i] = map[j][k];

					k = pre[k];
				}
			}

			for(j = pre[i] ; j != i ; j = pre[j])//被收缩的点标记
				flag[j] = true;

			break;//收缩结束形成新的图 从新的图开始找
		}

		if(i == n + 1)//所有边都不存在环则累加sum
		{
			for(int j = 1 ; j <= n ; j++)
			{
				if(j == source) continue ;
				if(!flag[j])
					sum += map[pre[j]][j];
			}
			break;//跳出while循环
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
			{
				map[i][j] = MAX;
			}
		}

		for(int i = 0 ; i < m ; i++)
		{
			int  u , v , w;
			cin>>u>>v>>w;
			if(map[u][v] > w)
			{
				if(map[u][v] > w)//检查重边
					map[u][v] = w;
			}
		}

		zhuliu(1);

		printf("%d\n" , sum);
	}
	return 0;
}
