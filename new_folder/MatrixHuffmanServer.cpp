#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include "matrixencripting.h"
#include "Huffman.h"

using namespace std;

#define PORT 8080 // Server port number

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Создание сокета
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Принимаем соединения с любых IP
    address.sin_port = htons(PORT); // Используем указанный порт

    // Привязка сокета к порту
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Ожидание соединений
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    cout << "Waiting for connections on port " << PORT << "..." << endl;

    // Принятие соединения от клиента
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    cout << "Connection established with client." << endl;

    // Получение зашифрованного сообщения от клиента
    int valread = read(new_socket, buffer, 1024);
    string encryptedMessage = string(buffer);
    cout << "Received encrypted message: " << encryptedMessage << endl;

    // Декодирование с помощью Хаффмана
    unordered_map<char, int> freqMap;
    for (char ch : encryptedMessage) {
        freqMap[ch]++;
    }
    HuffmanNode* root = buildHuffmanTree(freqMap);
    unordered_map<char, string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);
    string huffmanDecoded = decode(root, encryptedMessage);
    cout << "Decoded with Huffman: " << huffmanDecoded << endl;

    // Дешифровка с помощью матричного шифрования
    string matDecrypted = MatrixCripto::decrypt(huffmanDecoded, 3);
    cout << "Matrix Decrypted: " << matDecrypted << endl;

    // Отправка ответа обратно клиенту
    const char *response = "Decryption complete. Message: ";
    send(new_socket, response, strlen(response), 0);
    send(new_socket, matDecrypted.c_str(), matDecrypted.length(), 0);
    cout << "Response sent to client." << endl;

    // Закрытие соединения
    close(new_socket);
    close(server_fd);

    return 0;
}

