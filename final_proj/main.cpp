#include <iostream>
#include "poisson1d.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <cmath>

int main(int argc, char* argv[])
{

    //f(x) = 2.0 * x ^2
    ams562::LuSolver solver1(0.0, 1.0, 202);
    double h1 = (1.0 - 0.0)  / (202.0 - 1.0);
    double lb1 = 0.0;
    double rb1 = 2.0 * pow(1.0, 2) ;
    solver1.assign_bcs(lb1, rb1); //you should have lb, rb evaluated
    solver1.assemble();

    std::vector<double> b1(200, -4.0);


    solver1.solve(b1); //you should compute b before call this function
    auto sol1 = solver1.get_solution();
    // Now doing the post-processing, i.e. analyze errors

    std::vector<double> res1(200);
    for (int i = 0; i < 200; i++){
        res1[i] = sol1[i] - pow((i+1) * h1,2) * 2; //get the error vector
    }

    double twoNormErr1 = cblas_dnrm2(200, res1.data(), 1);
    double infNormErr1 = cblas_idamax(200, res1.data(), 1); //get (index + 1) of max values

    std::cout << "The 2 norm error of first equation by LuSolver is " << '\n';
    std::cout << twoNormErr1 << "\n";
    std::cout << "The inf norm error of first equation by LuSolver is " << '\n';
    std::cout << std::abs(res1[infNormErr1 - 1]) << "\n";

    //TriSolver
    ams562::TriSolver solver12(0.0, 1.0, 202);

    solver12.assign_bcs(lb1, rb1); //you should have lb, rb evaluated
    solver12.assemble();

    solver12.solve(b1); //you should compute b before call this function
    auto sol12 = solver12.get_solution();
    // Now doing the post-processing, i.e. analyze errors

    std::vector<double> res12(200);
    for (int i = 0; i < 200; i++){
        res12[i] = sol12[i] - pow((i+1) * h1, 2) * 2; //get the error vector
    }

    double twoNormErr12 = cblas_dnrm2(200, res12.data(), 1);
    double infNormErr12 = cblas_idamax(200, res12.data(), 1); //get the (index + 1) of max value

    std::cout << "The 2 norm error of first equation by TriSolver is " << '\n';
    std::cout << twoNormErr12 << "\n";
    std::cout << "The inf norm error of first equation by TriSolver is " << '\n';
    std::cout << std::abs(res12[infNormErr12 - 1]) << "\n";

    //PpSolver
    ams562::TriSolver solver13(0.0, 1.0, 202);

    solver13.assign_bcs(lb1, rb1); //you should have lb, rb evaluated
    solver13.assemble();

    solver13.solve(b1); //you should compute b before call this function
    auto sol13 = solver13.get_solution();
    // Now doing the post-processing, i.e. analyze errors

    std::vector<double> res13(200);
    for (int i = 0; i < 200; i++){
        res13[i] = sol13[i] - pow((i+1) * h1, 2) * 2; //get the error vector
    }

    double twoNormErr13 = cblas_dnrm2(200, res13.data(), 1);
    double infNormErr13 = cblas_idamax(200, res13.data(), 1); //get the (index + 1) of max value

    std::cout << "The 2 norm error of first equation by PpSolver is " << '\n';
    std::cout << twoNormErr13 << "\n";
    std::cout << "The inf norm error of first equation by PpSolver is " << '\n';
    std::cout << std::abs(res13[infNormErr13 - 1]) << "\n";

    //u(x) = sin(Pi / 2.0 * x)
    //LuSolver
    ams562::LuSolver solver2(0.0, 1.0, 202);
    double h2 = (1.0 - 0.0) / (202.0 - 1.0);
    double lb2 = 0.0;
    double rb2 = 1.0 ;
    solver2.assign_bcs(lb2, rb2); //you should have lb, rb evaluated
    solver2.assemble();

    std::vector<double> b2(200);
    for (int i  = 0; i < 200; i++){
        double bi = std::sin(M_PI * 0.5 * (i + 1) * h2) * pow(M_PI, 2) / 4.0;
        b2[i] = bi;
    }

    solver2.solve(b2); //you should compute b before call this function
    auto sol2 = solver2.get_solution();

    std::vector<double> res2(200);
    for (int i = 0; i < 200; i++){
        res2[i] = sol2[i] - std::sin((i + 1) * h2 * M_PI / 2.0);
    }

    double twoNormErr2 = cblas_dnrm2(200, res2.data(), 1);
    double infNormErr2 = cblas_idamax(200, res2.data(), 1);

    std::cout << "The 2 norm error of second equation by LuSolver is " << '\n';
    std::cout << twoNormErr2 << "\n";
    std::cout << "The inf norm error of second equation by LuSolver is " << '\n';
    std::cout << std::abs(res2[infNormErr2 - 1])  << "\n";

    //PpSolver
    ams562::PpSolver solver22(0.0, 1.0, 202);
    solver22.assign_bcs(lb2, rb2); //you should have lb, rb evaluated
    solver22.assemble();

    solver22.solve(b2); //you should compute b before call this function
    auto sol22 = solver22.get_solution();

    std::vector<double> res22(200);
    for (int i = 0; i < 200; i++){
        res22[i] = sol22[i] - std::sin((i + 1) * h2 * M_PI / 2.0);
    }

    double twoNormErr22 = cblas_dnrm2(200, res22.data(), 1);
    double infNormErr22 = cblas_idamax(200, res22.data(), 1);

    std::cout << "The 2 norm error of second equation by PpSolver is " << '\n';
    std::cout << twoNormErr22 << "\n";
    std::cout << "The inf norm error of second equation by PpSolver is " << '\n';
    std::cout << std::abs(res22[infNormErr22 - 1])  << "\n";

    //TriSolver
    ams562::TriSolver solver23(0.0, 1.0, 202);
    solver23.assign_bcs(lb2, rb2); //you should have lb, rb evaluated
    solver23.assemble();

    solver23.solve(b2); //you should compute b before call this function
    auto sol23 = solver23.get_solution();

    std::vector<double> res23(200);
    for (int i = 0; i < 200; i++){
        res23[i] = sol23[i] - std::sin((i + 1) * h2 * M_PI / 2.0);
    }

    double twoNormErr23 = cblas_dnrm2(200, res23.data(), 1);
    double infNormErr23 = cblas_idamax(200, res23.data(), 1);

    std::cout << "The 2 norm error of second equation by TriSolver is " << '\n';
    std::cout << twoNormErr23 << "\n";
    std::cout << "The inf norm error of second equation by TriSolver is " << '\n';
    std::cout << std::abs(res23[infNormErr23 - 1])  << "\n";

    return 0;
}
