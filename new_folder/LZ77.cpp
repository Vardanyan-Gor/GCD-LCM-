#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Структура для хранения триплетов (offset, length, character)
struct LZ77Token {
    int offset;
    int length;
    char nextChar;
};

// Функция для кодирования с использованием LZ77
vector<LZ77Token> lz77Encode(const string &input, int bufferSize) {
    vector<LZ77Token> tokens;
    int inputSize = input.size();
    
    for (int i = 0; i < inputSize;) {
        int matchOffset = 0;
        int matchLength = 0;
        char nextChar = input[i];
        
        // Поиск совпадений в окне
        int searchStart = max(0, i - bufferSize);
        for (int j = searchStart; j < i; ++j) {
            int k = 0;
            while (j + k < i && i + k < inputSize && input[j + k] == input[i + k]) {
                k++;
            }
            if (k > matchLength) {
                matchOffset = i - j;
                matchLength = k;
                nextChar = (i + k < inputSize) ? input[i + k] : '\0';
            }
        }
        
        // Добавляем токен (offset, length, nextChar)
        tokens.push_back({matchOffset, matchLength, nextChar});
        i += matchLength + 1;
    }
    return tokens;
}

// Функция для декодирования с использованием LZ77
string lz77Decode(const vector<LZ77Token> &tokens) {
    string decoded;
    for (const auto &token : tokens) {
        if (token.offset > 0) {
            int start = decoded.size() - token.offset;
            for (int i = 0; i < token.length; ++i) {
                decoded += decoded[start + i];
            }
        }
        if (token.nextChar != '\0') {
            decoded += token.nextChar;
        }
    }
    return decoded;
}

int main() {
    string text;
    int bufferSize;

    // Ввод строки для кодирования
    cout << "Enter text: ";
    getline(cin, text);

    // Ввод размера буфера
    cout << "Enter buffer size: ";
    cin >> bufferSize;

    // --- LZ77 Кодирование ---
    vector<LZ77Token> encoded = lz77Encode(text, bufferSize);
    cout << "\nLZ77 Encoded (offset, length, character):" << endl;
    for (const auto &token : encoded) {
        cout << "(" << token.offset << ", " << token.length << ", " 
             << (token.nextChar == '\0' ? ' ' : token.nextChar) << ")" << endl;
    }

    // --- LZ77 Декодирование ---
    string decoded = lz77Decode(encoded);
    cout << "\nLZ77 Decoded text: " << decoded << endl;

    return 0;
}
