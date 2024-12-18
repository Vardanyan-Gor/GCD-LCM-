#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "ColumnarCipher.h"

using namespace std;

string ColumnarCipher::encrypt(const string& message, int key) {
    int numRows = (message.length() + key - 1) / key;
    vector<string> grid(numRows, string(key, ' '));

    int idx = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < key; ++j) {
            if (idx < message.length()) {
                grid[i][j] = message[idx++];
            }
        }
    }

    string result = "";
    for (int j = 0; j < key; ++j) {
        for (int i = 0; i < numRows; ++i) {
            result += grid[i][j];
        }
    }
    return result;
}

string ColumnarCipher::decrypt(const string& message, int key) {
    int numRows = (message.length() + key - 1) / key;
    vector<string> grid(numRows, string(key, ' '));
    int idx = 0;

    for (int j = 0; j < key; ++j) {
        for (int i = 0; i < numRows; ++i) {
            if (idx < message.length()) {
                grid[i][j] = message[idx++];
            }
        }
    }

    string result = "";
    for (int i = 0; i < numRows; ++i) {
        result += grid[i];
    }
    return result;
}

int main() {
    string testData = "helloWorld";
    cout << "Original text: " << testData << endl;

    cout << "\nColumnar Cipher:" << endl;
    string encrypted = ColumnarCipher::encrypt(testData, 4);
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << ColumnarCipher::decrypt(encrypted, 4) << endl;

    return 0;
}
