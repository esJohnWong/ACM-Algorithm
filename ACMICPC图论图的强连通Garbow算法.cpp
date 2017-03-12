#include<iostream>
#include<cstring>
#include<stack>

using namespace std;
/**====================================**\
算法分析：
有向图的强连通分支Garbow算法是对Tarjan算法
的改进，Tarjan算法每次都要维护两个数组，tim
和lowt来找到一个强连通分量的根节点。而Garbow
则是利用两个堆栈来找到每个强连通分量的根。
stk1把每次找到的节点压入其中如果发现根节点
就把根和比根后进的点都弹出，stk2则是找根
节点的堆栈，当发现一个环时就把出根节点以外
属于这个换的其他点弹出，如果当一个点的所有
邻接点都被访问后stk2的栈顶为这个点则这个点
就是这个连通分量的根，就把相应的联通分量
弹出。
\**====================================**/
const int MAX = 0xfffffff;

struct E//定义边的数据结构
{
	int v , next;
}edge[15];
//tim为访问到每个点的时间，scc为每个点属于相应的哪个连通分量
int head[10] , tim[10] , scc[10];
stack<int> stk1 , stk2;//stk1为求连通分量的堆栈，stk2为求联通分量的根
int n , m;

void addEdge(int u , int v , int &num)//压入一条边
{
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;
}

void garDfs(int u , int t , int &sccNum)//Garbow搜索函数
{
	stk1.push(u);//先将u压入两个堆栈
	stk2.push(u);
	tim[u] = t;//设置u的访问时间

	for(int k = head[u] ; k != -1 ; k = edge[k].next)//扫面u的邻接点
	{
		int v = edge[k].v;
		if(tim[v] == 0)//如果u的邻接点v没有访问，就访问v
		{
			garDfs(v , ++t , sccNum);
		}
		else if(scc[v] == 0)//如果v访问了且没确定是哪个连通分量，
		{				//这时说明出现了环
			while(tim[stk2.top()] > tim[v])//将环上出v以外的点都删除
			{
				stk2.pop();
			}
		}
	}

	if(stk2.top() == u)//u的所有邻接点都扫描完stk2的栈顶元素等于u说明u是当前连通分量的根
	{
		stk2.pop();//将stk2中的u弹出u所属的强连通已经求出
		sccNum++;//连通分量加一
		while(stk1.top() != u)//u及u以后压入的点都属于同一连通分量弹出stk1
		{
			scc[stk1.top()] = sccNum;
			stk1.pop();
		}
		scc[stk1.top()] = sccNum;
		stk1.pop();
	}
}

int garbow()//garbow主函数
{
	int sccNum = 0 , t = 1;
	memset(tim , 0 , sizeof(tim));
	memset(scc , 0 , sizeof(scc));

	for(int i = 1 ; i <= n ; i++)//从一个没有扫面到的点进行扫描
	{
		if(tim[i] == 0) garDfs(i , t , sccNum);
	}
	return sccNum;
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

		int sccNum = garbow();
		cout<<sccNum<<endl;
		for(int i = 1 ; i <= n ; i++)
			cout<<i<<" "<<scc[i]<<endl;
	}
	return 0;
}
