#include<iostream>
#include<algorithm>
#include<cstring>
#include<stack>

using namespace std;
/**=================================**\
�㷨������
ͼ������ͨ����������ͼ�д���һ������
��ͼʹ������ͼ�����κ�һ����ͼ������ͨ
������һ��ͼ������ͨͼ���ҽ������ͼ��
������һ�㣬�����ɾ����ͼ��Ϊ�����ͨ
ͼ����һ���Ϊ�ؽڵ㡣����ͨ����������
����ͼ����������ͨ���������ܹ���һ����
�ϵĽڵ㡣
�ȶ�ԭͼ������������������γ�һ�����
���������Ը��ڵ����Ϊһ���ؽڵ㣨��㣩
����ڵ�����������������������ӣ��Բ�
�Ǹ��ڵ�������������dfn[u]<=low[v]��
�����ҲΪ��㣬ÿһ��������һ������
ͨ�ĸ���ͬһ�����ͬʱ���ڶ������ͨͼ��
dfnΪdepth first number��Ϊÿ��������
���ȷ��ʵ�ʱ��ʱ�䣬low[u] = min(dfn[u] , low[v])
\**=================================**/
struct E//����ߵ����ݽṹ
{
	int v , next;
}edge[28];
//bccΪ����ͨ�����Ľ����dfnÿ������ʵ���ʱ�䣬lowΪ������
int head[11] , bcc[11][11] , dfn[11] , low[11];
int n , m;
stack<int> stk;

void addEdge(int u , int v , int &num)//��ӱ�
{
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;

	edge[num].v = u;
	edge[num].next = head[v];
	head[v] = num++;
}

void tarDfs(int u , int &tim , int &bccNum , int pre)//dfs��������
{
	stk.push(u);
	dfn[u] = low[u] = ++tim;//��ʼ��dfn��lowΪ���ʵ�ʱ��
	for(int k = head[u] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(v == pre) continue;//u���ӽڵ㲻���Ժ���ֱ�Ӹ�����ͬ
		if(dfn[v] == 0)//vû�з���
		{
			tarDfs(v , tim , bccNum , u);//��������v
			low[u] = min(low[u] , low[v]);
			if(low[v] >= dfn[u])//u��һ�������u��v�Լ�v�Ժ�ѹ��ĵ㶼���������ͨ��
			{
				bcc[bccNum][0] = u;//���ε�����ͬһ������ͨ�еĵ�
				int cnt = 1;
				while(stk.top() != v)
				{
					bcc[bccNum][cnt++] = stk.top();
					stk.pop();
				}
				bcc[bccNum][cnt++] = stk.top();
				stk.pop();
				bcc[bccNum][cnt++] = -1;//����������
				bccNum++;
			}
		}
		else low[u] = min(low[u] ,dfn[v]);//v�����ʹ����������˻�·
	}
}

int tarjan()//������ͨ��������
{
	int bccNum = 0 , tim = 0;
	memset(low , 0 , sizeof(low));
	memset(dfn , 0 , sizeof(dfn));
	while(!stk.empty())//��ջ���
	{
		stk.pop();
	}

	for(int i = 1 ; i <= n ; i++)
	{
		if(dfn[i] == 0) tarDfs(i , tim , bccNum , 0);
	}

	return bccNum;
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt" , "r" , stdin);
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
		cout<<tarjan()<<endl;
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
