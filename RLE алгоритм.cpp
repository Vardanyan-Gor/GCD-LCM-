#include <iostream>
#include <string>

std::string RLE(const std::string& input) {
    std::string output;
    int count = 1;

    for (size_t i = 1; i <= input.length(); ++i) {
        
        if (i < input.length() && input[i] == input[i - 1]) {
            count++;
        }
        else {
            
            output += std::to_string(count) + input[i - 1];
            count = 1; 
        }
    }
    return output;
}

int main() {
    setlocale(LC_ALL, "Rus");
    std::string input;
    std::cout << "Введите строку для сжатия: ";
    std::getline(std::cin, input);

    std::string compressed = RLE(input);
    std::cout << "Сжатая строка (RLE): " << compressed << std::endl;

    return 0;
}