#include <iostream>
#include <string>

std::string caesarCipher(const std::string& text, int shift) {
    std::string result;

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            
            c = (c - base + shift) % 26 + base;
        }
        result += c; 
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "rus");

    std::string text;
    int shift;

    std::cout << "Введите текст для шифрования: ";
    std::getline(std::cin, text);
    std::cout << "Введите сдвиг (число): ";
    std::cin >> shift;

    std::string encryptedText = caesarCipher(text, shift);
    std::cout << "Зашифрованный текст: " << encryptedText << std::endl;

    return 0;
}
