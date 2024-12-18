#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Функция шифрования
string caesarEncrypt(const string& input, int shift) {
    string encrypted = "";
    for (char c : input) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            encrypted += (c - base + shift) % 26 + base;
        } else {
            encrypted += c;
        }
    }
    return encrypted;
}

// Функция дешифрования
string caesarDecrypt(const string& input, int shift) {
    return caesarEncrypt(input, 26 - (shift % 26));
}

// Шифрование файла
void encryptFileContent(const string& sourceFile, const string& destFile, int shift) {
    ifstream inputFile(sourceFile);
    ofstream outputFile(destFile);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Ошибка: Невозможно открыть файлы." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        outputFile << caesarEncrypt(line, shift) << endl;
    }

    inputFile.close();
    outputFile.close();
    cout << "Файл зашифрован успешно: " << destFile << endl;
}

// Дешифрование файла
void decryptFileContent(const string& sourceFile, const string& destFile, int shift) {
    ifstream inputFile(sourceFile);
    ofstream outputFile(destFile);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Ошибка: Невозможно открыть файлы." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        outputFile << caesarDecrypt(line, shift) << endl;
    }

    inputFile.close();
    outputFile.close();
    cout << "Файл дешифрован успешно: " << destFile << endl;
}

int main(int argc, char* argv[]) {
    // Проверка параметров
    if (argc < 4) {
        cerr << "Использование:\n";
        cerr << "  Для текста:   program text <encrypt/decrypt> <shift> <text>\n";
        cerr << "  Для файлов:  program file <encrypt/decrypt> <shift> <input_file> <output_file>\n";
        return 1;
    }

    string mode = argv[2];
    int shiftValue = stoi(argv[3]);

    if (string(argv[1]) == "text") {
        string textInput = argv[4];
        if (mode == "encrypt") {
            cout << "Зашифрованный текст: " << caesarEncrypt(textInput, shiftValue) << endl;
        } else if (mode == "decrypt") {
            cout << "Дешифрованный текст: " << caesarDecrypt(textInput, shiftValue) << endl;
        } else {
            cerr << "Неверный режим. Используйте encrypt или decrypt." << endl;
        }
    } else if (string(argv[1]) == "file") {
        if (argc < 6) {
            cerr << "Ошибка: Недостаточно параметров для файлового режима." << endl;
            return 1;
        }
        string inputPath = argv[4];
        string outputPath = argv[5];
        if (mode == "encrypt") {
            encryptFileContent(inputPath, outputPath, shiftValue);
        } else if (mode == "decrypt") {
            decryptFileContent(inputPath, outputPath, shiftValue);
        } else {
            cerr << "Неверный режим. Используйте encrypt или decrypt." << endl;
        }
    } else {
        cerr << "Неверный тип данных. Используйте text или file." << endl;
    }

    return 0;
}
