#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : character(c), frequency(f), left(nullptr), right(nullptr) {}
};

// Comparator for the priority queue
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

class Huffman {
public:
    static unordered_map<char, string> buildHuffmanTree(const string& text) {
        unordered_map<char, int> frequencies;
        for (char c : text) {
            frequencies[c]++;
        }

        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
        for (auto& pair : frequencies) {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            HuffmanNode* left = pq.top(); pq.pop();
            HuffmanNode* right = pq.top(); pq.pop();

            HuffmanNode* merged = new HuffmanNode('\0', left->frequency + right->frequency);
            merged->left = left;
            merged->right = right;
            pq.push(merged);
        }

        unordered_map<char, string> huffmanCodes;
        generateCodes(pq.top(), "", huffmanCodes);

        return huffmanCodes;
    }

    static string encrypt(const string& text, const unordered_map<char, string>& huffmanCodes) {
        string encodedText = "";
        for (char c : text) {
            encodedText += huffmanCodes.at(c);
        }
        return encodedText;
    }

    static string decrypt(const string& encodedText, HuffmanNode* root) {
        string decodedText = "";
        HuffmanNode* current = root;

        for (char bit : encodedText) {
            if (bit == '0') {
                current = current->left;
            } else {
                current = current->right;
            }

            if (current->left == nullptr && current->right == nullptr) {
                decodedText += current->character;
                current = root;
            }
        }

        return decodedText;
    }

private:
    static void generateCodes(HuffmanNode* node, const string& code, unordered_map<char, string>& huffmanCodes) {
        if (node == nullptr) return;

        if (node->left == nullptr && node->right == nullptr) {
            huffmanCodes[node->character] = code;
        }

        generateCodes(node->left, code + "0", huffmanCodes);
        generateCodes(node->right, code + "1", huffmanCodes);
    }
};

int main() {
    string text;
    cout << "Enter text to encode: ";
    getline(cin, text);

    unordered_map<char, string> huffmanCodes = Huffman::buildHuffmanTree(text);

    cout << "\nHuffman Codes:\n";
    for (auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    string encodedText = Huffman::encrypt(text, huffmanCodes);
    cout << "\nEncoded Text: " << encodedText << "\n";

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto& pair : huffmanCodes) {
        pq.push(new HuffmanNode(pair.first, text.length()));
    }
    HuffmanNode* root = pq.top();

    string decodedText = Huffman::decrypt(encodedText, root);
    cout << "Decoded Text: " << decodedText << "\n";

    return 0;
}
