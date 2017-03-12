#include<iostream>
#include<cstring>

using namespace std;
/**====================================**\
�㷨������
��������������ָ��V��ȡ������ĵ㣬ʹ��
��Щ��֮��û�б����������ڱ�<u,v>��u��v��
��ͬʱ�ڶ������У�����u��v�����ڶ������С�
����㷨����̰�Ĳ��ԣ����Ȱ��������������
��˳�����е㣬Ȼ���շ���ķ����ÿ����
���м�飬�����ǰ��û�б����ǣ��򽫵�ǰ
����������������ǵ�ǰ����丸��㶼��
���ǡ����ڵ�Ҫ��顣
\**====================================**/
struct E
{
	int v;
	int next;
}edge[20];

int head[10] , newpos[10] , now , pre[10];
bool select[10] , cover[10] , set[10];
int n , m;

void dfs(int x)
{
	newpos[now++] = x;
	for(int k = head[x] ; k != -1 ; k = edge[k].next)
	{
		if(!select[edge[k].v])
		{
			select[edge[k].v] = true;
			pre[edge[k].v] = x;
			dfs(edge[k].v);
		}
	}
}

int mis()
{
	int res = 0;
	memset(cover , false , sizeof(cover));
	memset(set , false , sizeof(set));

	for(int i = n - 1 ; i >= 0 ; i--)
	{
		int tmp = newpos[i];
		if(!cover[tmp])//�����ǰ��û�б���������뼯�ϣ�����ǵ�ǰ����丸���
		{
			set[tmp] = true;
			cover[tmp] = cover[pre[tmp]] = true;
			res++;
		}
	}
	return res;
}

void addedge(int u , int v , int &num)
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
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u ,v;
			cin>>u>>v;
			addedge(u , v , num);
		}

		int root = 1;
		memset(select , false , sizeof(select));
		select[root] = true;
		now = 0;
		pre[root] = root;
		dfs(root);

		int res = mis();
		cout<<res<<endl;
		for(int i = 1 ; i <= n ; i++)
			if(set[i]) cout<<i<<" ";
		cout<<endl;
	}
	return 0;
}
