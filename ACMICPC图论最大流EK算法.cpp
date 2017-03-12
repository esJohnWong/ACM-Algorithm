/**===========================================**\
�㷨������
�����EK�㷨�Ļ���˼������������������·�����ҵ�
һ������·���ͼ�������·������ͨ�������������ƿ
���ߵ�������Ȼ���޸�����·���ϵ�ÿ���ߵ���������
��<u,v>��·���Ͼͼ�ȥ�������������<v,u>��������
�����ıߵ��������䡣Ȼ�������������·������һ��
����·����ֱ��û������·��Ϊֹ��
\**===========================================**/

#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>

using namespace std;

const int N = 8 , MAX = 0xfffffff;

int map[N][N] , pre[N];//mapΪ��·��preΪÿ�����ǰ��
int source , sink , n , m;//sourceΪԴ�㣬sinkΪ��㣬n�ǵ�����m�Ǳ���
bool vist[N];//��־һ�����Ƿ񱻷���

bool EKBfs()//��������·��
{
	queue<int> Q;
	memset(pre , -1 , sizeof(pre));
	memset(vist , false , sizeof(vist));
	Q.push(source);//�Ƚ�Դ��ѹ�����
	vist[source] = true;

	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		if(u == sink) return true;//�ҵ�һ������·��

		for(int v = 1 ; v <= n ; v++)
		{
			if(map[u][v] && !vist[v])//�ߴ�����vû������
			{
				vist[v] = true;
				pre[v] = u;
				Q.push(v);
			}
		}
	}
	return false;//û�ҵ�����·��
}

int EK()
{
	int maxFlow = 0 , minf;//minfΪ�ҵ�����·����·���Ͽ���ͨ�����������

	while(EKBfs())
	{
		minf = MAX;
		int v = sink;
		while(pre[v] != -1)//�Ӵӻ�㵽Դ����ƿ����
		{
			minf = min(minf , map[pre[v]][v]);
			v = pre[v];
		}

		maxFlow += minf;//��������ϸ��ҵ�������
		v = sink;
		while(pre[v] != -1)//�޸�����·�ϵ�����
		{
			int u = pre[v];
			map[u][v] -= minf;
			map[v][u] += minf;
			v = u;
		}
	}
	return maxFlow;
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		for(int i = 1 ; i <= n ; i++)//��ʼ��
			for(int j = 1 ; j <= n ; j++)
				map[i][j] = 0;

		for(int i = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			map[u][v] = c;
		}

		source = 1 , sink = 4;
		int maxFlow = EK();
		printf("%d\n" , maxFlow);
	}
 	return 0;
}
