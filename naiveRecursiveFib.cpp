// ===================================================================
//                NAIVE RECURSIVE FIBONACCI BENCHMARK PROGRAM
// ===================================================================
//
// This program benchmarks the performance of the **naive recursive**
// Fibonacci implementation on various input sizes.
//
// Notes:
// - The recursive version has exponential time complexity O(2^n).
// - It recalculates the same values again and again, wasting time.
// - This makes it infeasible for large n (like 1000).
// - Safe test set: {1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50}.
// - Do NOT attempt very large n — it will freeze your PC!
//
// ===================================================================

#include <bits/stdc++.h>
#include <fstream>   // For CSV output
using namespace std;
using namespace std::chrono;

// ===================================================================
//                NAIVE RECURSIVE FIBONACCI
// ===================================================================

/**
 * @brief Naive recursive Fibonacci implementation.
 *
 * @param n The Fibonacci index.
 * @return The nth Fibonacci number.
 *
 * Time Complexity: O(2^n)
 * Space Complexity: O(n) due to recursion depth.
 */
long long fibRecursive(int n) {
    if (n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// ===================================================================
//                          MAIN FUNCTION
// ===================================================================

int main() {
    // Test set chosen carefully (don’t go too high!)
    vector<int> test_n = {1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

    // Open CSV file for appending results
    ofstream csv("benchmark_results.csv", ios::app);

    // Write a header section for clarity
    csv << "\nAlgorithm,InputSize,Time_ns\n";

    cout << "--- Recursive Fibonacci Benchmark ---" << endl;
    cout << "(Exponential runtime, safe up to n=50)\n" << endl;

    // Run benchmark for each n
    for (int n : test_n) {
        auto start = high_resolution_clock::now();
        fibRecursive(n);  // Compute nth Fibonacci number
        auto end = high_resolution_clock::now();

        long long duration = duration_cast<nanoseconds>(end - start).count();

        // Print to console
        cout << "n=" << n << " | Time = " << duration << " ns" << endl;

        // Save to CSV
        csv << "RecursiveFibonacci," << n << "," << duration << "\n";
    }

    csv.close();
    cout << "\nResults appended to benchmark_results.csv" << endl;

    return 0;
}
