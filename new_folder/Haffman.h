#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Узел дерева Хаффмана
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char character, int frequency);
};

// Компаратор для приоритетной очереди
struct Compare {
    bool operator()(HuffmanNode *a, HuffmanNode *b);
};

// Построение дерева Хаффмана
HuffmanNode* buildHuffmanTree(const unordered_map<char, int> &freqMap);

// Построение таблицы кодов
void buildHuffmanCodes(HuffmanNode *node, const string &code, unordered_map<char, string> &huffmanCodes);

// Кодирование строки
string encode(const string &text, const unordered_map<char, string> &huffmanCodes);

// Декодирование строки
string decode(HuffmanNode *root, const string &encoded);

#endif // HUFFMAN_CODING_H
