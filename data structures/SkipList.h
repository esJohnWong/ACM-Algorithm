#pragma once
#include <vector>
#include <memory>

/**
 *	跳表1.0版实现了Put，Get，Delete三个但节点操作
 *	预计在下一个版本中实现使用迭代器的方式浏览一个指定范围内的数据
 *	以及删除一个范围内的数据
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
		int maxLevel = DEFAULT_MAX_LEVEL;		// 支持的最大层数
	};

	explicit SkipList(const ListConf &conf);
	~SkipList();

	SkipList(const SkipList&) = delete;
	SkipList& operator=(const SkipList&) = delete;

	/**
	 *	插入或者更新一个key的值
	 *	如果key存在则更新值，返回false
	 *	否则key不存在直接插入一个新的key和值，返回true
	 */
	bool Put(int key, int value);

	/**
	 *	删除一key值，如果存在这个key则删除并返回true
	 *	否则返回false
	 */
	bool Delete(int key);

	/**
	 *	获取与key关联的值，如果存在key则返回相应的值
	 *	否则返回空
	 */
	std::shared_ptr<int> Get(int key);

private:
	int RandomLevel();

	Head m_head;
	ListConf m_conf;
};

