#include<iostream>
#include<cstring>
#include<stack>
#include<algorithm>

using namespace std;
/**=====================================**\
算法分析：
有向图的强连通分支Tarjan算法的思想是对与一
个强连通分支，它是以其中一个点为根的树，如
果我们找到这棵树的根，及其最下层的叶子就可
以确定这个强连通分量了。
对图进行深度优先搜索，每个点设置三种状态，
vist[u]=0时代表这个点还没有被搜到，为1时代
表这个点已经搜到，为2时代表这个点已经从图中
删除了。从图中找一个没有被访问的点u开始，将
其被访问的时间放在tim中，对于u的相邻的点v如果
没有访问就访问，如果为1就比较v和u的lowt，
(lowt初始化为tim)lowt[u]取其中最小的，即要求
这个点必须与其父结点间接或直接相连否则lowt不
会变小，（根除外）由于是深度优先而且强连通分支
之间的任意两个点可达，那么最后强连通分支的根节
点有lowt=tim.将访问到的每一个点都放进以个堆栈中，
堆栈中比u后放入的点都是以u为根的强连通分支中的点，
然后依次次弹出就可以了。
\**=====================================**/
struct E
{
	int v , next;
}edge[15];

int head[10] , tim[10] , lowt[10];
int vist[10];
int n , m , scc[10];//scc为最后强连通分支的结果
stack<int> s;

void tardfs(int u , int t , int &sccnum)
{
	vist[u] = 1;//将当前点设置为访问，并压入堆栈
	s.push(u);
	tim[u] = lowt[u] = t;//初始化访问时间及lowt
	for(int k = head[u] ; k != -1 ; k = edge[k].next)//扫面u与相连的点
	{
		int v = edge[k].v;
		if(vist[v] == 0) tardfs(v , ++t , sccnum);//如果v没有访问就访问
		if(vist[v] == 1) lowt[u] = min(lowt[u] , lowt[v]);//如果v访问了且在同一个强连通分支下就更新lowt
	}

	if(lowt[u] == tim[u])//当与u相连的所有点都被访问了后lowt=tim 则u为根
	{
		sccnum++;//强连通分支计数器加1
		while(s.top() != u)//将u以后压入的点全部弹栈
		{
			scc[s.top()] = sccnum;
			vist[s.top()] = 2;//点被从图中删除
			s.pop();
		}
		scc[s.top()] = sccnum;//将u弹栈
		vist[s.top()] = 2;
		s.pop();
	}
}

int tarjan()
{
	int sccnum = 0 , t = 0;
	memset(vist , 0 , sizeof(vist));
	memset(lowt , 0 , sizeof(vist));
	for(int i = 1 ; i <= n ; i++)
	{
		if(vist[i] == 0) tardfs(i , t , sccnum);//如果点i还没被访问就从i访问
	}
	return sccnum;
}

void addedge(int u , int v ,int &num)//压入一条有向边
{
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v , num);
		}

		int num = tarjan();
		cout<<num<<endl;
		for(int i = 1 ; i <= n ; i++)
			cout<<i<<" "<<scc[i]<<endl;
	}
	return 0;
}
