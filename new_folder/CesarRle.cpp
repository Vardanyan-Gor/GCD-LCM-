#include <iostream>
#include <string>
using namespace std;

// Функция шифрования Цезаря
string caesarEncrypt(const string &input, int shift) {
    string encrypted = "";
    for (char ch : input) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            encrypted += (ch - base + shift) % 26 + base;
        } else {
            encrypted += ch;
        }
    }
    return encrypted;
}

// Функция расшифровки Цезаря
string caesarDecrypt(const string &input, int shift) {
    string decrypted = "";
    for (char ch : input) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            decrypted += (ch - base - shift + 26) % 26 + base;
        } else {
            decrypted += ch;
        }
    }
    return decrypted;
}

// Функция RLE-кодирования
string rleEncode(const string &input) {
    string encoded = "";
    int n = input.length();
    for (int i = 0; i < n; i++) {
        int count = 1;
        while (i < n - 1 && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        encoded += input[i] + to_string(count);
    }
    return encoded;
}

// Функция RLE-декодирования
string rleDecode(const string &input) {
    string decoded = "";
    int n = input.length();
    for (int i = 0; i < n; i++) {
        char ch = input[i];
        string countStr = "";
        while (i + 1 < n && isdigit(input[i + 1])) {
            countStr += input[++i];
        }
        int count = stoi(countStr);
        decoded += string(count, ch);
    }
    return decoded;
}

int main() {
    string text;
    int shift;

    // Ввод строки для шифрования
    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter Caesar shift: ";
    cin >> shift;

    // 1. Шифрование Цезаря
    string caesarEncoded = caesarEncrypt(text, shift);
    cout << "\nCaesar Encrypted: " << caesarEncoded << endl;

    // 2. RLE-кодирование результата шифрования Цезаря
    string rleEncoded = rleEncode(caesarEncoded);
    cout << "RLE Encoded: " << rleEncoded << endl;

    // 3. RLE-декодирование
    string rleDecoded = rleDecode(rleEncoded);
    cout << "RLE Decoded: " << rleDecoded << endl;

    // 4. Расшифровка Цезаря
    string caesarDecoded = caesarDecrypt(rleDecoded, shift);
    cout << "Caesar Decoded: " << caesarDecoded << endl;

    return 0;
}
