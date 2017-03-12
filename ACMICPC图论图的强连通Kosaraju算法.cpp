#include<iostream>
#include<cstring>

using namespace std;
/**===============================**\
�㷨������
������ͼ��ǿ��ͨ��֧���Ȱ�ԭͼ�����
������һ�飬�õ�ÿ����Ľ���ʱ�䣬��
ÿ������ӵ㶼������ʱ�����Ľ�����
��ʱ�䡣Ȼ���ս�������ʱ��ݼ���˳
�򣬰�ԭͼ����������һ�飬��ʱ��ĳ��
��ɴ��ȫ���������ԭͼ��һ��ǿ��ͨ
��֧��
\**===============================**/
struct E
{
	int v , c , next;
}edge[15] , tedge[15];//ԭͼ�ıߣ������

int head[10] , thead[10];
int tim[10] , scc[10];//tim��һ�������Ľ���ʱ�䣬sccǿ��ͨ��֧
int n , m;
bool vist[10];//���һ�����Ƿ��ѵ�

void dfsone(int cur , int &t)//��ԭͼ���е������������
{
	vist[cur] = true;
	for(int k = head[cur] ; k != -1 ; k = edge[k].next)
	{
		int v = edge[k].v;
		if(!vist[v]) dfsone(v , t);
	}
	tim[++t] = cur;//��һ������ӵ㱻������ɺ󣬾ͼ���������������ʱ��
}

void dfstwo(int cur , int num)//�ڶ��ζԷ���ͼ������
{
	vist[cur] = true;
	scc[cur] = num;//numΪ��ÿ���������ĸ�ǿ��ͨ��֧�ı��
	for(int k = thead[cur] ; k != -1 ; k = tedge[k].next)
	{
		int v = tedge[k].v;
		if(!vist[v]) dfstwo(v , num);
	}
}

int Kosaraju()
{
	memset(vist , false , sizeof(vist));
	int t = 0;
	for(int i = 1 ; i <= n ; i++)//��һ��ԭͼ�������õ�����ʱ��
	{
		if(!vist[i]) dfsone(i , t);
	}

	int num = 0;
	memset(vist , false , sizeof(vist));
	for(int i = t ; i >= 1 ; i--)//�ڶ��鷴��ͼ������ȷ��ÿ���������ĸ���ͨ��֧
	{
		int u = tim[i];//ȡ�õ�iʱ������ĵ�
		if(!vist[u]) dfstwo(u , num++);
	}
	return num;
}

void addedge(int u , int v , int &num)//ѹ���
{
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num;

	tedge[num].v = u;
	tedge[num].next = thead[v];
	thead[v] = num++;
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt" , "r" , stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		memset(thead , -1 , sizeof(thead));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v , num);
		}

		int num = Kosaraju();
		cout<<num<<endl;
		for(int i = 1 ; i <= n ; i++)
			cout<<i<<" "<<scc[i]<<endl;
	}
	return 0;
}
