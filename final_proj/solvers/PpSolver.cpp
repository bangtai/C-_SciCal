#include "PpSolver.h"

// MAKE SURE YOU HAVE LAPACKE & CBLAS INCLUDED

namespace ams562 {

// assemble the packed UPPER part of A
// A = [2 -1 0 0]
//     [x 2 -1 0]
//     [x x 2 -1]
//     [x x x  2]
// where x means empty.
void PpSolver::assemble() {
    A_.resize((1 + N_) * N_ / 2);

    int N = N_;

    auto iter1 = A_.begin();
    for (int i = 0; i < N; i++){
        *iter1 = 2;
        iter1 = iter1 + N_ - i;
    }

    auto iter2 = A_.begin() + 1;
    for (int i = 0; i < N - 1; i++){
        *iter2 = -1;
        iter2 = iter2 + N_ - i;
    }
}

// call packed SPD solver, keep in mind
// boundary conditions
void PpSolver::solve(const std::vector<double> &b) {
    //std::vector<int> buffer(N_);

    double sigma = pow(h_, 2);
    cblas_dcopy(N_, b.data(), 1, u_.data(), 1);
    cblas_dscal(N_, sigma, u_.data(), 1);

    u_[0] += lb_;
    u_[N_ - 1] += rb_;

    LAPACKE_dppsv(LAPACK_ROW_MAJOR, 'U', N_, 1, A_.data(), u_.data(), 1);
}

} // namespace ams562
