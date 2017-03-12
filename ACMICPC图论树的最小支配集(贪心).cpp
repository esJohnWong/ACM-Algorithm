#include<iostream>
#include<cstring>

using namespace std;
/**================================================**\
�㷨������
������С֧�伯��ָ�Ӷ���V��ȡ�����ٵĵ����һ������V'
ʹ��V-V'�е����е㶼��V'�еĵ��б���������ʣ�µ�����
�㶼��ȡ���ĵ��б���������һ����uҪô��V����Ҫô��V'��
�ĵ����ڡ�
�������С֧�伯Ҫʹ��̰�ĵĲ��ԣ��Ƚ��������dfs����
һ��Ȼ�������˳�������ʼ��ÿ��������жϣ������
���㲻����С֧�伯�У�Ҳû����֧�伯�еĵ�����������
�������ĸ���㲻����֧�伯���������ĸ�������֧
�伯�����ڸ��ڵ㣬�丸����������
\**================================================**/
struct E//����ߵ����ݽṹ
{
	int v;
	int next;
}edge[20];

int head[10] , pre[10];//preΪÿ����ĸ����
bool select[10];//�ж�һ�������������ʱ���Ƿ��ѹ�
int newpos[10] , now;//newposΪ�������ʱ���˳��nowΪ�������ĵ�ĸ���
bool cover[10] , set[10];//coverΪ�ж�һ�����Ƿ񱻸��ǣ�setΪ��С֧�伯
int n , m;

void dfs(int x)//dfs�������˳��
{
	newpos[now++] = x;
	for(int k = head[x] ; k != -1 ; k = edge[k].next)
	{
		if(!select[edge[k].v])
		{
			select[edge[k].v] = true;
			pre[edge[k].v] = x;
			dfs(edge[k].v);
		}
	}
}

int mds()
{
	memset(cover , false , sizeof(cover));
	memset(set , false , sizeof(set));

	int res = 0;//��С֧�伯��ĸ���

	for(int i = n - 1 ; i >= 0 ; i--)
	{
		int tmp = newpos[i];
		if(!cover[tmp])//���һ����û�б�����
		{
			if(!set[pre[tmp]])//����㲻��֧�伯��
			{
				set[pre[tmp]] = true;//���������뼯����
				res++;
			}
			//��ǰ�㣬����㣬�����ĸ���㶼Ӧ�ñ�����
			cover[tmp] = cover[pre[tmp]] = cover[pre[pre[tmp]]] = true;
		}
	}
	return res;
}

void addedge(int u , int v , int &num)//���һ����
{
	edge[num].v = v;
	edge[num].next = head[u];
	head[u] = num++;

	edge[num].v = u;
	edge[num].next = head[v];
	head[v] = num++;
}

int main()
{
	while(cin>>n>>m)
	{
		memset(head , -1 , sizeof(head));
		for(int i = 0 , num = 0 ; i < m ; i++)
		{
			int u , v;
			cin>>u>>v;
			addedge(u , v , num);
		}

		int source = 1;
		now = 0;
		pre[source] = source;
		memset(select , false , sizeof(select));
		select[source] = true;
		dfs(source);//�Ӹ��ڵ㿪ʼ��

		int res = mds();//Ѱ����С֧�伯
		cout<<res<<endl;
		for(int i = 1 ; i <= n ; i++)//�����С֧�伯
			if(set[i]) cout<<i<<" ";
		cout<<endl;
	}
	return 0;
}
