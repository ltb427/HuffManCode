#include"huffman.h"
#include<string.h>
struct Tree {
	char Data;//ֵ
	int Weight;//Ȩ��
	int flag;//�Ƿ���ֵ
	struct Tree* LChild;//��ڵ�
	struct Tree* RChild;//�ҽڵ�
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
/*----------------------------------------------------
�������
------------------------------------------------------*/
static void PrintBTree_int(HuffTree* BT);
/*----------------------------------------------------
��ȡȨֵ
------------------------------------------------------*/
static int WeightPathLength(HuffTree* FBT, int len);
/*----------------------------------------------------
����������
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

void PrintBTree_int(HuffTree * BT)
{
	if (BT != NULL)
	{
		printf("%d", BT->Weight); //���������ֵ
		if (BT->LChild != NULL || BT->RChild != NULL)
		{
			printf("(");
			PrintBTree_int(BT->LChild); //���������
			if (BT->RChild != NULL)
				printf(",");
			PrintBTree_int(BT->RChild); //���������
			printf(")");
		}
	}
}

HuffTree* CreatHuffTree(HuffMap* map)
{
	int i, j;
	HuffTree **b, *q;
	b = malloc((map->CurrIndex)*sizeof(HuffTree));
	for (i = 0; i < map->CurrIndex; i++) //��ʼ��bָ�����飬ʹÿ��ָ��Ԫ��ָ��a�����ж�Ӧ��Ԫ�ؽ��
	{
		b[i] = malloc(sizeof(HuffTree));
		b[i]->Weight = map->Index[i];
		b[i]->Data = map->Data[i];
		b[i]->flag = 1;
		b[i]->LChild = b[i]->RChild = NULL;
	}
	for (i = 1; i < map->CurrIndex; i++)//���� n-1 ��ѭ��������������
	{
		//k1��ʾɭ���о�����СȨֵ�����������±꣬k2Ϊ����С���±�
		int k1 = -1, k2;
		for (j = 0; j < map->CurrIndex; j++)//��k1��ʼָ��ɭ���е�һ������k2ָ��ڶ���
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
		for (j = k2; j < map->CurrIndex; j++)//�ӵ�ǰɭ���������СȨֵ���ʹ���С
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
		//����СȨֵ���ʹ���СȨֵ������һ��������qָ���������
		q = malloc(sizeof(HuffTree));
		q->Weight = b[k1]->Weight + b[k2]->Weight;
		q->LChild = b[k1];
		q->RChild = b[k2];
		q->flag = 0;
		
		b[k1] = q;//��ָ��������ָ�븳��bָ��������k1λ��
		b[k2] = NULL;//k2λ��Ϊ��
	}
	if (map->CurrIndex == 1)
		q = b[0];
	free(b); //ɾ����̬����������b
	return q; //����������������������ָ��
}

//3������������Ĵ�Ȩ·������
int WeightPathLength(HuffTree* FBT, int len)//len��ʼΪ0
{
	if (FBT == NULL) //��������0
		return 0;
	else
	{
		if (FBT->LChild == NULL && FBT->RChild == NULL)//���ʵ�Ҷ�ӽ��
			return FBT->Weight * len;
		else //���ʵ���Ҷ�ӽ�㣬���еݹ���ã��������������Ĵ�Ȩ·������֮�ͣ�len����
			return WeightPathLength(FBT->LChild, len + 1) + WeightPathLength(FBT->RChild, len + 1);
	}
}

//4�����������루���Ը��ݹ���������Ȩ·�����ȵ��㷨�����Ͻ����޸ģ�
void HuffManCoding(HuffTree* FBT, int len)//len��ʼֵΪ0
{
	static int a[10];//���徲̬����a������ÿ��Ҷ�ӵı��룬���鳤������������ȼ�һ
	if (FBT != NULL)//���ʵ�Ҷ�ӽ��ʱ����䱣��������a�е�0��1���б���
	{
		if (FBT->LChild == NULL && FBT->RChild == NULL)
		{
			int i;
			printf("%c(ȨֵΪ:%d)�ı��룺", FBT->Data,FBT->Weight);
			for (i = 0; i < len; i++)
				printf("%d", a[i]);
			if (len == 0)
				printf("%d", 0);
			printf("\n");
		}
		else//���ʵ���Ҷ�ӽ��ʱ�ֱ������������ݹ���ã����ѷ�֧�ϵ�0��1���뱣�浽����a
		{   //�Ķ�ӦԪ���У���������һ��ʱlenֵ��1
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
