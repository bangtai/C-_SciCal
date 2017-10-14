#ifndef _INTERNAL_ROUTINES_H
#define _INTERNAL_ROUTINES_H

/////////////////////////////////////////////
// you need to implement 4 kernels here
//   [1] AXPY, i.e.
//          y=a*x+y
//   [2] SCAL, i.e.
//          y=a*x
//   [3] COPY, i.e.
//          y=x
//
// Where x, y are row vectors, and a is scalar
//
////////////////////////////////////////////
//
// In addtion, you need to implement three
// utility functions
//  [1] ASSERT
//          if !cond, then print msg, abort
//  [2] WRITE2TXT1D
//          write a 1-d array to text files
/////////////////////////////////////////////

#include <string>

namespace ams562proj1 { namespace internal {
    // axpy
    void axpy(const int n, const double alpha, const double *x, double *y);

    // scal
    void scal(const int n, const double alpha, double *y);

    // copy
    void copy(const int n, const double *x, double *y);

    // myassert
    void myassert(bool cond, const std::string &msg);

    // write2txt1d
    void write2txt1d(const std::string &filename, const int n, const double *x);
}}

#endif // _INTERNAL_ROUTINES_H
