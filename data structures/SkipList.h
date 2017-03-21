#pragma once
#include <vector>
#include <memory>

/**
 *	����1.0��ʵ����Put��Get��Delete�������ڵ����
 *	Ԥ������һ���汾��ʵ��ʹ�õ������ķ�ʽ���һ��ָ����Χ�ڵ�����
 *	�Լ�ɾ��һ����Χ�ڵ�����
 */
class SkipList
{
	struct Node
	{
		int key = 0;
		int value = 0;
		std::vector<Node*> next;

		explicit Node(int maxLevel, int k = 0, int v = 0)
			: key(k)
			, value(v)
		{
			next.resize(maxLevel);
		}
	};

	struct Head
	{
		int level = 0;
		Node* header;
		
		Head(int maxLevel)
			: header(new Node(maxLevel))
		{}
	};
public:
	struct ListConf
	{
		static constexpr int DEFAULT_MAX_LEVEL = 16;
		int maxLevel = DEFAULT_MAX_LEVEL;		// ֧�ֵ�������
	};

	explicit SkipList(const ListConf &conf);
	~SkipList();

	SkipList(const SkipList&) = delete;
	SkipList& operator=(const SkipList&) = delete;

	/**
	 *	������߸���һ��key��ֵ
	 *	���key���������ֵ������false
	 *	����key������ֱ�Ӳ���һ���µ�key��ֵ������true
	 */
	bool Put(int key, int value);

	/**
	 *	ɾ��һkeyֵ������������key��ɾ��������true
	 *	���򷵻�false
	 */
	bool Delete(int key);

	/**
	 *	��ȡ��key������ֵ���������key�򷵻���Ӧ��ֵ
	 *	���򷵻ؿ�
	 */
	std::shared_ptr<int> Get(int key);

private:
	int RandomLevel();

	Head m_head;
	ListConf m_conf;
};

