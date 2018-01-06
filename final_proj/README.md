## Solutions for Poisson Equations

In this porject, we need to solve two Poisson Equations:

-u'' = f(x), a < x < b.

The first one is solving the model problem u(x) = 2*x^2 in (0; 1), with number of grid points 202.

The second one is solving the model problem u(x) = sin(Pi / 2 * x) in (0; 1), with number of grid points 202.

In the implementation, we simplify these problems to solving linear quations.

And we use 3 methods, LAPACKE_dgesv, LAPACKE_dppsv and LAPACKE_dptsv in LuSolver, Ppsolver and TriSolver, to solve each questions.

#### Inside the ```final_proj```

-   ```make``` to build
-   ```make test``` to run test, the terminal will show the 2 norm error and inf norm error of these two equations by 3 methods.
-   ```make clean``` to clean the executable file.
