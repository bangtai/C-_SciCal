#ifndef __BASESOLVER_H
#define __BASESOLVER_H

#include <vector>
#include <cblas.h>
#include <lapacke.h>
#include <cmath>


namespace ams562 {

class BaseSolver {
public:
  BaseSolver(double xl, double xr, unsigned int nx)
      : xl_(xl), xr_(xr), N_(nx - 2) {
    h_ = (xr_ - xl_) / (N_ + 1);
    u_.resize(N_); // you should do the same thing in assemble
  }

  virtual ~BaseSolver() {}

  // pure abstract methods
  virtual void assemble() = 0;
  virtual void solve(const std::vector<double> &b) = 0;

  // implementation needed, assign lhs to lb_, rhs to rb_
  void assign_bcs(double lhs, double rhs){
      this -> lb_ = lhs;
      this -> rb_ = rhs;
  }

  // implemetation needed, return u_
  std::vector<double> &get_solution(){
      return this -> u_;
  }

protected:
  double xl_, xr_;
  double h_;
  unsigned int N_;
  double lb_, rb_;
  std::vector<double> u_;
  std::vector<double> A_;
};

} // namespace ams562

#endif
