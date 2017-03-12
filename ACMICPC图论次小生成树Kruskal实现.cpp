#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
/**=================================================**\
算法分析：
要求最小生成树之后的次小生成树，当我们找到一棵次小生
成树后，如果在点x,y之间再加一条边[x,y]那么必定形成了
一个环,如果把x,y之间的边除了新加的[x,y]以外最大的一条
边删除则形成了一棵次小生成树。把所有的没有在最小生成树
边都依次替换，算出相应的次小生成树权值，最后取所有权值
最小的就是要求的次小生成树,需要注意的是求出的次小生成
树的权值可能和最小生成树的相等，说明最小生成树不唯一
\**=================================================**/
const int MAX = 0xfffffff;

struct E//定义边的数据结构
{
	int u , v;
	int w;
	bool select;//标记这条边是否在最小生成树中
}edge[30];

struct S//定义一个集合的数据结构集合中的点是当前在最小生成树中的点
{
	int v;
	int next;
}set[12];

int pre[12] , rank[12];
int head[12] , tail[12];
int length[12][12];//标记每两个点间的最大边的权值
int n , m;

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
	if(rank[x] < rank[y])
		pre[x] = y;
		else
		{
			pre[y] = x;
			if(rank[x] == rank[y])
				rank[x]++;
		}
}

void Union(int x , int y)
{
	link(findset(x) , findset(y));
}

void init()//初始化
{
	memset(head , -1 , sizeof(head));
	for(int i = 0 ; i < n ; i++)//先把每个点都放到集合中
	{
		set[i].v = i + 1;
		set[i].next = head[i + 1];
		head[i + 1] = i;//集合在set中的存储边界
		tail[i + 1] = i;
	}

	for(int i = 0 ; i < m ; i++)
	{
		int u , v , w ;
		cin>>u>>v>>w;
		edge[i].u = u;
		edge[i].v = v;
		edge[i].w = w;
		edge[i].select = false;
	}
}

bool cmp(E e1 , E e2)
{
	return e1.w < e2.w;
}

void kruskal()
{
	for(int  i = 1 ; i <= n ; i++)
		makeset(i);

	int k = 0;
	sort(edge , edge + m , cmp);

	for(int i = 0 ; i < m ; i++)
	{
		if(k == n - 1) break;
		int x = findset(edge[i].u);
		int y = findset(edge[i].v);

		if(x != y)//一个集合是以x为父结点，另一个是以y为父结点
		{//当前加入的边一定是[x,y]的最大边
			for(int e1 = head[x] ; e1 != -1 ; e1 = set[e1].next)
			{
				for(int e2 = head[y] ; e2 != -1 ; e2 = set[e2].next)
				{
					int u = set[e1].v , v = set[e2].v;
					length[u][v] = length[v][u] = edge[i].w;
				}
			}

			Union(x , y);
			set[tail[y]].next = head[x];//合并两个点集
			tail[y] = tail[x];
			head[x] = head[y];//因为不知道合并后x、y谁是根所以就以y为准最后head[x],head[y]指向同一个地方
			k++;//记录所选边的条数
			edge[i].select = true;
		}
	}
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt", "r", stdin);
	while(cin>>n>>m)
	{
		init();
		int mst = 0 , secmst = MAX;
		kruskal();

		for(int i = 0 ; i < m ; i++)//算出最小生成树的权值
		{
			if(edge[i].select) mst += edge[i].w;
		}

		for(int i = 0 ; i < m ; i++)
		{
			if(!edge[i].select)//如果当前边没有被选择就加入最小生成树并删掉其最大边
			{
				int u = edge[i].u , v = edge[i].v;
				int tmst = mst + edge[i].w - length[u][v];
				secmst = min(secmst , tmst);
			}
		}

		cout<<secmst<<endl;
	}
	return 0;
}
