#include"huffman.h"
#include<string.h>
struct Tree {
	char Data;//数据
	int Weight;//权重
	int ElemId;//ID
	struct Tree* LChild;//左节点
	struct Tree* RChild;//右节点
	struct Tree* Parent;//父节点
};
struct Map {
	char Data[MAXSIZE];//数据
	int Index[MAXSIZE];//出现的次数
	int CurrIndex;//个数
};
typedef struct Tree HuffTree;
typedef struct Map  HuffMap;
/*----------------------------------------------------
统计各个字符出现的频率
str字符串 map结果
------------------------------------------------------*/
static void GetStrCount(const char* str, HuffMap* map);
/*----------------------------------------------------
判断一个字符在map中是否出现
如果有 则将个数加一
没有 添加一个
------------------------------------------------------*/
static void IsHaveChar(const char ch, HuffMap* map);
/*----------------------------------------------------
初始化map
data 清空
index 清空
currindex=0;
------------------------------------------------------*/
static void InitMap(HuffMap* map);
/*----------------------------------------------------
构建huffman树
map 表
------------------------------------------------------*/
static HuffTree* CreatHuffTree(HuffMap* map);
/*----------------------------------------------------
从表中找的最小频率的两个索引
map 表
------------------------------------------------------*/
static void FindLowest(HuffMap* map);
/*----------------------------------------------------
从表中删除最小的两个
重新构造map
------------------------------------------------------*/
static void DeleteLowest(HuffMap* map);


void GetStrCount(const char * str, HuffMap * map)
{
	char* p = str;
	while (*p++!='\0')
	{
		IsHaveChar(*p, map);
	}
}

void IsHaveChar(const char ch, HuffMap * map)
{
	for (int i = 0; i < map->CurrIndex; ++i)
	{
		if (ch == map->Data[i])
		{
			map->Index[i]++;
			return;
		}	
	}
	map->Data[map->CurrIndex] = ch;
	map->Index[map->CurrIndex]++;
	map->CurrIndex++;
}

void InitMap(HuffMap * map)
{
	memset(map->Data, '\0', sizeof(map->Data));
	memset(map->Index, 0, sizeof(map->Index));
	map->CurrIndex = 0;
}
void FindLowest(HuffMap* map)
{
	for (int i = 0; i < map->CurrIndex-1; ++i)
	{
		for (int j = i+1; j < map->CurrIndex; ++j)
		{
			if (map->Index[i] > map->Index[j])
			{
				//交换次数
				map->Index[i] = map->Index[i] ^ map->Index[j];
				map->Index[j] = map->Index[i] ^ map->Index[j];
				map->Index[i] = map->Index[i] ^ map->Index[j];
				//交换数据
				map->Data[i] = map->Data[i] ^ map->Data[j];
				map->Data[j] = map->Data[i] ^ map->Data[j];
				map->Data[i] = map->Data[i] ^ map->Data[j];
			}
		}
	}
}

void DeleteLowest(HuffMap * map)
{
	map->Data[0] = '\0';
	map->Index[0] += map->Index[1];
	for (int i = 1; i < map->CurrIndex-1; ++i)
	{
		map->Data[i] = map->Data[i + 1];
		map->Index[i] = map->Index[i + 1];
	}
	--map->CurrIndex;
}

HuffTree* CreatHuffTree(HuffMap* map)
{
	
}
