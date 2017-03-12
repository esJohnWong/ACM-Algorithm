#include<iostream>

using namespace std;
/**========================**\
�㷨������
floyd�㷨���ڶ�̬�滮��˼�뵫
��Ҫ��ͼ��û�и�Ȩ��·��
[i,j]����̼�·��������ֻ��
��n�������Ծ���n��ѭ��������
ÿ����·�������һ����k�����
k������·������ԭ����dist[i][j]����
dist[i][j] > dist[i][k] + dist[k][j]
�ͽ�dist[i][j]���£����򲻱䡣
��Ӧ��pre[i][j]����ʾ��i��j����
��·����j�ĸ���㣩��Ϊpre[k][j]
���򲻱䡣
\**========================**/
const int MAX = 0xfffffff;
//mapΪͼ����Ϣ��distΪ���յĽ����pre[i][j]��ʾ��i��j�����·����j�ĸ����
int map[6][6] , dist[6][6] , pre[6][6];
int n , m;

void init()
{
	for(int i = 1 ; i <= n ; i++)//��ʼ��map
		for(int j = 1 ; j <= n ; j++)
		{
			map[i][j] = MAX;
			if(i == j)//���i=j��i���Լ���·��Ȩֵ��Ϊ0�����ʼ��Ϊ�����
				map[i][j] = 0;
		}

	for(int i = 0 ; i < m ; i++)
	{
		int u , v , c;
		cin>>u>>v>>c;
		map[u][v] = c;
	}
}

void floyd()
{
	for(int i = 1 ; i <= n ; i++)//��ʼ��dist��pre
		for(int j = 1 ; j <= n ; j++)
		{
			if(i == j || map[i][j] == MAX)//�����i���Լ���j��·��pre[i][j]Ϊ0����Ϊi
				pre[i][j] = 0;
				else pre[i][j] = i;
			dist[i][j] = map[i][j];//i��j֮��û�������ĵ�ʱdistΪͼ��Ȩֵ
		}

	for(int k = 1 ; k <= n ; k++)//������[i,j]����·���м�һ����k
	{
		for(int i = 1 ; i <= n ; i++)
			for(int j = 1 ; j <= n ; j++)
			{
				if(dist[i][k] == MAX || dist[k][j] == MAX)
					continue;
				if(dist[i][j] > dist[i][k] + dist[k][j])//k��[i,j]�����·����
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					pre[i][j] = pre[k][j];
				}
			}
	}
}

void printpath(int i , int j)//��ӡ·��
{
	if(i == j) printf("%d" , i);
		else if(pre[i][j] == 0) printf("no path from %d to %d\n" , i , j);
		else
		{
			printpath(i , pre[i][j]);
			printf("->%d" , j);
		}
}


int main()
{
	while(cin>>n>>m)
	{
		init();
		floyd();

		for(int i = 1 ; i <= n ; i++)
			for(int j = 1 ; j <= n ;j++)
			{
				printf("%d " , dist[i][j]);
				printpath(i , j);
				printf("\n");
			}
	}
	return 0;
}
