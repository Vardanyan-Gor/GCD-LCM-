#include <iostream>
#include <string>
#include "matrixencripting.h"
#include "Haffman.h"

using namespace std;

int main() {
    string testData = "hello world";
    cout << "Original Text: " << testData << endl;

    // Шифрование с помощью матричного шифрования
    string matEncrypted = MatrixCripto::encrypt(testData, 3);
    cout << "Matrix Encrypted: " << matEncrypted << endl;

    // Кодирование с помощью Хаффмана
    unordered_map<char, int> freqMap;
    for (char ch : matEncrypted) {
        freqMap[ch]++;
    }
    HuffmanNode* root = buildHuffmanTree(freqMap);
    unordered_map<char, string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);
    string huffmanEncoded = encode(matEncrypted, huffmanCodes);
    cout << "Huffman Encrypted: " << huffmanEncoded << endl;

    // Декодирование с помощью Хаффмана
    string huffmanDecoded = decode(root, huffmanEncoded);
    cout << "Huffman Decrypted: " << huffmanDecoded << endl;

    // Дешифрование с помощью матричного шифрования
    string matDecrypted = MatrixCripto::decrypt(huffmanDecoded, 3);
    cout << "Matrix Decrypted: " << matDecrypted << endl;

    return 0;
}
