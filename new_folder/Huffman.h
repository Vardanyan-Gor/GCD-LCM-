#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include <queue>

class Huffman {
public:
    struct Node {
        char ch;
        int freq;
        Node* left;
        Node* right;
        
        Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    };

    struct Compare {
        bool operator()(Node* left, Node* right) {
            return left->freq > right->freq;
        }
    };

    static std::string encode(const std::string& input);
    static std::string decode(const std::string& encoded, Node* root);
    static void generateCodes(Node* node, const std::string& code, std::unordered_map<char, std::string>& codes);
};

#endif // HUFFMAN_H
