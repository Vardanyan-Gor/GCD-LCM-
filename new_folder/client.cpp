#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

#define PORT 8080 // Server port number

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char *message = "This is an update message from client!";

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP address to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address or Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send message (update) to server
    send(sock, message, strlen(message), 0);
    cout << "Update sent to server." << endl;

    // Receive server's response
    int valread = read(sock, buffer, 1024);
    cout << "Server response: " << buffer << endl;

    // Close the connection
    close(sock);

    return 0;
}
