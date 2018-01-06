#include "TriSolver.h"

// MAKE SURE YOU HAVE LAPACKE & CBLAS INCLUDED

namespace ams562 {

// A_ = [2 2 2 ... 2 -1 -1 ... -1]
// where N_ 2's and N_-1 -1's
void TriSolver::assemble() {
    A_.reserve(N_ * 2 - 1);
    int N = N_;

    for (int i = 0; i < N; i++){
        A_.push_back(2);
    }

    for (int i = 0; i < N; i++){
        A_.push_back(-1);
    }
}

// call tridiagonal solver for SPD
// keep in mind boundary conditions
void TriSolver::solve(const std::vector<double> &b) {

    double sigma = pow(h_, 2);
    cblas_dcopy(N_, b.data(), 1, u_.data(), 1);
    cblas_dscal(N_, sigma, u_.data(), 1);

    u_[0] += lb_;
    u_[N_ - 1] += rb_;

    LAPACKE_dptsv(LAPACK_ROW_MAJOR, N_, 1, A_.data(), A_.data() + N_, u_.data(), 1);
}

} // namespace ams562
