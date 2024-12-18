#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include "MatrixCripto.h"
#include "Huffman.h"

using namespace std;

#define PORT 8080 // Server port number

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    string testData = "hello world";
    cout << "Original Text: " << testData << endl;

    // Шифрование с помощью матричного шифрования
    string matEncrypted = MatrixCripto::encrypt(testData, 3);
    cout << "Matrix Encrypted: " << matEncrypted << endl;

    // Кодирование с помощью Хаффмана
    unordered_map<char, int> freqMap;
    for (char ch : matEncrypted) {
        freqMap[ch]++;
    }
    HuffmanNode* root = buildHuffmanTree(freqMap);
    unordered_map<char, string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);
    string huffmanEncoded = encode(matEncrypted, huffmanCodes);
    cout << "Huffman Encrypted: " << huffmanEncoded << endl;

    // Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Преобразование IP-адреса в бинарную форму
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address or Address not supported");
        exit(EXIT_FAILURE);
    }

    // Подключение к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Отправка зашифрованного сообщения (Huffman код)
    send(sock, huffmanEncoded.c_str(), huffmanEncoded.length(), 0);
    cout << "Encrypted message sent to server." << endl;

    // Получение ответа от сервера
    int valread = read(sock, buffer, 1024);
    cout << "Server response: " << buffer << endl;

    // Закрытие соединения
    close(sock);

    return 0;
}
