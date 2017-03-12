#include<iostream>
#include<cstring>
#include<queue>

using namespace std;
/**============================**\
算法分析：
从源点到汇点的最短距离为第1短距离
还有第2短，第3短距离…求第k短距离
我们用了A*算法的思想，即
估价函数 = 当前值 + 当前位置到终点的距离
f(p) = g(p) + h(p)，每次扩展估价函数
值最小的一个。
g(p)为从源点到p点所走过的实际距离
h(p)为p点到终点的距离。h(p)通过将
图反向以终点为源点，源点为终点，通
过SPFA算出最短距离。
用一个优先级队列先将源点压入队中。
每次弹出一个f值最小的点，当终点的
出队次数达到k时这时的g值即为所求。
否则扫描与当前点相邻的点。
\**============================**/
const int MAX = 0xfffffff;

struct node
{
	int v;
	int g , f ;
	bool operator<(const node & a) const
	{
		if(a.f == f) return a.g < g;
		return a.f < f;
	}
};

struct E
{
	int v , c , next;
}edge[12] , reedge[12];//reedge为图的反向边

int head[7] , rehead[7] , h[7];//h为边反向时算出的距离
int start , end , n , m , K;

bool SPFA()//spfa算法
{
	queue<int> Q;
	bool inq[6];
	int outq[6];
	for(int i = 1 ; i <= n ; i++)
	{
		inq[i] = false;
		outq[i] = 0;
		h[i] = MAX;
	}
	inq[end] = true;
	h[end] = 0;
	Q.push(end);

	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		inq[u] = false;
		outq[u]++;

		if(outq[u] > n) return false;

		for(int k = rehead[u] ; k != -1 ; k = reedge[k].next)
		{
			int v = reedge[k].v;
			if(h[v] > h[u] + reedge[k].c)
			{
				h[v] = h[u] + reedge[k].c;
				if(!inq[v])
				{
					inq[v] = true;
					Q.push(v);
				}
			}
		}
	}
	return true;
}

int Astar()//A*算法
{
	priority_queue<node> Q;
	node s , t;
	int cnt = 0;//计算终点出队的次数

	if(start == end) K++;//去掉源点到源点为0的这条距离
	if(h[start] == MAX) return -1;

	s.v = start;//首先将源点压入队列
	s.g = 0;//当前已走的距离为0
	s.f = h[start];//加上到终点的距离为h[start]
	Q.push(s);

	while(!Q.empty())
	{
		s = Q.top();//弹出f值最小的点
		Q.pop();

		if(s.v == end) cnt++;
		if(cnt == K) return s.g;//已得到第k短路
		//将与s.v相邻的点也压入队列
		for(int k = head[s.v] ; k != -1 ; k = edge[k].next)
		{
			t.v = edge[k].v;
			t.g = s.g + edge[k].c;//当前已走的距离为前一个点已走的距离加上前一点到当前点的距离
			t.f = t.g + h[t.v];//路径估价函数为已走的距离加上当前点到终点的距离
			Q.push(t);//将这个点压入队列
		}
	}
	return -1;
}

void addedge(int u , int v , int c , int &num)
{//压入正向边
	edge[num].c = c;
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num;
//压入反向边
	reedge[num].c = c;
	reedge[num].v = u;
	reedge[num].next = rehead[v];
	rehead[v] = num;
	num++;
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		memset(rehead , -1 , sizeof(rehead));

		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			addedge(u , v , c , num);
		}

		start = 1 , K = 1 , end = 5;

		SPFA();
		int ans = Astar();
		cout<<ans<<endl;
	}
	return 0;
}
