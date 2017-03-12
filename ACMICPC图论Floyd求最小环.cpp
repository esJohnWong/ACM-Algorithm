#include<iostream>
#include<cstring>

using namespace std;
/**======================================**\
�㷨������
floyd����С����˼��ĺ����ǣ�����ÿ�Ե���
����ʱ�����u��v�����·����һ�����У���ô��
�ɳ����������������صı�֮ǰ������u��v��
·���м����z֮ǰ���Է����������
����·��1->2->5->3->8->1��ô��8��δ����֮ǰ��
��ɼ��dist[1,3] + w[3,8] + w[8,1]�Ƿ�Ϊ����
�������Ϊ�����������һ���������ڲ�����
floyd�㷨�ǰѵ��С��������������ĳһ��·
�е�����������·��֮ǰ���Է��������·��
\**======================================**/
const int MAX = 0xfffffff;
//mapΪͼ��distΪÿ�Ե��ľ���
int map[6][6] , dist[6][6];
int n , m;

int floyd()
{
	int mincircle = MAX;//��С����Ȩֵ

	for(int i = 1 ; i <= n ; i++)//��ʼ��
	{
		for(int j = 1 ; j <= n ; j++)
			dist[i][j] = map[i][j];
	}

	for(int k = 1 ; k <= n ; k++)//k��ѭ����ÿ����·���м���һ����k
	{
		for(int i = 1 ; i <= n ; i++)
		{
			for(int j = 1 ; j <= n ; j++)
			{
				if(i == j) continue;//�����Ի�
				if(map[j][k] != MAX && map[k][i] != MAX && dist[i][j] != MAX)//����һ�������Ҽ����k����i��jֱ������
				{
					if(dist[i][j] + map[k][i] + map[j][k] < mincircle)
					{
						mincircle = dist[i][j] + map[k][i] + map[j][k] ;//������С����ֵ
						cout<<i<<" "<<j<<" "<<k<<" "<<mincircle<<endl;
					}

				}
			}
		}

		for(int i = 1 ; i <= n ; i++)//��ÿ�Ե��ľ���
		{
			for(int j = 1 ; j <= n ; j++)
			{
				if(dist[i][k] != MAX && dist[k][j] != MAX)
				{
					if(dist[i][j] > dist[i][k] + dist[k][j])
						dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	return mincircle;
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		for(int i = 1 ; i <= n ; i++)
		{
			for(int j = 1 ; j <= n ; j++)
			{
				if(i == j)
					map[i][j] = 0;
					else map[i][j] = MAX;
			}
		}

		for(int i = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			map[u][v] = c;
		}

		int mincircle = floyd();

		cout<<mincircle<<endl;
	}
	return 0;
}
