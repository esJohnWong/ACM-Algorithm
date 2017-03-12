/**===================================**\
�㷨������
����㷨�ĺ��Ļ����ҵ�һ������·����ֻ��
���õ���BFS����Ϊÿ����һ��ƥ���������
��·����ʱ����������ֻ��������һ�Ρ�
Ҳ�����޸�pre����ʱ����Ӱ��ǰ�������Ĺ�����
\**===================================**/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

bool biGraph[6][6];//����ͼ
int matchRight[6] , matchLeft[6];//���ҵ����Ӧƥ���
int vist[6] , pre[6];//vist��־һ������������·����ͬʱ�Ƿ񱻷��ʹ���preΪ���ÿ�������һ���ڵ�
int nright , nleft , m;//����ͼ�������ߵ���������Լ����еıߵ�����

int maxMatch()
{
	int res = 0;
	memset(matchLeft , -1 , sizeof(matchLeft));
	memset(matchRight , -1 , sizeof(matchRight));
	memset(vist , -1 , sizeof(vist));

	for(int i = 1 ; i <= nleft ; i++)
	{
		if(matchLeft[i] == -1)
		{
			queue<int> Q;
			Q.push(i);
			pre[i] = -1;
			bool flag = false;//��־�Ƿ��ҵ�����·

			while(!Q.empty() && !flag)
			{
				int u = Q.front();
				Q.pop();

				for(int v = 1 ; v <= nright && !flag ; v++)
				{//�ߴ��ڲ���û�з���
					if(biGraph[u][v] && vist[v] != i)
					{
						vist[v] = i;
						Q.push(matchRight[v]);//���ұߵ�ƥ�����ߵ�������
						if(matchRight[v] > 0)//û���ҵ�����·
						{
							pre[matchRight[v]] = u;//��¼��ߵ��˳��
						}
						else//�ҵ�����·
						{
							flag = true;
							int d = u , e = v ;
							while(d != -1)//��ԭƥ��ı�ȥ������ԭ������ƥ���еı�
							{
								int t = matchLeft[d];
								matchLeft[d] = e;
								matchRight[e] = d;
								d = pre[d] , e = t;
							}
						}
					}
				}
			}
			if(matchLeft[i] != -1)//����һ��ƥ��ı�
				res++;
		}
	}
	return res;
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt" , "r" , stdin);
	while(cin>>nright>>nleft>>m)
	{
		for(int i = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			biGraph[u][v] = true;
		}

		int res = maxMatch();
		cout<<res<<endl;
	}
	return 0;
}
