#include "_internal_routines.h"
#include <iostream>
#include <string>
#include <fstream>

namespace ams562proj1 { namespace internal {

////////////////////////////////////////////////
// After calling this routine, y = alpha * x + y
////////////////////////////////////////////////
void axpy(const int n, const double alpha, const double *x, double *y)
{
    // Implementations needed
    for (int i = 0; i < n; i++){
        *y = (*x) * alpha + (*y);
        y++;
        x++;
    }

}

////////////////////////////////////////////////
// After calling this routine, y = alpha * y
////////////////////////////////////////////////
void scal(const int n, const double alpha, double *y)
{
    // Implementations needed
    for (int i = 0; i < n; i++){
        *y = (*y) * alpha;
        y++;
    }

}

////////////////////////////////////////////////
// After calling this routine, y = x
////////////////////////////////////////////////
void copy(const int n, const double *x, double *y)
{
    // Implementations needed
    for (int i = 0; i < n; i++){
        *y = *x;
        y++;
        x++;
    }

}

////////////////////////////////////////////////
// After calling this routine
//      if cond == false,
//          then, we print msg
//          abort program
////////////////////////////////////////////////
void myassert(bool cond, const std::string &msg)
{
    // Implementations needed
    if (cond == false){
        std::cout << msg << '\n';
        exit(1);
    }
}

///////////////////////////////////////////////
// After calling this routine
//      write the data in x into filename
//////////////////////////////////////////////
void write2txt1d(const std::string &filename, const int n, const double *x)
{
    // Implementations needed
    std::ofstream outfile(filename, std::ios::app) ;
    for(int i = 0; i < n; i++){
        outfile << *x << " ";
        x++;
    }
    outfile.close();
}

}
}
