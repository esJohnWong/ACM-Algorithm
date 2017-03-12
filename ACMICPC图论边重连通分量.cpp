#include<iostream>
#include<cstring>
#include<stack>

using namespace std;
/**================================**\
�㷨������
�ߵ�����ͨ�����Ǻ͵������ͨ�����㷨
���Ƶģ�
low[u] = min(low[u] , dfn[u] , dfn[v](��·))
����low[v]>dfn[u]ʱv��v�Ժ�����ջ��
�㶼�ڱ�����ͨ�����У�u���ڣ���������
ͨuҲ�ڡ��پ��Ǻ͸������ͬһ������ͨ
��ĵ�Ҫ��������
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
			while(!stk.empty())//������ڵ������ı�����ͨ��������
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
	//freopen("D:\\cruanjian\\����\\in.txt" , "r" , stdin);
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
