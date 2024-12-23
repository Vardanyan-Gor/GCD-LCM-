#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class MatrixCripto {
public:
    static string encrypt(const string& message, int key) {
        vector<vector<char>> mat;
        string result = "";

        for (size_t i = 0; i < message.length(); i += key) {
            vector<char> row(message.begin() + i, message.begin() + min(i + key, message.length()));
            mat.push_back(row);
        }

        for (int i = 0; i < key; ++i) {
            for (size_t j = 0; j < mat.size(); ++j) {
                if (i < mat[j].size()) {
                    result += mat[j][i];
                }
                else {
                    result += ' ';
                }
            }
        }

        return result;
    }

    static string decrypt(const string& message, int key) {
        vector<vector<char>> mat;
        string result = "";
        int col = message.length() / key;

        for (size_t i = 0; i < message.length(); i += col) {
            vector<char> row(message.begin() + i, message.begin() + min(i + col, message.length()));
            mat.push_back(row);
        }

        for (int i = 0; i < col; ++i) {
            for (size_t j = 0; j < mat.size(); ++j) {
                if (i < mat[j].size()) {
                    result += mat[j][i];
                }
                else {
                    result += ' ';
                }
            }
        }

        return result;
    }
};

int main() {
    string testData = "mmmdddjjjj";
    cout << "Test data: " << testData << endl;

    cout << "\nMatrix Cripto:" << endl;
    string matEncrypted = MatrixCripto::encrypt(testData, 3);
    cout << "Encrypted text: " << matEncrypted << endl;
    cout << "Decrypted text: " << MatrixCripto::decrypt(matEncrypted, 3) << endl;

    return 0;
}
