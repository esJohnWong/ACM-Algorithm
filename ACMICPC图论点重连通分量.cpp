#include<iostream>
#include<algorithm>
#include<cstring>
#include<stack>

using namespace std;
/**=================================**\
算法分析：
图的重连通分量就是在图中存在一个最大的
子图使得这子图不是任何一个子图的重连通
分量，一个图是重连通图当且仅当这个图中
不存在一点，把这点删掉后图变为多个连通
图，这一点称为关节点。重连通分量讲的是
无向图。两个重连通分量不可能共享一个以
上的节点。
先对原图进行深度优先搜索，形成一棵深度
优先树。对根节点如果为一个关节点（割点）
则根节点在深度树中有至少两个孩子，对不
是根节点的其他点如果有dfn[u]<=low[v]则
这个点也为割点，每一个割点就是一个重连
通的根，同一点可能同时属于多个重连通图。
dfn为depth first number即为每个点的深度
优先访问到时的时间，low[u] = min(dfn[u] , low[v])
\**=================================**/
struct E//定义边的数据结构
{
	int v , next;
}edge[28];
//bcc为重连通分量的结果，dfn每个点访问到的时间，low为如上述
int head[11] , bcc[11][11] , dfn[11] , low[11];
int n , m;
stack<int> stk;

void addEdge(int u , int v , int &num)//添加边
{
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;

	edge[num].v = u;
	edge[num].next = head[v];
	head[v] = num++;
}

void tarDfs(int u , int &tim , int &bccNum , int pre)//dfs搜索函数
{
	stk.push(u);
	dfn[u] = low[u] = ++tim;//初始化dfn，low为访问的时间
	for(int k = head[u] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(v == pre) continue;//u的子节点不可以和其直接父亲相同
		if(dfn[v] == 0)//v没有访问
		{
			tarDfs(v , tim , bccNum , u);//继续访问v
			low[u] = min(low[u] , low[v]);
			if(low[v] >= dfn[u])//u是一个割点则u和v以及v以后压入的点都在这个重连通中
			{
				bcc[bccNum][0] = u;//依次弹出在同一个重连通中的点
				int cnt = 1;
				while(stk.top() != v)
				{
					bcc[bccNum][cnt++] = stk.top();
					stk.pop();
				}
				bcc[bccNum][cnt++] = stk.top();
				stk.pop();
				bcc[bccNum][cnt++] = -1;//方便后面输出
				bccNum++;
			}
		}
		else low[u] = min(low[u] ,dfn[v]);//v被访问过，即出现了回路
	}
}

int tarjan()//求重连通的主函数
{
	int bccNum = 0 , tim = 0;
	memset(low , 0 , sizeof(low));
	memset(dfn , 0 , sizeof(dfn));
	while(!stk.empty())//将栈清空
	{
		stk.pop();
	}

	for(int i = 1 ; i <= n ; i++)
	{
		if(dfn[i] == 0) tarDfs(i , tim , bccNum , 0);
	}

	return bccNum;
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
			addEdge(u , v , num);
		}

		int bccNum = tarjan();
		cout<<tarjan()<<endl;
		for(int i = 0 ; i < bccNum ; i++)
		{
			int j = 0;
			while(bcc[i][j] != -1)
			{
				cout<<bcc[i][j++]<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}
