#include "_internal_routines.h"
#include "_chol.h"
#include <math.h>
#include <fstream>
#include <iostream>

namespace ams562proj1 {

////////////////////////////////////////////
// After calling this function
//          then A = tran(R)*R,
//          R stores the upper decomp
///////////////////////////////////////////
void chol(const matrix_t &A, matrix_t &R)
{
    // Implementations needed
    // hints:

    //  [1] copy half of A into R
    //  [2] based on the algorithm, you should have two for-loops
    //      (a) inner one requires a subroutine
    //      (b) outer one requires a subroutine
    for (int i = 0; i < A.size; i++) {

        ams562proj1::internal::copy(A.size-i, A.data[i]+i, R.data[i]+i);

    }

    for (int k = 0; k < A.size; k++) {
        for (int j = k + 1; j < A.size; j++) {
            double alpha = -1 * R.data[k][j] / R.data[k][k];
            ams562proj1::internal::axpy(A.size-j, alpha, R.data[k]+j, R.data[j]+j);
        }
        double beta = 1.0/sqrt(R.data[k][k]);
        ams562proj1::internal::scal(A.size-k, beta, R.data[k]+k);
    }


}

///////////////////////////////////////////
// After calling this function, there
// should be text file that contains
// the data of matrix A
// using write2txt1d
//////////////////////////////////////////
void write2txt(const std::string &filename, const matrix_t &A)
{
    // Implementations needed

    for (int i = 0; i < A.size; i++){
        ams562proj1::internal::write2txt1d(filename, A.size, A.data[i]);
    }

}

///////////////////////////////////////////
// After calling this function, A should
// contains the data from text file
// directly implement here
//////////////////////////////////////////
void readtxt(const std::string &filename, matrix_t &A)
{
    // Implementations needed
    std::ifstream infile(filename);

    if (infile.is_open()) {

        double buff;



        for (int i = 0; i < A.size; i++){
            for (int j = 0; j < A.size; j++){
                infile >> buff;
                A.data[i][j] = buff;

            }
        }
        infile.close();


    }
    else
        std::cerr << "Cannot open file" << '\n';


}

}
