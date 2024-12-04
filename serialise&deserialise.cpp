#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Функция сериализации
string serialize(const vector<string> &data) {
    string serialized = "";
    for (const auto &str : data) {
        serialized += to_string(str.size()) + ":" + str;
    }
    return serialized;
}

// Функция десериализации
vector<string> deserialize(const string &data) {
    vector<string> deserialized;
    int i = 0;
    while (i < data.size()) {
        // Читаем длину текущей строки
        int delimiterPos = data.find(':', i);
        int length = stoi(data.substr(i, delimiterPos - i));
        i = delimiterPos + 1;

        // Извлекаем строку указанной длины
        deserialized.push_back(data.substr(i, length));
        i += length;
    }
    return deserialized;
}

int main() {
    // Ввод данных для сериализации
    vector<string> originalData = {"hello", "world", "this", "is", "serialization"};
    cout << "Original data:" << endl;
    for (const auto &str : originalData) {
        cout << str << " ";
    }
    cout << endl;

    // Сериализация
    string serializedData = serialize(originalData);
    cout << "\nSerialized data: " << serializedData << endl;

    // Десериализация
    vector<string> deserializedData = deserialize(serializedData);
    cout << "\nDeserialized data:" << endl;
    for (const auto &str : deserializedData) {
        cout << str << " ";
    }
    cout << endl;

    return 0;
}
