/**=========================================================**\
�㷨������
SAP�㷨Ҳ��ÿ�ζ���һ����Դ�㵽��������·����ֻ�������ҵ�һ
������·��֮�󲢲����ִ�Դ�㿪ʼ���Ǵӵ�ǰ�ҵ�������·����ƿ
��������������һ���ҵ�����ı�������������ʱ�䡣�پ�������㷨
���յ�ѹ�����ر���㷨�Ķ����ŵķ�������ÿ����һ����ţ�Դ��
�ı����󲻳��������������Ϊһ����·��n�������ֻ��n-1����
��ô������ʵ�ʾ��Ǵ��������������Ҫ�ߵ����ٵıߵ�������
���б�<u,v>��h[u]=h[v]+1ʱ���ǳ���������һ�����бߣ�ÿ��������
·�������ſ��бߣ�����ĳ�������û���ҵ����б߾Ͱ������ı��
���Ϊ������С�ӵ��ż�һ�����������һֱ���ӵĵ���ĳ����ŵ�
�ĵ������Ϊ0ʱ��ʱ��������ô��Ҳ����������·���˽��˳����㡣
\**=========================================================**/

#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAX = 0xfffffff;

struct unit//�ߵ����ݽṹ��cΪ�ߵ�����
{
	int v , c , next;
}edge[25];
//preΪÿ�����ǰ��
int  n , m , head[10] , pre[10];
//curEdgeΪ��ÿ��������Ŀ��бߵĴ洢λ�ã�highΪÿ����ĸ߶ȱ�ţ�hNumΪ��Ӧ��ŵ������
int curEdge[10] , high[10] , hNum[10];
int source , sink;//Դ��ͻ��

void addedge(int u , int v , int  c , int &num)//����һ���ߣ����䷴���
{
	edge[num].c = c;
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;

	edge[num].c = 0;
	edge[num].v = u;
	edge[num].next = head[v];
	head[v] = num++;
}

int SAP()//�����SAP�㷨
{
	int maxFlow = 0;//�����
	memset(high , 0 , sizeof(high));//��ʼ��
	memset(hNum , 0 , sizeof(hNum));
	memset(pre , -1 , sizeof(pre));

	for(int i = 1 ; i <= n ; i++)//�ѵ�ǰ����Ϊÿ����ĵ�һ����
		curEdge[i] = head[i];

	hNum[0] = n;//�߶�Ϊ0�ĵ������Ϊn
	int u = source;
	while(high[source] < n)
	{
		if(u == sink)//��ǰΪ���˵���ҵ�һ������·��
		{
			int minf = MAX , neck;
			//��Դ�����������·����ƿ����
			for(int k = source ; k != sink ; k = edge[curEdge[k]].v)
			{
				if(minf > edge[curEdge[k]].c)
				{
					neck = k;
					minf = edge[curEdge[k]].c;
				}
			}
			//��Դ�����������·���ϵıߵ��������䷴��ߵ������޸�
			for(int k = source ; k != sink ; k = edge[curEdge[k]].v)
			{
				int tmp = curEdge[k];
				edge[tmp].c -= minf;
				edge[tmp^1].c += minf;
			}
			//��������������ӵ���
			maxFlow += minf;
			u = neck;//�´δ�ƿ���߿�ʼ������·��
		}
		//�Ҵӵ�ǰ������Ŀ��б�
		int k = curEdge[u];
		for(; k != -1 ; k = edge[k].next)
		{
			if(edge[k].c && high[u] == high[edge[k].v]+1)
				break;
		}

		if(k != -1)//�ҵ����б�
		{
			curEdge[u] = k;//����ǰ������Ŀ��бߵ�λ���޸�
			pre[edge[k].v] = u;
			u = edge[k].v;//�´δӿ��бߵ���һ��������
		}
		else//û�ҵ����б�
		{//��ǰ��ı��Ҫ�޸ģ������ȰѶ�Ӧ��������һ�����Ϊ0���˳�����
			if(--hNum[high[u]] == 0) break;
			curEdge[u] = head[u];//�ѿ��б߼�Ϊ��һ����
			int tmp = n ;
			//�Ҵӵ�ǰ����������С�ĵ�ı��
			for(int k = head[u] ; k != -1 ; k = edge[k].next)
			{
				if(edge[k].c)
					tmp = min(tmp , high[edge[k].v]);
			}

			high[u] = tmp+1;//�޸ĵ�ǰ��ı��
			hNum[high[u]]++;
			if(u != source) u = pre[u];//�ӵ�ǰ�����û������·�����丸��㿪ʼ��
		}
	}
	return  maxFlow;
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			addedge(u , v , c , num);
		}

		source = 1 , sink =  4;
		int maxFlow = SAP();
		cout<<maxFlow<<endl;
	}
	return 0;
}
