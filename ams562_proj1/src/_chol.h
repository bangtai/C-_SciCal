#ifndef _CHOL_H
#define _CHOL_H

#include <string>
#include "_matrix_t.h"

// The end user Cholesky Factorization interface
// your implementation should not touch the lower part!

// also  text file interfaces

namespace ams562proj1 {
    // chol
    void chol(const matrix_t &A, matrix_t &R);

    // write
    void write2txt(const std::string &filename, const matrix_t &A);

    // read
    void readtxt(const std::string &filename, matrix_t &A);
}

#endif // _CHOL_H
