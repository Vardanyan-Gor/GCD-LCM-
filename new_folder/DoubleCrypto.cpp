#include <iostream>
#include <string>
#include "MatrixCripto.h"
#include "Huffman.h"

using namespace std;

int main() {
    string testData = "hello world";
    cout << "Original Text: " << testData << endl;

    string matEncrypted = MatrixCripto::encrypt(testData, 3);
    cout << "Matrix Encrypted: " << matEncrypted << endl;

    string huffmanEncoded = Huffman::encode(matEncrypted);
    cout << "Huffman Encrypted: " << huffmanEncoded << endl;

    Huffman::Node* root = nullptr;
    string huffmanDecoded = Huffman::decode(huffmanEncoded, root);
    cout << "Huffman Decrypted: " << huffmanDecoded << endl;

    string matDecrypted = MatrixCripto::decrypt(huffmanDecoded, 3);
    cout << "Matrix Decrypted: " << matDecrypted << endl;

    return 0;
}
