#include "SkipList.h"

#include <deque>
#include <random>

SkipList::SkipList(const ListConf &conf)
	: m_conf(conf)
	, m_head(conf.maxLevel)
{
}

SkipList::~SkipList()
{
	/**
	 *	ɾ���������Ƶ��������ʽ���ӵ�0��˳��ɾ������
	 */
	Node *curNode = m_head.header, *nextNode = nullptr;
	
	while ((nextNode = curNode->next[0]) != nullptr)
	{
		delete curNode;
		curNode = nextNode;
	}

	delete curNode;
	curNode = nullptr;
}

bool SkipList::Put(int key, int value)
{
	Node *curNode = m_head.header, *nextNode = nullptr;
	std::deque<Node*> updates;	// ��¼��ת����һ��ı߽�ڵ�
	
	/**
	 *	��������������ģ����Ҳ��Խ�߱�ʾ��key��ΧԽ��
	 *	����һ��һ����ң��𽥽����ҷ�Χ��С��ֱ�����һ��ȷ��λ��
	 */
	for (int level = m_head.level - 1; level >= 0; --level)
	{
		while (((nextNode = curNode->next[level]) != nullptr) && 
			(nextNode->key < key))
		{
			curNode = nextNode;
		}

		updates.push_front(curNode);
	}

	// key�Ѿ�����
	if (nextNode != nullptr && 
		nextNode->key == key)
	{
		nextNode->value = value;
		return false;
	}

	// ����һ������Ĳ���
	int insertLevel = RandomLevel();

	// �����ڵ�ǰ����ı߽�ڵ�����Ϊ����ͷ
	if (insertLevel > m_head.level)
	{
		for (int level = m_head.level; level < insertLevel; ++level)
		{
			updates.push_front(m_head.header);
		}

		m_head.level = insertLevel;
	}

	Node* insertNode = new Node(insertLevel, key, value);

	/**
	 *	��㵱ǰ�½ڵ��ÿ����һ���ڵ㣬����Ϊ�߽�ڵ���Ӧ�����һ���ڵ㣬
	 *	���߽�ڵ��Ӧ�����һ���ڵ�����Ϊ��ǰ�½ڵ�
	 */
	for (int level = 0; level < insertLevel; ++level)
	{
		insertNode->next[level] = updates[level]->next[level];
		updates[level]->next[level] = insertNode;
	}

	return true;
}

bool SkipList::Delete(int key)
{
	std::deque<Node*> updates;
	Node *curNode = m_head.header, *nextNode = nullptr;

	for (int level = m_head.level - 1; level >= 0; --level)
	{
		while ((nextNode = curNode->next[level]) != nullptr &&
			nextNode->key < key)
		{
			curNode = nextNode;
		}

		updates.push_front(curNode);
	}

	if (nextNode != nullptr &&
		nextNode->key == key)
	{
		/**
		 *	���Ƶ������ɾ�����ӵ�0�㵽��ɾ���ڵ�����һ��
		 *	��ÿ���ǰһ���ڵ����һ���ڵ�����Ϊ��ǰɾ���ڵ����һ���ڵ�
		 */
		for (int level = 0; level < static_cast<int>(nextNode->next.size()); ++level)
		{
			updates[level]->next[level] = nextNode->next[level];
		}

		delete nextNode;

		/**
		 *	ɾ����ɺ����ͷ�ڵ����߲㿪ʼ��������һ���ڵ�Ϊ�յĻ���
		 *	��˵�������Ѿ����Եݼ���
		 */
		for (int level = m_head.level - 1; level >= 0; --level)
		{
			if (m_head.header->next.back() == nullptr)
			{
				m_head.level -= 1;
			}
		}

		return true;
	}

	return false;
}

std::shared_ptr<int> SkipList::Get(int key)
{
	Node *curNode = m_head.header, *nextNode = nullptr;

	for (int level = m_head.level - 1; level >= 0; --level)
	{
		while ((nextNode = curNode->next[level]) != nullptr &&
			nextNode->key <= key)
		{
			if (nextNode->key == key)
			{
				return std::make_shared<int>(nextNode->value);
			}

			curNode = nextNode;
		}
	}

	return nullptr;
}

/**
 *	�������һ������0~m_conf.maxLevel�Ĳ���
 */
int SkipList::RandomLevel()
{
	std::random_device rd;
	std::uniform_int_distribution<int> intDist;

	int newLevel = 1;

	// �������ֱ����������Ϊֹ
	if (intDist(rd) % 2)
	{
		++newLevel;
	}

	newLevel = newLevel > m_conf.maxLevel ? m_conf.maxLevel : newLevel;
	return newLevel;
}
