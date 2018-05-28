//Bangtai Chen     SBU ID: 111789386     Email: bangtai.chen@stonybrook.edu

/*
    
    In main function, there are also some result export code shown in comments,
    which is the source of figures in the report. You can ignore these code.

*/
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double euroCallTri(double K, double T, double S, double sig, double r, double div, int N, int Nj, double dx){
    //precpompute constains
    double dt = T / N;
    double nu =  r - div - 0.5 * pow(sig, 2);
    double edx = exp(dx);
    double pu =  0.5 * dt * (pow(sig / dx, 2) + nu / dx);
    double pm =  1.0 - dt * pow(sig / dx, 2) - r * dt;
    double pd =  0.5 * dt * (pow(sig / dx, 2) - nu / dx);

    //initalize the asset prive at maturity
    double St[2 * Nj + 1] = {};
    St[0] = S * exp(-Nj * dx);
    for(int j = 1; j < 2 * Nj + 1; j++){
        St[j] = St[j - 1] * edx;
    }

    //initalize option values at maturity
    double C[2 * N + 1][2 * Nj + 1] = {0};
    for(int j = 0; j < 2 * Nj + 1; j++){
        C[2 * N][j] = max(0.0, St[j] - K);
    }
    

    //step back through lattice
    for(int i = 2 * N - 1; i > N - 1 ; i--){
        for(int j = 1; j < 2 * Nj ; j++){
            C[i][j] =  (pu * C[i + 1][j + 1] + pm * C[i + 1][j] + pd * C[i + 1][j - 1]);
        }
        //boundary conditions
        C[i][0] = C[i][1];
        C[i][2 * Nj] = C[i][2 * Nj - 1] + (St[2 * Nj] - St[2 * Nj - 1]);
    }

    return C[N][Nj];
}

double euroPutTri(double K, double T, double S, double sig, double r, double div, int N, int Nj, double dx){
    //precpompute constains
    double dt = T / N;
    double nu =  r - div - 0.5 * pow(sig, 2);
    double edx = exp(dx);
    double pu =  0.5 * dt * (pow(sig / dx, 2) + nu / dx);
    double pm =  1.0 - dt * pow(sig / dx, 2) - r * dt;
    double pd =  0.5 * dt * (pow(sig / dx, 2) - nu / dx);

    //initalize the asset prive at maturity
    double St[2 * Nj + 1] = {};
    St[0] = S * exp(-Nj * dx);
    for(int j = 1; j < 2 * Nj + 1; j++){
        St[j] = St[j - 1] * edx;
    }

    //initalize option values at maturity
    double C[2 * N + 1][2 * Nj + 1] = {0};
    for(int j = 0; j < 2 * Nj + 1; j++){
        C[2 * N][j] = max(0.0, K - St[j]);
    }

    //step back through lattice
    for(int i = 2 * N - 1; i > N - 1 ; i--){
        for(int j = 1; j < 2 * Nj ; j++){
            C[i][j] =  (pu * C[i + 1][j + 1] + pm * C[i + 1][j] + pd * C[i + 1][j - 1]);
        }
        //boundary conditions
        C[i][0] = C[i][1] + (St[1] - St[0]);
        C[i][2 * Nj] = C[i][2 * Nj - 1];
    }


    return C[N][Nj];
}

double amCallTri(double K, double T, double S, double sig, double r,  double div, int N, int Nj, double dx){
    //precpompute constains
    double dt = T / N;
    double nu =  r - div - 0.5 * pow(sig, 2);
    double edx = exp(dx);
    double pu =  0.5 * dt * (pow(sig / dx, 2) + nu / dx);
    double pm =  1.0 - dt * pow(sig / dx, 2) - r * dt;
    double pd =  0.5 * dt * (pow(sig / dx, 2) - nu / dx);

    //initalize the asset prices at maturity
    double St[2 * Nj + 1] = {};
    St[0] = S * exp(-Nj * dx);
    for(int j = 1; j < 2 * Nj + 1; j++){
        St[j] = St[j - 1] * edx;
    }

    //initalize option values at maturity
    double C[2 * N + 1][2 * Nj + 1] = {0};
    for(int j = 0; j < 2 * Nj + 1; j++){
        C[2 * N][j] = max(0.0, St[j] - K);
    }

    //step back through lattice
    for(int i = 2 * N - 1; i > N - 1; i--){

        for(int j = 1; j < 2 * Nj ; j++){
            C[i][j] =  (pu * C[i + 1][j + 1] + pm * C[i + 1][j] + pd * C[i + 1][j - 1]);
        }

        //boundary conditions
        C[i][0] = C[i][1];
        C[i][2 * Nj] = C[i][2 * Nj - 1] + (St[2 * Nj] - St[2 * Nj - 1]);

        //apply early exercise condition
        for(int j = 0; j < 2 * Nj + 1; j++){
            C[i][j] = max(C[i][j], St[j] - K);
        }

    }

    return C[N][Nj];
}

double amPutTri(double K, double T, double S, double sig, double r,  double div, int N, int Nj, double dx){
    //precpompute constains
    double dt = T / N;
    double nu =  r - div - 0.5 * pow(sig, 2);
    double edx = exp(dx);
    double pu =  0.5 * dt * (pow(sig / dx, 2) + nu / dx);
    double pm =  1.0 - dt * pow(sig / dx, 2) - r * dt;
    double pd =  0.5 * dt * (pow(sig / dx, 2) - nu / dx);

    //initalize the asset prices at maturity
    double St[2 * Nj + 1] = {};
    St[0] = S * exp(-Nj * dx);
    for(int j = 1; j < 2 * Nj + 1; j++){
        St[j] = St[j - 1] * edx;
    }

    //initalize option values at maturity
    double C[2 * N + 1][2 * Nj + 1] = {0};
    for(int j = 0; j < 2 * Nj + 1; j++){
        C[2 * N][j] = max(0.0, K - St[j]);
    }

    //step back through lattice
    for(int i = 2 * N - 1; i > N - 1; i--){

        for(int j = 1; j < 2 * Nj ; j++){
            C[i][j] =  (pu * C[i + 1][j + 1] + pm * C[i + 1][j] + pd * C[i + 1][j - 1]);
        }

        //boundary conditions
        C[i][0] = C[i][1] + (St[1] - St[0]) ;
        C[i][2 * Nj] = C[i][2 * Nj - 1];

        //apply early exercise condition
        for(int j = 0; j < 2 * Nj + 1; j++){
            C[i][j] = max(C[i][j], K - St[j]);
        }

    }

    return C[N][Nj];
}


int main(int argc, char* argv[])
{

    double euroCall = euroCallTri(2500.0, 0.25, 2644.0, 0.2, 0.06, 0.03, 500, 500, 0.2);
    double euroPut = euroPutTri(100.0, 1.0, 100.0, 0.2, 0.06, 0.03, 500, 500, 0.2);
    double amCall = amCallTri(100.0, 1.0, 100.0, 0.2, 0.06, 0.03, 500, 500, 0.2);
    double amPut = amPutTri(100.0, 1.0, 100.0, 0.2, 0.06, 0.03, 500, 500, 0.2);
    cout << euroCall << "\n";
    cout << euroPut << "\n";
    cout << amCall << "\n";
    cout << amPut << "\n";

    return 0;
}
