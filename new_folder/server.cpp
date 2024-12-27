#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

#define PORT 8080 // Port number for the server

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    address.sin_port = htons(PORT); // Use defined port

    // Bind socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    cout << "Waiting for connections on port " << PORT << "..." << endl;

    // Accept a client connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    cout << "Connection established with client." << endl;

    // Receive message from client
    int valread = read(new_socket, buffer, 1024);
    cout << "Received from client: " << buffer << endl;

    // Send a response back to the client
    const char *response = "Update received and processed!";
    send(new_socket, response, strlen(response), 0);
    cout << "Response sent to client." << endl;

    // Close the connection
    close(new_socket);
    close(server_fd);

    return 0;
}
