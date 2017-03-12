#include<iostream>
#include<cstring>
#include<stack>
#include<algorithm>

using namespace std;
/**=====================================**\
�㷨������
����ͼ��ǿ��ͨ��֧Tarjan�㷨��˼���Ƕ���һ
��ǿ��ͨ��֧������������һ����Ϊ����������
�������ҵ�������ĸ����������²��Ҷ�ӾͿ�
��ȷ�����ǿ��ͨ�����ˡ�
��ͼ�����������������ÿ������������״̬��
vist[u]=0ʱ��������㻹û�б��ѵ���Ϊ1ʱ��
��������Ѿ��ѵ���Ϊ2ʱ����������Ѿ���ͼ��
ɾ���ˡ���ͼ����һ��û�б����ʵĵ�u��ʼ����
�䱻���ʵ�ʱ�����tim�У�����u�����ڵĵ�v���
û�з��ʾͷ��ʣ����Ϊ1�ͱȽ�v��u��lowt��
(lowt��ʼ��Ϊtim)lowt[u]ȡ������С�ģ���Ҫ��
�����������丸����ӻ�ֱ����������lowt��
���С���������⣩������������ȶ���ǿ��ͨ��֧
֮�������������ɴ��ô���ǿ��ͨ��֧�ĸ���
����lowt=tim.�����ʵ���ÿһ���㶼�Ž��Ը���ջ�У�
��ջ�б�u�����ĵ㶼����uΪ����ǿ��ͨ��֧�еĵ㣬
Ȼ�����δε����Ϳ����ˡ�
\**=====================================**/
struct E
{
	int v , next;
}edge[15];

int head[10] , tim[10] , lowt[10];
int vist[10];
int n , m , scc[10];//sccΪ���ǿ��ͨ��֧�Ľ��
stack<int> s;

void tardfs(int u , int t , int &sccnum)
{
	vist[u] = 1;//����ǰ������Ϊ���ʣ���ѹ���ջ
	s.push(u);
	tim[u] = lowt[u] = t;//��ʼ������ʱ�估lowt
	for(int k = head[u] ; k != -1 ; k = edge[k].next)//ɨ��u�������ĵ�
	{
		int v = edge[k].v;
		if(vist[v] == 0) tardfs(v , ++t , sccnum);//���vû�з��ʾͷ���
		if(vist[v] == 1) lowt[u] = min(lowt[u] , lowt[v]);//���v����������ͬһ��ǿ��ͨ��֧�¾͸���lowt
	}

	if(lowt[u] == tim[u])//����u���������е㶼�������˺�lowt=tim ��uΪ��
	{
		sccnum++;//ǿ��ͨ��֧��������1
		while(s.top() != u)//��u�Ժ�ѹ��ĵ�ȫ����ջ
		{
			scc[s.top()] = sccnum;
			vist[s.top()] = 2;//�㱻��ͼ��ɾ��
			s.pop();
		}
		scc[s.top()] = sccnum;//��u��ջ
		vist[s.top()] = 2;
		s.pop();
	}
}

int tarjan()
{
	int sccnum = 0 , t = 0;
	memset(vist , 0 , sizeof(vist));
	memset(lowt , 0 , sizeof(vist));
	for(int i = 1 ; i <= n ; i++)
	{
		if(vist[i] == 0) tardfs(i , t , sccnum);//�����i��û�����ʾʹ�i����
	}
	return sccnum;
}

void addedge(int u , int v ,int &num)//ѹ��һ�������
{
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;
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
			addedge(u , v , num);
		}

		int num = tarjan();
		cout<<num<<endl;
		for(int i = 1 ; i <= n ; i++)
			cout<<i<<" "<<scc[i]<<endl;
	}
	return 0;
}
