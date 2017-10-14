clc; clear all;

% construct the the matrix in hint 1
A = [2. -1. 0.;-1. 2. -1.;0. -1. 2.];

fprintf('The SPD matrix is...\n');
disp(A);

% call cholesky
R = chol(A);

% print
fprintf('The Cholesky decomposition of the SPD system is...\n');
disp(R);