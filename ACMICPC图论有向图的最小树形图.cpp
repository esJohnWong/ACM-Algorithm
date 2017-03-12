#include<iostream>
#include<cstring>

using namespace std;
/**===================================**\
�㷨������
����ͼ����С����ͼGҪ����һ����������
1 G��û�л�
2 G�����ҽ���һ����v0�����καߵ��յ㣬
�������ĵ�ǡ����Ψһһ���ߵ��յ�
����㷨Ϊ�����㷨 ����� ������ 1965��
����
1' ��ͼ�г��˸��ڵ��⣬ȡ�����Ե�vΪ�յ�
�ı�����С��һ�����뵽�߼�E0�������ĳһ
��û�������ԭͼ��������С����ͼ���㷨��
��
2' ���E0���Ƿ��������ĵ��Լ����򻷣����
û����Ϊԭͼ����С����ͼ
1'' ���E0�������򻷣���v�ڻ��У�v'���ڻ�
����߰�����������һ����u��wΪ����Ϊ��vΪ
�յ�ıߵ�Ȩֵ�����µ�w<v',u>=w<v',v>-w
2'' �����С����ͼ�Ѿ��������������ĵ�
չ��ȥ������С����ͼ������ͬ�յ�ıߣ���
���ľ������յ���С����ͼ
����������Ĺ��������еĻ���Ȩֵ�ͼ�����
��һ����С����ͼ��Ȩֵ����Ҫ���������С
����ͼ��Ȩֵ
\**===================================**/
const int MAX = 0xfffffff;

int map[8][8];
bool flag[8];//��־һ�����Ƿ�������
bool visit[8];
int pre[8];
int sum;
int n , m;

void zhuliu(int source)
{
	sum = 0;
	memset(flag , false , sizeof(flag));
	pre[source] = source;

	while(true)
	{//����ÿ����Ϊ�յ����С�߼�E0
		for(int i = 1 ; i <= n ; i++)
		{
			if(i == source || flag[i]) continue;

			pre[i] = i;
			for(int j = 1 ; j <= n ; j++)
			{
				if(!flag[j] && map[j][i] < map[pre[i]][i])
					pre[i] = j;
			}

			if(pre[i] == i)//�����һ����û����߾��˳�����
			{
				sum = -1;
				return;
			}
		}

		int i;
		for(i = 1 ; i <= n ; i++)//���E0���Ƿ��л�
		{
			if(i == source || flag[i]) continue;
			memset(visit , false , sizeof(visit));

			visit[source] = true;
			int j = i;

			do
			{
				visit[j] = true;
				j = pre[j];
			}while(!visit[j]);

			if(j == source) continue;//�ҵ����ڵ�˵��û�л�

			i = j;//�������ɵ�j

			do//������С����ͼ��ֵ
			{
				sum += map[pre[j]][j];
				j = pre[j];
			}while(j != i);

			j = i;//���Ի��еĵ�Ϊ�յ�ıߵ�Ȩֵ�޸�
			do
			{
				for(int k = 1 ; k <= n ; k++)
				{// ��kû�������ұ�<k,j>���ڣ���k���ڻ���
					if(!flag[k] && map[k][j] < MAX && k != pre[j])
						map[k][j] -= map[pre[j]][j];
				}

				j = pre[j];
			}while(j != i);

			for(j = 1 ; j <= n ; j++)//����������i��������뻷�����ı߱����i����
			{
				if(j == i) continue ;

				int k = pre[i];
				while(k != i)
				{
					if(map[k][j] < map[i][j])//��ֹ�ر�
						map[i][j] = map[k][j];

					if(map[j][k] < map[j][i])
						map[j][i] = map[j][k];

					k = pre[k];
				}
			}

			for(j = pre[i] ; j != i ; j = pre[j])//�������ĵ���
				flag[j] = true;

			break;//���������γ��µ�ͼ ���µ�ͼ��ʼ��
		}

		if(i == n + 1)//���б߶������ڻ����ۼ�sum
		{
			for(int j = 1 ; j <= n ; j++)
			{
				if(j == source) continue ;
				if(!flag[j])
					sum += map[pre[j]][j];
			}
			break;//����whileѭ��
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
			{
				map[i][j] = MAX;
			}
		}

		for(int i = 0 ; i < m ; i++)
		{
			int  u , v , w;
			cin>>u>>v>>w;
			if(map[u][v] > w)
			{
				if(map[u][v] > w)//����ر�
					map[u][v] = w;
			}
		}

		zhuliu(1);

		printf("%d\n" , sum);
	}
	return 0;
}
