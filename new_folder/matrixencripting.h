#ifndef COLUMNAR_CIPHER_H
#define COLUMNAR_CIPHER_H

#include <string>
#include <vector>

class ColumnarCipher {
public:
    static std::string encrypt(const std::string& message, int key);
    static std::string decrypt(const std::string& message, int key);
};

#endif
