#include "src/_matrix_t.h"
#include "src/_chol.h"
#include <iostream>
#include <iomanip>
#include <string>

#ifdef ABS
#undef ABS
#endif
#define ABS(x) ((x>0.0)?x:-x)

// idea borrowed from Wenbin Lu
const std::string PASS = "\033[1;32m PASS\033[0m\n";
const std::string FAIL = "\033[1;31m FAIL\033[0m\n";


//
// YOU SHOULD NOT CHANGE ANYTHING IN THE TESTING
// PROGRAM, OTHERWISE THE TESTING MAY GO WRONG!
//

extern void generate_spd(const int, double **);
extern void recover(const int, double**, double **);

namespace Private {
    void _alloc(const int, ams562proj1::matrix_t &);
    void _dealloc(ams562proj1::matrix_t &);
    bool _testrecv(const int,
                   const ams562proj1::matrix_t &,
                   const ams562proj1::matrix_t &);
    bool _touchtest(const int, const ams562proj1::matrix_t &);
    bool _testtxt(const int,
                   const ams562proj1::matrix_t &,
                   const ams562proj1::matrix_t &);
    constexpr double tol = 1e-12;

    // test cases
    void test1();
    void test2();
    void test3();
    void test4();
}

// main function

int main() {
    using namespace Private;
    test1();
    test2();
    test3();
    test4();
    return 0;
}

void Private::_alloc(const int n, ams562proj1::matrix_t &A) {
    A.size = n;
    A.data = new double * [n];
    for (int i = 0; i < n; ++i) A.data[i] = new double [n];
}

void Private::_dealloc(ams562proj1::matrix_t &A) {
    for (int i = 0; i < A.size; ++i)
        delete [] A.data[i];
    delete [] A.data;
    A.size = 0;
}

bool Private::_testrecv(const int n,
            const ams562proj1::matrix_t &A,
            const ams562proj1::matrix_t &B) {
    for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j) {
                const double diff(A.data[i][j]-B.data[i][j]);
                if (ABS(diff) > tol)
                    return true;
            }
    return false;
}

bool Private::_touchtest(const int n, const ams562proj1::matrix_t &A) {
    for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j)
                if (ABS(A.data[i][j]) > tol)
                    return true;
    return false;
}

bool Private::_testtxt(const int n,
            const ams562proj1::matrix_t &A,
            const ams562proj1::matrix_t &B) {
    for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j) {
                const double diff(A.data[i][j]-B.data[i][j]);
                if (ABS(diff) > 0.01)
                    return true;
            }
    return false;
}

static void test(const int c, const int n) {
    using namespace std;
    string result = PASS;
    ams562proj1::matrix_t A, Atemp, LR;
    A.size = Atemp.size = LR.size = n;
    std::string filename = std::string("text")+std::to_string(c)+".txt";
    Private::_alloc(n, A);
    Private::_alloc(n, Atemp);
    Private::_alloc(n, LR);
    for (auto i = 0; i < n; ++i)
        for (auto j = 0; j < n; ++j)
            LR.data[i][j] = 0.0;
    cout << "****************************************\n"
        <<  "************* Test # " << c << " *****************\n"
        <<  "****************************************\n\n";
    cout << "\n\nGenerating an SPD system....\n";
    generate_spd(n, A.data);
    cout << "\nDone!, the matrix is:\n";
    cout << fixed << setprecision(3); // set fixed precision
    // using a lambda
    auto print_mat = [=](double **data) {
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < n; ++j)
                cout << left << setw(7) << data[i][j];
            cout << '\n';
        }
    };
    print_mat(A.data);
    cout << "\n\nCalling Cholesky factorization...\n";
    ams562proj1::chol(A, LR);
    cout << "\nDone!, the upper triangular part is:\n";
    print_mat(LR.data);
    if (Private::_touchtest(n, LR)) {
        cout << "\nYour algorithm modified the lower part...\n";
        result = FAIL;
        goto res;
    }
    cout << "\n\nRecovering the decomposition...\n";
    recover(n, Atemp.data, LR.data);
    cout << "\nDone! the recovered matrix is:\n";
    print_mat(Atemp.data);
    if (Private::_testrecv(n, A, Atemp)) {
        cout << "\nThe recoverred matrix does not"
            << " match with original one...\n";
        result = FAIL;
        goto res;
    }
    cout << "\n\nPerforming text file testing...\n";
    ams562proj1::write2txt(filename, A);
    for (auto i = 0; i < n; ++i)
        for (auto j = 0; j < n; ++j)
            Atemp.data[i][j] = 0.0;
    ams562proj1::readtxt(filename, Atemp);
    cout << "\nDone!\n";
    if (Private::_testtxt(n, A, Atemp)) {
        cout << "\nSomething went wrong while writing and reading data...\n";
        result = FAIL;
        goto res;
    }

res:
    cout << "\nThis test is finished with \n";
    cout << "Result: " << result << '\n';
    cout << defaultfloat; // reset cout to default

    Private::_dealloc(A);
    Private::_dealloc(Atemp);
    Private::_dealloc(LR);
}

void Private::test1() {test(1, 5);}
void Private::test2() {test(2, 4);}
void Private::test3() {test(3, 8);}
void Private::test4() {test(4, 6);}
