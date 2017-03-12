#include<iostream>
#include<cstring>

using namespace std;
/**===========================================**\
�㷨������
�㷨��ͼ�����еĵ��Ϊ������������С��������ǰ��
���ҵ��ĵ�ļ��ϣ����ڵ�ǰ�ҵ�����С�������ĵ��
��������ҵ�һ����v����С��������ǰ�㼯��S�оͰ�
�������Ϊ��S�У��㷨ά����һ��dist���飬�����
v��S����dist[v]��ʾv��v��ǰ��u�ıߵ�Ȩֵmap[u][v]
��dist[v]�������ٸ��ģ����v����S����dist[v]��ʾ
������S�еĵ�u��v�����ıߵ���СȨֵ���㷨ÿ�δ�
����S�еĵ���Ѱ��һ������distֵ��С���ҵ�����
�������S���޸���v����������S�еĵ�t��dist��ֵ
Ȼ���ִӲ���S�еĵ�����һ��dist��С�ĵ㣬ֱ����
�еĵ�ȫ����S�н�������dist�ĺ;�Ϊ��С������
��Ȩֵ�ͣ�ʱ�临�Ӷ�o(n^2)���ռ临�Ӷ�o(n^2)
\**===========================================**/
const int MAX = 0xfffffff;

int map[10][10];
int n , m;
int dist[10] , pre[10];
bool ins[10];

void prim(int source)
{
	for(int i = 1 ; i <= n ; i++)
	{
		ins[i] = false;
		dist[i] = map[source][i];
		pre[i] = source;
	}

	dist[source] = 0;
	ins[source] = true;

	for(int i = 1 ; i < n ; i++)
	{
		int min = MAX;
		int k = 0 ;
		for(int j = 1 ; j <= n ; j++)
		{
			if(!ins[j] && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}

		if(k == 0) return ;

		ins[k] = true;
		for(int j = 1 ; j <= n ; j++)
		{
			if(!ins[j] && map[k][j] != MAX && dist[j] > map[k][j])
			{
				dist[j] = map[k][j];
				pre[j] = k;
			}
		}
	}
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt", "r", stdin);
	while(cin>>n>>m)
	{
		for(int i = 1 ; i <= n ; i++)
		{
			for(int j = 1 ; j <= n ; j++)
				map[i][j] = MAX;
		}

		for(int i = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			map[u][v]= map[v][u] = c;
		}

		prim(3);

		int ans = 0;
		for(int i = 1 ; i <= n ; i++)
		{
			cout<<dist[i]<<endl;
			ans +=  dist[i];
		}

		cout<<ans<<endl;
	}
	return 0;
}
