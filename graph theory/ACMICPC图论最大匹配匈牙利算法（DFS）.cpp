/**===============================================**\
算法分析：
匈牙利算法就是在二分图中不断的找增广路径。如果一条路
径的边交替出现在匹配M中和不出现在M中，则称这条路径为
交错路径。如果路径的起点和终点没有匹配叫增广路径。可
以看到，如果出现增广路径只要把这条路径上不属于原匹配
的边加入匹配，把原匹配的边删除形成的新匹配的边必定增
加一条。
\**===============================================**/

#include<iostream>
#include<cstring>

using namespace std;

bool biGraph[6][6];//二分图
bool vist[6];//标记左边的点是否被访问
int matchRight[6] , matchLeft[6] ;//右边的点和左边的点分别匹配到的对边的点

int nright , nleft , m;//左右匹配的点数，总边数

int findPath(int u)//找一条增广路径
{
	for(int i = 1 ; i <= nright ; i++)
	{
		if(biGraph[u][i] && !vist[i])
		{
			vist[i] = true;
			if(matchRight[i] == -1 || findPath(matchRight[i]))//找到右边没有匹配的点或者已经匹配但是找到一条增广路径
			{
				matchLeft[u] = i;
				matchRight[i] = u;
				return 1;
			}
		}
	}
	return 0;
}

int maxMatch()
{
	int res = 0;
	memset(matchLeft , -1 , sizeof(matchLeft));
	memset(matchRight , -1 , sizeof(matchRight));

	for(int i = 1 ; i <= nleft ; i++)
	{
		if(matchLeft[i] == -1)//从左边没有匹配的点开始找
		{
			memset(vist , false , sizeof(vist));
			res += findPath(i);
		}
	}
	return res;
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt" , "r" , stdin);
	while(cin>>nright>>nleft>>m)
	{
		for(int i = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			biGraph[u][v] = true;
		}

		int res = maxMatch();
		cout<<res<<endl;
	}
	return 0;
}
