#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
/**=========================================**\
�㷨������
����ͼ��ȫ����С�Ϊ��ͼG(V)�еĵ㻮��Ϊ����
����S,Tʹ������һ����S��T�ıߵ�Ȩֵ֮����С��
stoer_wanger�㷨��prim�㷨����.
1��ʼ����С��ansΪ�����T��Ϊͼ��ȫ���㡣
2��ͼ����ѡһ����s�ŵ�����S�ж���dist[p]ΪS��
�ĵ㵽T��һ��p��Ȩֵ�ܺ͡�
3������ѡ��s����ͼ�е�dist[p]��
4��dist[p]��ѡ��ֵ���ĵ���Ϊ�µ�s����S��=G(v)
�����3.
5������S���������Ϊs��t����dist[t]����ans��
6�½���c��Ȩw[c] = w[s,v]+w[t,v]��ɾ��������t
��s�����ıߡ�
7��|V|��=1���������2.
����㷨��prim�㷨���ơ�
���S������|V|-1��������С�����������Ϊÿ
�ζ���dist����һ����ŵ�S�����һ����һ����
dist��С�ĵ㣬����ʱ�����ù�����һ��������
ֻʣ���������ʱ�������߾�������С�ĸ������
ѡ��
\**=========================================**/
const int MAX = 0xfffffff;
//mapͼ����Ϣ��node����ÿ����ı�ţ�dist������
int map[10][10] , node[10] , dist[10];
int n , m;
bool vist[10];//vist��־һ�������û��

int stoerWanger()//����С����㷨
{//preΪ��һ��dist���ĵ㣬maxjΪ��ǰdist���ĵ�
	int ans = MAX , N = n , pre , maxj;
	for(int i = 1 ; i <= N ; i++)
		node[i] = i;//�ѵ�ı�ŷŽ�node��

	while(N > 1)
	{
		int m = -MAX;//����dist�����ֵ
		for(int i = 2 ; i <= N ; i++)//��һ��ѡnode[1]Ϊdist���ĵ�
		{
			dist[node[i]] = map[node[1]][node[i]];
			vist[node[i]] = false;
			if(dist[node[i]] > m)//����һ��dist���ĵ�
			{
				m = dist[node[i]];
				maxj = i;
			}
		}

		pre = 1;
		vist[node[1]] = true;

		for(int j = 2 ; j <= N ; j++)
		{
			vist[node[maxj]] = true;//�ѵ�ǰdist���ĵ����S��

			if(j != N)//��������������
			{
				pre = maxj;
				m = -MAX;
				for(int i = 1 ; i <= N ; i++)//����dist
				{
					if(!vist[node[i]])
					{
						dist[node[i]] += map[node[pre]][node[i]];
						if(dist[node[i]] > m)
						{
							m = dist[node[i]];
							maxj = i;
						}
					}
				}
			}
			else
			{
				ans = min(ans , m);//ans�����ĵ��dist�Ƚ�
				for(int i = 1 ; i <= N ; i++)//��c����Ϊpre��
				{
					map[node[pre]][node[i]] += map[node[maxj]][node[i]];
					map[node[i]][node[pre]] += map[node[maxj]][node[i]];
				}
				node[maxj] = node[N--];//�����һ����ŵ�maxj��λ�ã�maxj�����ǵ�
			}
		}
	}
	return ans;
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
				map[i][j] = 0;//��ֵΪ0�������ļ��㣬
				//0���Ա�ʾ[i,j]ȨֵΪ0�����ǲ����ڱ�<i,j>
			}
		}

		for(int i = 1 ; i <= m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			map[u][v] = map[v][u] = c;
		}

		int ans = stoerWanger();
		cout<<ans<<endl;
	}
	return 0;
}
