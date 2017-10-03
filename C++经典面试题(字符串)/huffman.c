#include"huffman.h"
#include<string.h>
struct Tree {
	char Data;//����
	int Weight;//Ȩ��
	int ElemId;//ID
	struct Tree* LChild;//��ڵ�
	struct Tree* RChild;//�ҽڵ�
	struct Tree* Parent;//���ڵ�
};
struct Map {
	char Data[MAXSIZE];//����
	int Index[MAXSIZE];//���ֵĴ���
	int CurrIndex;//����
};
typedef struct Tree HuffTree;
typedef struct Map  HuffMap;
/*----------------------------------------------------
ͳ�Ƹ����ַ����ֵ�Ƶ��
str�ַ��� map���
------------------------------------------------------*/
static void GetStrCount(const char* str, HuffMap* map);
/*----------------------------------------------------
�ж�һ���ַ���map���Ƿ����
����� �򽫸�����һ
û�� ���һ��
------------------------------------------------------*/
static void IsHaveChar(const char ch, HuffMap* map);
/*----------------------------------------------------
��ʼ��map
data ���
index ���
currindex=0;
------------------------------------------------------*/
static void InitMap(HuffMap* map);
/*----------------------------------------------------
����huffman��
map ��
------------------------------------------------------*/
static HuffTree* CreatHuffTree(HuffMap* map);
/*----------------------------------------------------
�ӱ����ҵ���СƵ�ʵ���������
map ��
------------------------------------------------------*/
static void FindLowest(HuffMap* map);
/*----------------------------------------------------
�ӱ���ɾ����С������
���¹���map
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
				//��������
				map->Index[i] = map->Index[i] ^ map->Index[j];
				map->Index[j] = map->Index[i] ^ map->Index[j];
				map->Index[i] = map->Index[i] ^ map->Index[j];
				//��������
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
