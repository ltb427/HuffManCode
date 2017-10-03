#include"huffman.h"
#include<string.h>
struct Tree {
	char Data;//值
	int Weight;//权重
	int flag;//是否有值
	struct Tree* LChild;//左节点
	struct Tree* RChild;//右节点
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
/*----------------------------------------------------
遍历输出
------------------------------------------------------*/
static void PrintBTree_int(HuffTree* BT);
/*----------------------------------------------------
获取权值
------------------------------------------------------*/
static int WeightPathLength(HuffTree* FBT, int len);
/*----------------------------------------------------
哈夫曼编码
------------------------------------------------------*/
static void HuffManCoding(HuffTree* FBT, int len);


void GetStrCount(const char * str, HuffMap * map)
{
	char* p = str;
	while (*p++!='\0')
	{
		IsHaveChar(*(p-1), map);
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

void PrintBTree_int(HuffTree * BT)
{
	if (BT != NULL)
	{
		printf("%d", BT->Weight); //输出根结点的值
		if (BT->LChild != NULL || BT->RChild != NULL)
		{
			printf("(");
			PrintBTree_int(BT->LChild); //输出左子树
			if (BT->RChild != NULL)
				printf(",");
			PrintBTree_int(BT->RChild); //输出右子树
			printf(")");
		}
	}
}

HuffTree* CreatHuffTree(HuffMap* map)
{
	int i, j;
	HuffTree **b, *q;
	b = malloc((map->CurrIndex)*sizeof(HuffTree));
	for (i = 0; i < map->CurrIndex; i++) //初始化b指针数组，使每个指针元素指向a数组中对应的元素结点
	{
		b[i] = malloc(sizeof(HuffTree));
		b[i]->Weight = map->Index[i];
		b[i]->Data = map->Data[i];
		b[i]->flag = 1;
		b[i]->LChild = b[i]->RChild = NULL;
	}
	for (i = 1; i < map->CurrIndex; i++)//进行 n-1 次循环建立哈夫曼树
	{
		//k1表示森林中具有最小权值的树根结点的下标，k2为次最小的下标
		int k1 = -1, k2;
		for (j = 0; j < map->CurrIndex; j++)//让k1初始指向森林中第一棵树，k2指向第二棵
		{
			if (b[j] != NULL && k1 == -1)
			{
				k1 = j;
				continue;
			}
			if (b[j] != NULL)
			{
				k2 = j;
				break;
			}
		}
		for (j = k2; j < map->CurrIndex; j++)//从当前森林中求出最小权值树和次最小
		{
			if (b[j] != NULL)
			{
				if (b[j]->Weight < b[k1]->Weight)
				{
					k2 = k1;
					k1 = j;
				}
				else if (b[j]->Weight < b[k2]->Weight)
					k2 = j;
			}
		}
		//由最小权值树和次最小权值树建立一棵新树，q指向树根结点
		q = malloc(sizeof(HuffTree));
		q->Weight = b[k1]->Weight + b[k2]->Weight;
		q->LChild = b[k1];
		q->RChild = b[k2];
		q->flag = 0;
		
		b[k1] = q;//将指向新树的指针赋给b指针数组中k1位置
		b[k2] = NULL;//k2位置为空
	}
	if (map->CurrIndex == 1)
		q = b[0];
	free(b); //删除动态建立的数组b
	return q; //返回整个哈夫曼树的树根指针
}

//3、求哈夫曼树的带权路径长度
int WeightPathLength(HuffTree* FBT, int len)//len初始为0
{
	if (FBT == NULL) //空树返回0
		return 0;
	else
	{
		if (FBT->LChild == NULL && FBT->RChild == NULL)//访问到叶子结点
			return FBT->Weight * len;
		else //访问到非叶子结点，进行递归调用，返回左右子树的带权路径长度之和，len递增
			return WeightPathLength(FBT->LChild, len + 1) + WeightPathLength(FBT->RChild, len + 1);
	}
}

//4、哈夫曼编码（可以根据哈夫曼树带权路径长度的算法基础上进行修改）
void HuffManCoding(HuffTree* FBT, int len)//len初始值为0
{
	static int a[10];//定义静态数组a，保存每个叶子的编码，数组长度至少是树深度减一
	if (FBT != NULL)//访问到叶子结点时输出其保存在数组a中的0和1序列编码
	{
		if (FBT->LChild == NULL && FBT->RChild == NULL)
		{
			int i;
			printf("%c(权值为:%d)的编码：", FBT->Data,FBT->Weight);
			for (i = 0; i < len; i++)
				printf("%d", a[i]);
			if (len == 0)
				printf("%d", 0);
			printf("\n");
		}
		else//访问到非叶子结点时分别向左右子树递归调用，并把分支上的0、1编码保存到数组a
		{   //的对应元素中，向下深入一层时len值增1
			a[len] = 0;
			HuffManCoding(FBT->LChild, len + 1);
			a[len] = 1;
			HuffManCoding(FBT->RChild, len + 1);
		}
	}
}

void Test(const char * str)
{
	HuffMap map;
	InitMap(&map);
	GetStrCount(str, &map);
	HuffTree* tree = CreatHuffTree(&map);
	PrintBTree_int(tree);
	printf("\n");
	HuffManCoding(tree, 0);
}
