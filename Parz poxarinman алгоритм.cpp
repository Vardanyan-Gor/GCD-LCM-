#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>

std::unordered_map<char, char> createSubstitutionMap() {
    std::unordered_map<char, char> substitutionMap;
    substitutionMap['A'] = 'Q';
    substitutionMap['B'] = 'W';
    substitutionMap['C'] = 'E';
    substitutionMap['D'] = 'R';
    substitutionMap['E'] = 'T';
    substitutionMap['F'] = 'Y';
    substitutionMap['G'] = 'U';
    substitutionMap['H'] = 'I';
    substitutionMap['I'] = 'O';
    substitutionMap['J'] = 'P';
    substitutionMap['K'] = 'A';
    substitutionMap['L'] = 'S';
    substitutionMap['M'] = 'D';
    substitutionMap['N'] = 'F';
    substitutionMap['O'] = 'G';
    substitutionMap['P'] = 'H';
    substitutionMap['Q'] = 'J';
    substitutionMap['R'] = 'K';
    substitutionMap['S'] = 'L';
    substitutionMap['T'] = 'Z';
    substitutionMap['U'] = 'X';
    substitutionMap['V'] = 'C';
    substitutionMap['W'] = 'V';
    substitutionMap['X'] = 'B';
    substitutionMap['Y'] = 'N';
    substitutionMap['Z'] = 'M';
    return substitutionMap;
}

std::string substitute(const std::string& text, const std::unordered_map<char, char>& substitutionMap) {
    std::string substitutedText;
    for (char c : text) {
        if (isalpha(c)) {
            char upperChar = toupper(c);
            substitutedText += substitutionMap.at(upperChar);
        }
        else {
            substitutedText += c; // Не заменяем неалфавитные символы
        }
    }
    return substitutedText;
}

int main() {
    setlocale(LC_ALL, "rus");

    auto substitutionMap = createSubstitutionMap();

    std::string text;
    std::cout << "Введите текст для шифрования: ";
    std::getline(std::cin, text);

    std::string substitutedText = substitute(text, substitutionMap);
    std::cout << "Зашифрованный текст: " << substitutedText << std::endl;

    return 0;
}