/**===============================================**\
�㷨������
�������㷨�����ڶ���ͼ�в��ϵ�������·�������һ��·
���ı߽��������ƥ��M�кͲ�������M�У��������·��Ϊ
����·�������·���������յ�û��ƥ�������·������
�Կ����������������·��ֻҪ������·���ϲ�����ԭƥ��
�ı߼���ƥ�䣬��ԭƥ��ı�ɾ���γɵ���ƥ��ı߱ض���
��һ����
\**===============================================**/

#include<iostream>
#include<cstring>

using namespace std;

bool biGraph[6][6];//����ͼ
bool vist[6];//�����ߵĵ��Ƿ񱻷���
int matchRight[6] , matchLeft[6] ;//�ұߵĵ����ߵĵ�ֱ�ƥ�䵽�ĶԱߵĵ�

int nright , nleft , m;//����ƥ��ĵ������ܱ���

int findPath(int u)//��һ������·��
{
	for(int i = 1 ; i <= nright ; i++)
	{
		if(biGraph[u][i] && !vist[i])
		{
			vist[i] = true;
			if(matchRight[i] == -1 || findPath(matchRight[i]))//�ҵ��ұ�û��ƥ��ĵ�����Ѿ�ƥ�䵫���ҵ�һ������·��
			{
				matchLeft[u] = i;
				matchRight[i] = u;
				return 1;
			}
		}
	}
	return 0;
}

int maxMatch()
{
	int res = 0;
	memset(matchLeft , -1 , sizeof(matchLeft));
	memset(matchRight , -1 , sizeof(matchRight));

	for(int i = 1 ; i <= nleft ; i++)
	{
		if(matchLeft[i] == -1)//�����û��ƥ��ĵ㿪ʼ��
		{
			memset(vist , false , sizeof(vist));
			res += findPath(i);
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
