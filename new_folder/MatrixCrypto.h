#ifndef MATRIX_CRIPTO_H
#define MATRIX_CRIPTO_H

#include <string>
#include <vector>
#include <algorithm>

class MatrixCripto {
public:
    static std::string encrypt(const std::string& message, int key);
    static std::string decrypt(const std::string& message, int key);
};

#endif
