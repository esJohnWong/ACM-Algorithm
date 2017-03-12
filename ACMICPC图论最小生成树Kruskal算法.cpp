#include<iostream>
#include<algorithm>

using namespace std;
/**==============================================**\
算法分析：
最小生成树kruskal算法，利用了并查集，这样就不需要建
图简化了操作，算法维护一个集合A，A中装已经被找到的
最小生成树的边。算法开始时将图中的每个点建成一个集
合，然后将所有的边按照权值的大小从小到大排序，然后
按照排序后的结果对每条边的量个点进行检查，如果这两
个点不在一个集合内则把这条边加入A中直到找到n-1条边
就结束，因为含有n个点的最小生成树最多只有n-1条边。
因为如果一条边的两个点在一个集合内，把这条边加到A中
那么最小生成树就有了回路，而要求树是不具有回路的。
\**==============================================**/

int rank[16] , pre[12];//并查集的每个点的父结点以及度数
int n , m , se;//se为A中边的条数

struct E//定义边的数据结构
{
	int u , v;
	int w;
}edge[16];

struct set//定义集合A
{
	int u , v;
	int w;
}A[12];

bool cmp(E e1 , E e2)//排序比较函数
{
	return e1.w < e2.w;
}

void makeset(int x)
{
	pre[x] = x;
	rank[x] = 0;
}

int findset(int x)
{
	if(pre[x] != x)
		pre[x] = findset(pre[x]);
	return pre[x];
}

void link(int x , int y)
{
	if(rank[x] > rank[y])
		pre[y] = x;
		else
		{
			pre[x] = y;
			if(rank[x] == rank[y])
				rank[y]++;
		}
}

void Union(int x , int y)
{
	link(findset(x) , findset(y));
}

void kruskal()
{
	for(int i = 1 ; i <= n ; i++)//先将每个点变成一个集合
		makeset(i);

	sort(edge , edge + m , cmp);//对边排序

	se = 0;
	for(int i = 0 ; i < m ; i++)//每次循环判断当前边是否合法
	{
		if(se == n - 1)	break;//如果找到n-1条边则结束计算

		int u = edge[i].u;
		int v = edge[i].v;
		if(findset(u) != findset(v))//一条边的两个点不能已经在同一个集合
		{
			Union(u , v);
			A[se].u = u;
			A[se].v = v;
			A[se].w = edge[i].w;
			se++;
		}
	}
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt", "r", stdin);
	while(cin>>n>>m)
	{
		for(int i = 0 ; i < m ; i++)
		{
			int u , v , w;
			cin>>u>>v>>w;
			edge[i].u = u;
			edge[i].v = v;
			edge[i].w = w;
		}

		kruskal();

		int res = 0;
		for(int i = 0 ; i < se ; i++)
		{
			res += A[i].w;
		}
		cout<<res<<endl;
	}
	return 0;
}
