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
	 *	删除操作类似单链表的形式，从第0层顺序删除即可
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
	std::deque<Node*> updates;	// 记录跳转到下一层的边界节点
	
	/**
	 *	由于跳表是有序的，并且层次越高表示的key范围越大
	 *	所以一层一层的找，逐渐将查找范围缩小，直到最后一层确定位置
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

	// key已经存在
	if (nextNode != nullptr && 
		nextNode->key == key)
	{
		nextNode->value = value;
		return false;
	}

	// 产生一个随机的层数
	int insertLevel = RandomLevel();

	// 将高于当前最大层的边界节点设置为链表头
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
	 *	逐层当前新节点的每层下一个节点，设置为边界节点相应层的下一个节点，
	 *	将边界节点对应层的下一个节点设置为当前新节点
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
		 *	类似单链表的删除，从第0层到待删除节点的最后一层
		 *	将每层的前一个节点的下一个节点设置为当前删除节点的下一个节点
		 */
		for (int level = 0; level < static_cast<int>(nextNode->next.size()); ++level)
		{
			updates[level]->next[level] = nextNode->next[level];
		}

		delete nextNode;

		/**
		 *	删除完成后，如果头节点从最高层开始出现了下一个节点为空的话，
		 *	则说明层数已经可以递减了
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
 *	随机产生一个介于0~m_conf.maxLevel的层数
 */
int SkipList::RandomLevel()
{
	std::random_device rd;
	std::uniform_int_distribution<int> intDist;

	int newLevel = 1;

	// 随机产生直到产生奇数为止
	if (intDist(rd) % 2)
	{
		++newLevel;
	}

	newLevel = newLevel > m_conf.maxLevel ? m_conf.maxLevel : newLevel;
	return newLevel;
}
