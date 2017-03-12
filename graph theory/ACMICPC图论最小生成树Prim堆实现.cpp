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
的权值和，这个算法使用最小堆实现在时间复杂度上
为o((N+M)logN)
\**===========================================**/
const int MAX = 0xfffffff;

int dist[12];
int n , m , head[12] , sum;
bool ins[12];
int pre[12];

struct E//用链式前向星存储边
{
	int v , cap;
	int next;
}edge[30];

void addedge(int u , int v , int c)//添加一条边
{
	edge[sum].v = v;
	edge[sum].cap = c;
	edge[sum].next = head[u];
	head[u] = sum++;

	edge[sum].v = u;
	edge[sum].cap = c;
	edge[sum].next = head[v];
	head[v] = sum++;

}

struct priority_queue//最小优先级队列
{
	int point[12];//队列中的每个点
	int position[12];//每个点在队列数组中的位置
	int size;//队列的长度

	void exchange(int x , int y)//交换队列中的两个点
	{
		int tmp = position[point[x]];//先交换位置
		position[point[x]] = position[point[y]];
		position[point[y]] = tmp;

		tmp = point[x];//交换点
		point[x] = point[y];
		point[y] = tmp;
	}

	void init(int n , int s)//初始化最小队列
	{
		size = n;
		for(int i = 1 ; i <= n ; i++)//初始化每个点及其位置
		{
			position[i] = i;
			point[i] = i;
		}
		exchange(position[s] , 1);//将源点s放到队列的最前面
	}

	void min_heapify(int pos)//保持最小堆的性质
	{
		int l = pos * 2;
		int r = 2 * pos + 1;

		int minimum;
		if(l <= size && dist[point[l]] < dist[point[pos]])
			minimum = l;
			else minimum = pos;

		if(r <= size && dist[point[r]] < dist[point[minimum]])
			minimum = r;

		if(minimum != pos)
		{
			exchange(pos , minimum);
		}
	}

	int extract_min()//弹出关键值最小的点
	{
		int min = point[1];
		point[1] = point[size];
		position[point[1]] = 1;
		size--;
		min_heapify(1);//修改后要调整队列使其仍然保持最小堆得性质
		return min;
	}

	void decrease(int poi , int key)//修改一个点poi的关键值
	{
		dist[poi] = key;
		int pos = position[poi];
		while(pos > 1 && dist[point[pos]] < dist[point[pos/2]])
		{
			exchange(pos , pos/2);
			pos /= 2;
		}
	}

	bool empty()//判断队列是否为空
	{
		if(size == 0)
			return true;
			else return false;
	}
}Q;

void prim(int source)//Prim算法
{
	memset(ins , false , sizeof(ins));
	for(int i = 1 ; i <= n ; i++)
		dist[i] = MAX;

	dist[source] = 0;//将第一个点的dist值赋为0
	Q.init(n , source);//初始化最小优先级队列

	while(!Q.empty())
	{
		int u = Q.extract_min();//弹出dist值最小的点
		ins[u] = true;

		int e = head[u];//修改与当前点相连的点的dist值
		while(e != -1)
		{
			int v = edge[e].v;
			if(!ins[v] && dist[v] > edge[e].cap)
			{
				Q.decrease(v , edge[e].cap);
				pre[v] = u;
			}
			e = edge[e].next;
		}
	}
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt", "r", stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		sum = 0;

		for(int i = 1 ;  i <= m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			addedge(u , v , c);
		}

		prim(3);

		int res = 0;
		for(int i = 1 ; i <= n ; i++)
		{
			cout<<dist[i]<<endl;
			res += dist[i];
		}
		cout<<res<<endl;
	}
	return 0;
}
