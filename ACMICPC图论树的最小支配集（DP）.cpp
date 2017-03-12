#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
/**======================================**\
�㷨����:
������С֧�伯�Ǵ�V��ȡ�����ٵĵ����һ����
�ϣ�ʹ��V��ʣ��ĵ㶼��ȡ�����ĵ��б�������
����㷨�ǻ������ζ�̬�滮�ġ�
dp[u][0]��ʾ��u����֧�伯�����Ե�uΪ��������
���������˵������֧�伯�а��������ٵ�ĸ���
dp[u][1]��ʾu������֧�伯�����Ե�uΪ��������
���������ˣ�u�����в�����һ���ӽڵ㸲�����
��֧�伯�������������ٵ�ĸ�����
dp[u][2]��ʾu������֧�伯������uΪ����������
�����ǣ���û���ӽڵ㸲��u�����֧�伯������
�����ٵĵ�����
�򣺶�u�������ӽڵ㣬E��ʾȡ��
dp[u][0] = 1 + E(pre[v] = u)min(dp[v][0] , dp[v][1] , dp[v][2])
dp[u][2] = E(pre[v] = u)dp[v][1]
���uû���ӽڵ���dp[u][1] = INF
����dp[u][1] = E(pre[v] = u)min(dp[v][1] , dp[v][2]) + inc
���dp[u][1]�а�����ĳ��dp[v][0]��inc = 0
����inc = min(pre[v] = u)(dp[v][0] - dp[v][1])
��ǿ�ư�ĳ���㣨dp[v][0]��С����dp[v][0]��
��dp[u][1]����ʹ��u�����ǡ�
���Ľ��Ϊmin(dp[root][0] , dp[root][1])
\**======================================**/
const int MAX = 0xfffffff;//���������

struct E
{
	int v;
	int next;
}edge[20];

int head[10] , dp[10][3];

void mds(int u , int pre)
{
	dp[u][2] = 0;//��ʼ��
	dp[u][0] = 1;

	bool flag = false;
	int sum = 0 , inc = MAX;

	for(int k = head[u] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(v == pre) continue;
		mds(v , u);

		dp[u][0] += min(dp[v][0] , min(dp[v][1] , dp[v][2]));

		if(dp[v][0] <= dp[v][1])
		{
			sum += dp[v][0];
			flag = true;
		}
		else
		{
			sum += dp[v][1];
			inc = min(inc , dp[v][0] - dp[v][1]);
		}

		if(dp[v][1] != MAX && dp[u][2] != MAX)
			dp[u][2 ] += dp[v][1];
			else dp[u][2] = MAX;
	}

	if(inc == MAX && !flag)
		dp[u][1] = MAX;
		else
		{
			dp[u][1] = sum;
			if(!flag) dp[u][1] += inc;
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
		for(int  i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v , num);
		}

		int root = 1;
		mds(1 , 1);
		cout<<min(dp[root][0] , dp[root][1])<<endl;
	}
	return 0;
}
