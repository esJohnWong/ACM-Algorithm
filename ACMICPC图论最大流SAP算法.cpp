/**=========================================================**\
算法分析：
SAP算法也是每次都找一条从源点到汇点的增广路径，只不过在找到一
条增广路径之后并不是又从源点开始而是从当前找到的增广路径的瓶
颈边往下找期望一次找到更多的边来减少搜索的时间。再就是这个算法
吸收的压入与重标记算法的顶点标号的方法，个每个点一个标号，源点
的标号最大不超过点的数量，因为一条简单路径n个点最多只含n-1条边
那么顶点标号实质就是从这个点出发到汇点要走的最少的边的数量。
当有边<u,v>且h[u]=h[v]+1时我们称这条边是一条可行边，每次找增广
路径都沿着可行边，当从某个点出发没有找到可行边就把这个点的标号
标记为它的最小子点标号加一，这样标号是一直增加的当有某个标号的
的点的数量为0时这时不管在怎么找也不会有增广路径了仅退出计算。
\**=========================================================**/

#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAX = 0xfffffff;

struct unit//边的数据结构，c为边的容量
{
	int v , c , next;
}edge[25];
//pre为每个点的前驱
int  n , m , head[10] , pre[10];
//curEdge为从每个点出发的可行边的存储位置，high为每个点的高度标号，hNum为相应标号点的数量
int curEdge[10] , high[10] , hNum[10];
int source , sink;//源点和汇点

void addedge(int u , int v , int  c , int &num)//增加一条边，及其反向边
{
	edge[num].c = c;
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;

	edge[num].c = 0;
	edge[num].v = u;
	edge[num].next = head[v];
	head[v] = num++;
}

int SAP()//最大流SAP算法
{
	int maxFlow = 0;//最大流
	memset(high , 0 , sizeof(high));//初始化
	memset(hNum , 0 , sizeof(hNum));
	memset(pre , -1 , sizeof(pre));

	for(int i = 1 ; i <= n ; i++)//把当前边置为每个点的第一条边
		curEdge[i] = head[i];

	hNum[0] = n;//高度为0的点的数量为n
	int u = source;
	while(high[source] < n)
	{
		if(u == sink)//当前为汇点说明找到一条增广路径
		{
			int minf = MAX , neck;
			//从源点出发沿增广路径找瓶颈边
			for(int k = source ; k != sink ; k = edge[curEdge[k]].v)
			{
				if(minf > edge[curEdge[k]].c)
				{
					neck = k;
					minf = edge[curEdge[k]].c;
				}
			}
			//从源点出发把增广路径上的边的容量及其反向边的容量修改
			for(int k = source ; k != sink ; k = edge[curEdge[k]].v)
			{
				int tmp = curEdge[k];
				edge[tmp].c -= minf;
				edge[tmp^1].c += minf;
			}
			//最大流加上新增加的流
			maxFlow += minf;
			u = neck;//下次从瓶颈边开始找增广路径
		}
		//找从当前点出发的可行边
		int k = curEdge[u];
		for(; k != -1 ; k = edge[k].next)
		{
			if(edge[k].c && high[u] == high[edge[k].v]+1)
				break;
		}

		if(k != -1)//找到可行边
		{
			curEdge[u] = k;//将当前点出发的可行边的位置修改
			pre[edge[k].v] = u;
			u = edge[k].v;//下次从可行边的下一个点搜索
		}
		else//没找到可行边
		{//当前点的标号要修改，所以先把对应的数量减一，如果为0就退出计算
			if(--hNum[high[u]] == 0) break;
			curEdge[u] = head[u];//把可行边记为第一条边
			int tmp = n ;
			//找从当前点出发标号最小的点的标号
			for(int k = head[u] ; k != -1 ; k = edge[k].next)
			{
				if(edge[k].c)
					tmp = min(tmp , high[edge[k].v]);
			}

			high[u] = tmp+1;//修改当前点的标号
			hNum[high[u]]++;
			if(u != source) u = pre[u];//从当前点出发没有增广路，从其父结点开始搜
		}
	}
	return  maxFlow;
}

int main()
{
	freopen("D:\\cruanjian\\桌面\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			addedge(u , v , c , num);
		}

		source = 1 , sink =  4;
		int maxFlow = SAP();
		cout<<maxFlow<<endl;
	}
	return 0;
}
