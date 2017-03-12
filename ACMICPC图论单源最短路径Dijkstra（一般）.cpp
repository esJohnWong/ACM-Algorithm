#include<iostream>

using namespace std;
/**=======================================**\
�㷨������
��Դ�����·Dijkstra�㷨ά������������Sa,Sb
�Լ�һ��dist���㷨��ʼʱSaΪ�գ�Sb��Ϊȫ��ͼ
�ĵ㡣SaΪԴ�㵽��v�ľ���ȷ���˵ĵ�ļ��ϣ���
SbΪԲ�㵽v����̾��뻹ûȷ���ĵ�ļ��ϡ�ÿһ
�ζ���Sb��ѡһ����Դ�������̵ĵ�v�ӵ�Sa�У�
Ȼ����v������Sb�еĵ�ľ����޸ģ���Դ�㵽v
�ľ������v�����ľ���С�����Դ�㵽����
����ͽ�����dist�޸ġ�ʱ�临�Ӷ�Ϊo(n^2)��
\**=======================================**/
const int MAX = 0xfffffff;
//mapΪͼ��distΪԴ�㵽����ľ��룬preΪ����ĸ����
int map[6][6]  , dist[6] , pre[6];
bool insp[6];//��־һ�����Ƿ��ڼ���Sa��
int source , n , m;//sourceΪԴ�㣬nΪͼ�е�ĸ�����mΪ�ߵĸ���

void Dijkstra()
{
	for(int i = 1 ; i <= n ; i++)//��ʼ��
	{
		dist[i] = map[source][i];
		pre[i] = source;
		insp[i] = false;
	}
	dist[source] = 0;//Դ�㵽�Լ��ľ���Ϊ0����Sa��
	insp[source] = true;

	for(int i = 1 ; i <= n - 1 ; i++)//ÿ�ζ�Ҫ�ҳ�һ����Դ����̾���ȷ���˵ĵ�
	{
		int min = MAX;
		int k = 0;
		for(int j = 1 ; j <= n ; j++)//�ҳ�Sb�е�Դ�������С�ĵ�
		{
			if(!insp[j] && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}

		if(k == 0) break;//���û�ҵ����˳�����

		insp[k] = true;//���ҵ��ĵ�k�ŵ�Sa��

		for(int j = 1 ; j <= n ; j++)//�޸���Sb����k�����ĵ��distֵ
		{
			if(!insp[j] && map[k][j] != MAX && dist[j] > dist[k] + map[k][j])
			{
				dist[j] = dist[k] + map[k][j];
				pre[j] = k;
			}
		}
	}
}

int main()
{
	while(cin>>n>>m)
	{
		for(int i = 1 ; i <= n ; i++)//��ʼ��ͼ
			for(int j = 1 ; j <= n ; j++)
				map[i][j] = MAX;

		for(int i = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			map[u][v] = c;
		}

		source = 1 ;
		Dijkstra();

		int res = 0;
		for(int i = 1 ; i <= n ; i++)
			cout<<dist[i]<<endl;
	}
	return 0;
}
