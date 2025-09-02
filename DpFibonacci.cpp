// ===================================================================
//                   DYNAMIC PROGRAMMING FIBONACCI
// ===================================================================
//
// This program benchmarks the performance of Fibonacci computation
// using a **bottom-up dynamic programming approach**.
//
// Key Notes:
// - Naive recursion grows exponentially (O(2^n)).
// - With DP, we store already-computed values, avoiding recomputation.
// - This reduces complexity to O(n), which is drastically faster.
// - We can now compute very large Fibonacci numbers (like n=5000)
//   in milliseconds instead of hours/years.
//
// ===================================================================

#include <bits/stdc++.h>
#include <fstream>   // For file I/O
using namespace std;
using namespace std::chrono;

// ===================================================================
//                    DYNAMIC PROGRAMMING FIBONACCI
// ===================================================================

/**
 * @brief Computes Fibonacci using bottom-up dynamic programming.
 *
 * @param n The input Fibonacci index.
 * @return long long The nth Fibonacci number (for benchmarking, only time matters).
 */
long long fibonacciDP(int n) {
    if (n <= 1) return n;

    vector<long long> fib(n + 1);
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

// ===================================================================
//                          MAIN FUNCTION
// ===================================================================

int main() {
    // Test input sizes (safe for DP, even large ones work fine)
    vector<int> test_sizes = {1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 100, 500, 1000, 5000};

    // Number of runs to average over
    int runs_per_n = 10;

    // Open CSV file in append mode
    ofstream csv("benchmark_results.csv", ios::app);
    if (!csv.is_open()) {
        cerr << "Error: Could not open CSV file!" << endl;
        return 1;
    }

    cout << "\n--- Dynamic Programming Fibonacci Benchmark ---" << endl;
    cout << "Averaged over " << runs_per_n << " runs per input size.\n" << endl;

    for (int n : test_sizes) {
        long long total_duration = 0;

        for (int i = 0; i < runs_per_n; i++) {
            auto start = high_resolution_clock::now();
            fibonacciDP(n);
            auto end = high_resolution_clock::now();

            total_duration += duration_cast<nanoseconds>(end - start).count();
        }

        long long avg_duration = total_duration / runs_per_n;

        cout << "n=" << n << " | Avg Time = " << avg_duration << " ns" << endl;

        csv << "DP Fibonacci," << n << "," << avg_duration << "\n";
    }

    csv.close();
    cout << "\nResults appended to benchmark_results.csv" << endl;

    return 0;
}
