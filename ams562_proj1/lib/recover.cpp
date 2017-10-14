void recover(const int n, double **Atemp, double **LR) {
    // inefficent implementation for correctness
    // LR == R
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j)
                LR[i][j] = 0.0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                double temp = 0;
                for (int k = 0; k < n; ++k)
                    temp += LR[k][i]*LR[k][j]; // haha
                Atemp[i][j] = temp;
            }
}
