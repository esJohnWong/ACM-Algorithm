#include<iostream>
#include<cstring>
#include<stack>

using namespace std;
/**====================================**\
�㷨������
����ͼ��ǿ��ͨ��֧Garbow�㷨�Ƕ�Tarjan�㷨
�ĸĽ���Tarjan�㷨ÿ�ζ�Ҫά���������飬tim
��lowt���ҵ�һ��ǿ��ͨ�����ĸ��ڵ㡣��Garbow
��������������ջ���ҵ�ÿ��ǿ��ͨ�����ĸ���
stk1��ÿ���ҵ��Ľڵ�ѹ������������ָ��ڵ�
�ͰѸ��ͱȸ�����ĵ㶼������stk2�����Ҹ�
�ڵ�Ķ�ջ��������һ����ʱ�Ͱѳ����ڵ�����
����������������㵯���������һ���������
�ڽӵ㶼�����ʺ�stk2��ջ��Ϊ������������
���������ͨ�����ĸ����Ͱ���Ӧ����ͨ����
������
\**====================================**/
const int MAX = 0xfffffff;

struct E//����ߵ����ݽṹ
{
	int v , next;
}edge[15];
//timΪ���ʵ�ÿ�����ʱ�䣬sccΪÿ����������Ӧ���ĸ���ͨ����
int head[10] , tim[10] , scc[10];
stack<int> stk1 , stk2;//stk1Ϊ����ͨ�����Ķ�ջ��stk2Ϊ����ͨ�����ĸ�
int n , m;

void addEdge(int u , int v , int &num)//ѹ��һ����
{
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;
}

void garDfs(int u , int t , int &sccNum)//Garbow��������
{
	stk1.push(u);//�Ƚ�uѹ��������ջ
	stk2.push(u);
	tim[u] = t;//����u�ķ���ʱ��

	for(int k = head[u] ; k != -1 ; k = edge[k].next)//ɨ��u���ڽӵ�
	{
		int v = edge[k].v;
		if(tim[v] == 0)//���u���ڽӵ�vû�з��ʣ��ͷ���v
		{
			garDfs(v , ++t , sccNum);
		}
		else if(scc[v] == 0)//���v��������ûȷ�����ĸ���ͨ������
		{				//��ʱ˵�������˻�
			while(tim[stk2.top()] > tim[v])//�����ϳ�v����ĵ㶼ɾ��
			{
				stk2.pop();
			}
		}
	}

	if(stk2.top() == u)//u�������ڽӵ㶼ɨ����stk2��ջ��Ԫ�ص���u˵��u�ǵ�ǰ��ͨ�����ĸ�
	{
		stk2.pop();//��stk2�е�u����u������ǿ��ͨ�Ѿ����
		sccNum++;//��ͨ������һ
		while(stk1.top() != u)//u��u�Ժ�ѹ��ĵ㶼����ͬһ��ͨ��������stk1
		{
			scc[stk1.top()] = sccNum;
			stk1.pop();
		}
		scc[stk1.top()] = sccNum;
		stk1.pop();
	}
}

int garbow()//garbow������
{
	int sccNum = 0 , t = 1;
	memset(tim , 0 , sizeof(tim));
	memset(scc , 0 , sizeof(scc));

	for(int i = 1 ; i <= n ; i++)//��һ��û��ɨ�浽�ĵ����ɨ��
	{
		if(tim[i] == 0) garDfs(i , t , sccNum);
	}
	return sccNum;
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

		int sccNum = garbow();
		cout<<sccNum<<endl;
		for(int i = 1 ; i <= n ; i++)
			cout<<i<<" "<<scc[i]<<endl;
	}
	return 0;
}
