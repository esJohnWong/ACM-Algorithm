#include<iostream>
#include<cstring>

using namespace std;
/**==================================**\
�㷨����:
������С�㸲�Ǿ��Ǵ�V��ȡ�����ٵĵ�ʹ��
E�����еı߶���ȡ�����ĵ�������
����㷨Ҳ�ǻ���̰��˼�룬���Ȱ��ն�����
������ȴ���ķ�����У������ǰ����丸
�ڵ㶼û�б����ǣ��򽫸������뵽��С��
���Ǽ��ϣ���ǵ�ǰ����丸��㶼�����ǡ�
���Ƕ��ڸ��ڵ��ǲ����Լ��ġ�
\**==================================**/
struct E//�ߵ����ݽṹ
{
	int v;
	int next;
}edge[20];
//newposΪ�������ʱ�ĵ�Ĵ���nowΪ�Ѿ��ж��ٵ㱻���ʣ�preΪÿ����ĸ����
int head[10] , newpos[10] , now , pre[10];
bool select[10] , cover[10] , set[10];//selecΪ�ж�ĳ�����Ƿ񱻷����ˣ�cover���ĳ�����Ƿ񱻸��ǣ�setΪ��С�㸲�Ǽ���
int n , m;

void dfs(int x)
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

int mpc()
{
	int res = 0;
	memset(cover , false , sizeof(cover));
	memset(set , false , sizeof(set));

	for(int i = n - 1 ; i >= 1 ; i--)
	{
		int tmp = newpos[i];
		if(!cover[tmp] && !cover[pre[tmp]])//�����ǰ����丸��㶼û�����ǣ��򽫸������뼯��
		{
			set[pre[tmp]] = true;
			cover[tmp] = cover[pre[tmp]] = true;
			res++;
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

		int root = 1;
		memset(select , false , sizeof(select));
		select[root] = true;//��Ǹ��ڵ��ѱ�����
		pre[root] = root;//���ڵ�ĸ����Ϊ����
		now = 0;
		dfs(root);

		int res = mpc();
		cout<<res<<endl;
		for(int i = 1 ; i <= n ; i++)
			if(set[i]) cout<<i<<" ";
		cout<<endl;
	}
	return 0;
}
