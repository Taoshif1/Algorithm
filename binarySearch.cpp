// ===================================================================
//                 BINARY SEARCH BENCHMARK PROGRAM
// ===================================================================
//
// This program benchmarks the performance of Binary Search on arrays
// of different input sizes. Results are averaged over multiple runs
// for stability, and saved into a single CSV file that can contain
// multiple algorithms for easy comparison.
//
// Key Notes:
// - Binary Search requires the input array to be sorted.
// - Sorting time is deliberately excluded; we only measure searching.
// - The target is chosen as -1, which is guaranteed NOT to exist
//   in the generated array, ensuring worst-case performance.
// - Results are saved with an "Algorithm" column for plotting legends.
//
// ===================================================================

#include <bits/stdc++.h>
#include <fstream>   // For file I/O
using namespace std;
using namespace std::chrono;

// ===================================================================
//                       HELPER FUNCTIONS
// ===================================================================

/**
 * @brief Generates a vector of high-quality random integers.
 * @param size The number of integers to generate.
 * @return A vector<int> filled with random integers.
 */
vector<int> generateRandomVector(int size) {
    vector<int> vec(size);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100000);

    for (int i = 0; i < size; ++i)
        vec[i] = distrib(gen);

    return vec;
}

// ===================================================================
//                       BINARY SEARCH
// ===================================================================

/**
 * @brief Iterative Binary Search algorithm.
 * @param arr A sorted vector<int>.
 * @param target The value to find.
 * @return Index of target if found, else -1.
 */
int binarySearch(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// ===================================================================
//                          MAIN FUNCTION
// ===================================================================

int main() {
    vector<int> n_values = {1, 10, 100, 1000, 10000};
    int runs_per_n = 30;

    // Use a single CSV for all algorithms
    ofstream csv("benchmark_results.csv", ios::app); // append mode
    if (csv.tellp() == 0) csv << "Algorithm, InputSize, Time_ns\n"; // header if empty

    cout << "--- Binary Search Benchmark ---" << endl;
    cout << "Averaged over " << runs_per_n << " runs per input size.\n" << endl;

    for (int n : n_values) {
        long long total_duration = 0;

        for (int i = 0; i < runs_per_n; ++i) {
            vector<int> data = generateRandomVector(n);
            sort(data.begin(), data.end()); // must sort before searching
            int target = -1;

            auto start = high_resolution_clock::now();
            binarySearch(data, target);
            auto end = high_resolution_clock::now();

            total_duration += duration_cast<nanoseconds>(end - start).count();
        }

        long long avg_duration = total_duration / runs_per_n;

        cout << "n=" << n << " | Avg Time = " << avg_duration << " ns" << endl;

        // Save results with Algorithm name for legend
        csv << "BinarySearch," << n << "," << avg_duration << "\n";
    }

    csv.close();
    cout << "\nResults appended to benchmark_results.csv" << endl;

    return 0;
}
