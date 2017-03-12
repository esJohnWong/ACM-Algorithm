#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
/**=======================================**\
�㷨������
������С�㸲����ָ��V��ȡ�����ٵĵ����һ��
���ϣ�ʹ��E�����еı߶���ȡ�����ĵ�������
�㷨�������ζ�̬�滮��˼�롣E��ʾȡ�͡�
dp[u][0]��ʾ��u���ڵ㸲�ǣ�����uΪ����������
���ӵı߶������ǵ�����µ㸲�Ǽ�������������
�ٵ������
dp[u][1]��ʾ��u�����ڵ㸲�ǣ����Ե�uΪ������
���������ӵı߶������ǵ�����µ㸲�Ǽ�������
�������ٵ������
��
dp[u][0] = 1 + E(pre[v] = u)min(dp[v][1] , dp[v][0])
dp[u][1] = E(pre[v] = u)dp[v][0]
\**=======================================**/
struct E
{
	int v;
	int next;
}edge[20];

int head[10] , dp[10][2];

void mpc(int u , int pre)
{
	dp[u][0] = 1;//ÿ���㶼Ҫ��ʼ��������Ҷ�ӽڵ�ʱҲ����
	dp[u][1] = 0;

	for(int k = head[u] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(v == pre) continue;
		mpc(v , u);
		dp[u][0] += min(dp[v][1] , dp[v][0]);
		dp[u][1] += dp[v][0];
	}
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
	int n , m;
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v , num);
		}

		int root = 1;
		mpc(root , root);
		cout<<min(dp[root][0] , dp[root][1])<<endl;
	}
	return 0;
}
