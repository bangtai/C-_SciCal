#include "LuSolver.h"

// MAKE SURE YOU HAVE LAPACKE & CBLAS INCLUDED

namespace ams562 {

// assemble a whole dense matrix of N_ by N_
void LuSolver::assemble() {
    int N = 0;
    N = this -> N_;
    this -> A_.reserve(N * N);

    //for(int i = 0; i < this -> N_ * this -> N_; i++){

    this -> A_.resize(N_ * N_);


    auto iter1 = A_.begin();
    for (int i = 0; i < N; i++){
        *iter1 = 2;
        iter1 = iter1 + N + 1;
    }

    auto iter2 = A_.begin() + 1;
    for (int i = 0; i < N - 1; i++){
        *iter2 = -1;
        iter2 = iter2 + N + 1;
    }

    auto iter3 = A_.begin() + N;
    for (int i = 0; i < N - 1; i++){
        *iter3 = -1;
        iter3 = iter3 + N + 1;
    }


}

// given a right-hand side vector b, solve the problem
// remember to apply the boundary conditions, i.e. add
// lb_ (or lb_/h^2 depending on implementation) to b[0]
// rb_ (or rb_/h^2) to b[N_-1]
// then call lapack solver to solve the system
// you can create a vector<int> as buffer for pivotings
void LuSolver::solve(const std::vector<double> &b) {
    std::vector<int> buffer(N_);

    double sigma = pow(h_, 2);
    cblas_dcopy(N_, b.data(), 1, u_.data(), 1);
    cblas_dscal(N_, sigma, u_.data(), 1);

    u_[0] += lb_;
    u_[N_ - 1] += rb_;

    LAPACKE_dgesv(LAPACK_ROW_MAJOR, N_, 1, A_.data(), N_, buffer.data(), u_.data(), 1);
    // for (int i = 0; i < N_; ++i)
    //     u_[i] = sigma*b[i];


}

} // namespace ams562
