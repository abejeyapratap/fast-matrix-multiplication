#include <chrono>
#include <iostream>
#include <string>
#include <thread>

void outputMatrix(int **m, const int n);
void initializeMatrix(int **m, const int n, bool isRand);
void cleanUpMatrix(int **m, const int n);
void threadedMult(const int N, int **m1, int **m2, int **res);
void multMatrixThreaded(const int n, int rStart, int rStop, int **m1, int **m2, int **res);
void multMatrixBasic(const int n, int **m1, int **m2, int **res);

const int MAX_THREADS = 30;

// n - size of square matrix
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./bin/mult n\n";
        return 1;
    }

    const int N = std::stoi(argv[1]);
    if (N < 2) {
        std::cout << "Square matrix size should at least 2\n";
        return 1;
    }

    std::srand(42); // to reproduce results
    int **m1 = new int *[N];
    int **m2 = new int *[N];
    int **res1 = new int *[N];
    int **res2 = new int *[N];
    initializeMatrix(m1, N, true);
    initializeMatrix(m2, N, true);
    initializeMatrix(res1, N, false);
    initializeMatrix(res2, N, false);

    // outputMatrix(m1, N);

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

    begin = std::chrono::steady_clock::now();
    threadedMult(N, m1, m2, res1);
    end = std::chrono::steady_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;

    begin = std::chrono::steady_clock::now();
    multMatrixBasic(N, m1, m2, res2);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
    
    // outputMatrix(res1, N);
    // outputMatrix(res2, N);

    cleanUpMatrix(m1, N);
    cleanUpMatrix(m2, N);
    cleanUpMatrix(res1, N);
    cleanUpMatrix(res2, N);
    delete[] m1;
    delete[] m2;
    delete[] res1;
    delete[] res2;

    return 0;
}

void multMatrixBasic(const int n, int **m1, int **m2, int **res) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            res[row][col] = 0;
            for (int k = 0; k < n; k++) {
                res[row][col] += m1[row][k] * m2[k][col];
            }
        }
    }
}

void threadedMult(const int N, int **m1, int **m2, int **res) {
    if (N <= MAX_THREADS) {
        std::thread myThreads[N];
        for (int i = 0; i < N; i++) {
            myThreads[i] = std::thread(multMatrixThreaded, N, i, i + 1, m1, m2, res);
        }

        for (int i = 0; i < N; i++) {
            myThreads[i].join();
        }
    } else {
        std::thread myThreads[MAX_THREADS];
        int step = N / MAX_THREADS;
        int numExtra = N % MAX_THREADS;
        int stop = step + numExtra; // 1st thread gets extra work
        int start = 0;

        for (int i = 0; i < MAX_THREADS; i++) {
            myThreads[i] = std::thread(multMatrixThreaded, N, start, stop, m1, m2, res);
            start = stop;
            stop += step;
        }

        for (int i = 0; i < MAX_THREADS; i++) {
            myThreads[i].join();
        }
    }
}

void multMatrixThreaded(const int n, int rStart, int rStop, int **m1, int **m2, int **res) {
    for (int row = rStart; row < rStop; row++) {
        for (int col = 0; col < n; col++) {
            res[row][col] = 0;
            for (int k = 0; k < n; k++) {
                res[row][col] += m1[row][k] * m2[k][col];
            }
        }
    }
}

void outputMatrix(int **m, const int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// initialize matrix to all 0s or random numbers
void initializeMatrix(int **m, const int n, bool isRand) {
    if (isRand) {
        for (int i = 0; i < n; i++) {
            m[i] = new int[n];
            for (int j = 0; j < n; j++) {
                m[i][j] = std::rand() % 10;  // number between 0 and 9
                // m[i][j] = 2;
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            m[i] = new int[n];
            for (int j = 0; j < n; j++) {
                m[i][j] = 0;
            }
        }
    }
}

void cleanUpMatrix(int **m, const int n) {
    for (int i = 0; i < n; i++) {
        delete[] m[i];
    }
}