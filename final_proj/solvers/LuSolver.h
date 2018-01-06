#ifndef __LUSOLVER_H
#define __LUSOLVER_H

#include "BaseSolver.h"

namespace ams562 {

class LuSolver : public BaseSolver {
public:
  LuSolver(double xl, double xr, unsigned int nx) : BaseSolver(xl, xr, nx) {}

  virtual void assemble() override;
  virtual void solve(const std::vector<double> &b) override;
};

} // namespace ams562

#endif
