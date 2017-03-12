#include<iostream>
#include<cstring>
#include<stack>

using namespace std;
/**================================**\
算法分析：
边的重连通分量是和点的重连通分量算法
相似的，
low[u] = min(low[u] , dfn[u] , dfn[v](回路))
但当low[v]>dfn[u]时v和v以后进入堆栈的
点都在边重连通分量中，u不在，而点重连
通u也在。再就是和根结点在同一个重连通
里的点要单独处理。
\**================================**/
struct E
{
	int v , next;
}edge[25];

int head[12] , bcc[12][12] , dfn[12] , low[12];
int n , m;
stack<int> stk;

void tarDfs(int u , int &bccNum , int &t , int pre)
{
	stk.push(u);
	dfn[u] = low[u] = ++t;
	for(int k = head[u] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(v == pre) continue;
		if(dfn[v] == 0)
		{
			tarDfs(v , bccNum , t , u);
			low[u] = min(low[u] , low[v]);
			if(low[v] > dfn[u])
			{
				int cnt = 0;
				while(stk.top() != v)
				{
					bcc[bccNum][cnt++] = stk.top();
					stk.pop();
				}
				bcc[bccNum][cnt++] = stk.top();
				stk.pop();
				bcc[bccNum][cnt++] = -1;
				bccNum++;
			}
		}
		else low[u] = min(low[u] , dfn[v]);
 	}
}

int tarjan()
{
	int bccNum = 0 , tim = 0;
	memset(low , 0 , sizeof(low));
	memset(dfn , 0 , sizeof(low));

	for(int i = 1 ; i <= n ; i++)
	{
		if(dfn[i] == 0)
		{
			tarDfs(i , bccNum , tim , 0);
			int cnt = 0;
			while(!stk.empty())//将与根节点相连的边重连通分量弹出
			{
				bcc[bccNum][cnt++] = stk.top();
				stk.pop();
			}
			bcc[bccNum][cnt++] = -1;
			bccNum++;
		}
	}
	return bccNum;
}

void addEdge(int u , int v , int &num)
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
	//freopen("D:\\cruanjian\\桌面\\in.txt" , "r" , stdin);
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
		cout<<bccNum<<endl;
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
