#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

// Узел дерева Хаффмана
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};

// Компаратор для приоритетной очереди
struct Compare {
    bool operator()(HuffmanNode *a, HuffmanNode *b) {
        return a->freq > b->freq; // Узел с меньшей частотой должен быть выше в очереди
    }
};

// Построение дерева Хаффмана
HuffmanNode* buildHuffmanTree(const unordered_map<char, int> &freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // Добавляем все символы в приоритетную очередь
    for (const auto &pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Построение дерева
    while (pq.size() > 1) {
        HuffmanNode *left = pq.top(); pq.pop();
        HuffmanNode *right = pq.top(); pq.pop();

        // Создаём новый узел
        HuffmanNode *newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    return pq.top();
}

// Построение таблицы кодов
void buildHuffmanCodes(HuffmanNode *node, const string &code, unordered_map<char, string> &huffmanCodes) {
    if (!node) return;

    if (node->ch != '\0') { // Лист дерева
        huffmanCodes[node->ch] = code;
    }

    buildHuffmanCodes(node->left, code + "0", huffmanCodes);
    buildHuffmanCodes(node->right, code + "1", huffmanCodes);
}

// Кодирование строки
string encode(const string &text, const unordered_map<char, string> &huffmanCodes) {
    string encoded = "";
    for (char ch : text) {
        encoded += huffmanCodes.at(ch);
    }
    return encoded;
}

// Декодирование строки
string decode(HuffmanNode *root, const string &encoded) {
    string decoded = "";
    HuffmanNode *current = root;

    for (char bit : encoded) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (!current->left && !current->right) { // Достигли листа
            decoded += current->ch;
            current = root;
        }
    }

    return decoded;
}

int main() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);

    // Подсчёт частот символов
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    // Построение дерева Хаффмана
    HuffmanNode *root = buildHuffmanTree(freqMap);

    // Построение таблицы кодов
    unordered_map<char, string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);

    // Вывод таблицы кодов
    cout << "\nHuffman Codes:\n";
    for (const auto &pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Кодирование строки
    string encoded = encode(text, huffmanCodes);
    cout << "\nEncoded string: " << encoded << endl;

    // Декодирование строки
    string decoded = decode(root, encoded);
    cout << "\nDecoded string: " << decoded << endl;

    return 0;
}
