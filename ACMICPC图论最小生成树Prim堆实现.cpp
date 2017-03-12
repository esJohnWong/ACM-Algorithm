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
��Ȩֵ�ͣ�����㷨ʹ����С��ʵ����ʱ�临�Ӷ���
Ϊo((N+M)logN)
\**===========================================**/
const int MAX = 0xfffffff;

int dist[12];
int n , m , head[12] , sum;
bool ins[12];
int pre[12];

struct E//����ʽǰ���Ǵ洢��
{
	int v , cap;
	int next;
}edge[30];

void addedge(int u , int v , int c)//���һ����
{
	edge[sum].v = v;
	edge[sum].cap = c;
	edge[sum].next = head[u];
	head[u] = sum++;

	edge[sum].v = u;
	edge[sum].cap = c;
	edge[sum].next = head[v];
	head[v] = sum++;

}

struct priority_queue//��С���ȼ�����
{
	int point[12];//�����е�ÿ����
	int position[12];//ÿ�����ڶ��������е�λ��
	int size;//���еĳ���

	void exchange(int x , int y)//���������е�������
	{
		int tmp = position[point[x]];//�Ƚ���λ��
		position[point[x]] = position[point[y]];
		position[point[y]] = tmp;

		tmp = point[x];//������
		point[x] = point[y];
		point[y] = tmp;
	}

	void init(int n , int s)//��ʼ����С����
	{
		size = n;
		for(int i = 1 ; i <= n ; i++)//��ʼ��ÿ���㼰��λ��
		{
			position[i] = i;
			point[i] = i;
		}
		exchange(position[s] , 1);//��Դ��s�ŵ����е���ǰ��
	}

	void min_heapify(int pos)//������С�ѵ�����
	{
		int l = pos * 2;
		int r = 2 * pos + 1;

		int minimum;
		if(l <= size && dist[point[l]] < dist[point[pos]])
			minimum = l;
			else minimum = pos;

		if(r <= size && dist[point[r]] < dist[point[minimum]])
			minimum = r;

		if(minimum != pos)
		{
			exchange(pos , minimum);
		}
	}

	int extract_min()//�����ؼ�ֵ��С�ĵ�
	{
		int min = point[1];
		point[1] = point[size];
		position[point[1]] = 1;
		size--;
		min_heapify(1);//�޸ĺ�Ҫ��������ʹ����Ȼ������С�ѵ�����
		return min;
	}

	void decrease(int poi , int key)//�޸�һ����poi�Ĺؼ�ֵ
	{
		dist[poi] = key;
		int pos = position[poi];
		while(pos > 1 && dist[point[pos]] < dist[point[pos/2]])
		{
			exchange(pos , pos/2);
			pos /= 2;
		}
	}

	bool empty()//�ж϶����Ƿ�Ϊ��
	{
		if(size == 0)
			return true;
			else return false;
	}
}Q;

void prim(int source)//Prim�㷨
{
	memset(ins , false , sizeof(ins));
	for(int i = 1 ; i <= n ; i++)
		dist[i] = MAX;

	dist[source] = 0;//����һ�����distֵ��Ϊ0
	Q.init(n , source);//��ʼ����С���ȼ�����

	while(!Q.empty())
	{
		int u = Q.extract_min();//����distֵ��С�ĵ�
		ins[u] = true;

		int e = head[u];//�޸��뵱ǰ�������ĵ��distֵ
		while(e != -1)
		{
			int v = edge[e].v;
			if(!ins[v] && dist[v] > edge[e].cap)
			{
				Q.decrease(v , edge[e].cap);
				pre[v] = u;
			}
			e = edge[e].next;
		}
	}
}

int main()
{
	freopen("D:\\cruanjian\\����\\in.txt", "r", stdin);
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		sum = 0;

		for(int i = 1 ;  i <= m ; i++)
		{
			int u , v , c;
			cin>>u>>v>>c;
			addedge(u , v , c);
		}

		prim(3);

		int res = 0;
		for(int i = 1 ; i <= n ; i++)
		{
			cout<<dist[i]<<endl;
			res += dist[i];
		}
		cout<<res<<endl;
	}
	return 0;
}
