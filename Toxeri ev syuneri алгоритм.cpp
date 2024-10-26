#include <iostream>
#include <vector>
#include <string>

std::string encryptWithTable(const std::string& text, int columns) {
   
    int rows = (text.length() + columns - 1) / columns;

   
    std::vector<std::vector<char>> table(rows, std::vector<char>(columns, ' '));
    int k = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (k < text.length()) {
                table[i][j] = text[k++];
            }
        }
    }

   
    std::string encryptedText;
    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i < rows; ++i) {
            if (table[i][j] != ' ') {
                encryptedText += table[i][j];
            }
        }
        encryptedText += ' '; 
    }

    return encryptedText;
}

int main() {
    setlocale(LC_ALL, "rus");

    std::string text;
    std::cout << "Введите текст: ";
    std::getline(std::cin, text); 

    int columns = 3;

    std::string encryptedText = encryptWithTable(text, columns);
    std::cout << "Зашифрованный текст: " << encryptedText << std::endl;

    return 0;
}