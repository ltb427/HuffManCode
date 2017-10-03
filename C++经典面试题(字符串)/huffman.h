/*----------------------------------------------------------------------------
huffman编码以及解码
给定一篇用于通信的英文电文，统计该电文中每个字符出现的频率，按频率左小右大的方
法为这些字符建立哈夫曼(Huffamn)树，并编出每个字符的哈夫曼树码，输出该电文的哈夫
曼码译文。
【输入】
输入文件huffman.in是一篇用于通信的英文电文。
【输出】
输出文件huffman.out输出该电文的哈夫曼码译文。
【输入输出样例1】
huffman.i	          huffman.out
aaccdddbacbcddddddd	  011011000011101001100010001111111
-------------------------------------------------------------------------------*/
#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100


#ifdef __cplusplus
extern "C" {
#endif
	void Test(const char* str);
#ifdef __cplusplus
}
#endif
#endif
