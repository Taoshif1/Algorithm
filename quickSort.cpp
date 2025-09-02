// ===================================================================
//                 QUICK SORT BENCHMARK PROGRAM
// ===================================================================
//
// This program benchmarks the performance of Quick Sort on arrays
// of different input sizes. Results are averaged over multiple runs
// for stability, and saved into a CSV file.
//
// Key Notes:
// - Quick Sort is a divide-and-conquer sorting algorithm.
// - We measure only the sorting time itself.
// - The input arrays are filled with random integers.
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
 *
 * @param size The number of integers to generate.
 * @return A vector<int> filled with random integers.
 */
vector<int> generateRandomVector(int size) {
    vector<int> vec(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100000);
    for (int i = 0; i < size; ++i) {
        vec[i] = distrib(gen);
    }
    return vec;
}

// ===================================================================
//                        QUICK SORT ALGORITHM
// ===================================================================

/**
 * @brief Partition helper function for Quick Sort
 * @param arr Reference to the vector to sort
 * @param low Starting index
 * @param high Ending index
 * @return The partition index
 */
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // choose last element as pivot
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

/**
 * @brief Recursive Quick Sort function
 * @param arr Reference to the vector to sort
 * @param low Starting index
 * @param high Ending index
 */
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ===================================================================
//                          MAIN FUNCTION
// ===================================================================

int main() {
    // Input sizes to test
    vector<int> n_values = {1, 10, 100, 1000, 10000};

    // Number of runs per input size to average out fluctuations
    int runs_per_n = 30;

    // Open CSV file to append results
    ofstream csv("benchmark_results.csv", ios::app);
    csv << "Algorithm,InputSize,Time_ns\n";  // header for quick sort

    cout << "--- Quick Sort Benchmark ---" << endl;
    cout << "Averaged over " << runs_per_n << " runs per input size.\n" << endl;

    // Loop through each input size
    for (int n : n_values) {
        long long total_duration = 0;

        for (int i = 0; i < runs_per_n; ++i) {
            vector<int> data = generateRandomVector(n);

            auto start = high_resolution_clock::now();
            quickSort(data, 0, data.size() - 1);
            auto end = high_resolution_clock::now();

            total_duration += duration_cast<nanoseconds>(end - start).count();
        }

        long long average_duration = total_duration / runs_per_n;

        // Print to console
        cout << "n=" << n << " | Avg Time = "
             << average_duration << " ns" << endl;

        // Save to CSV
        csv << "QuickSort," << n << "," << average_duration << "\n";
    }

    csv.close();
    cout << "\nResults appended to benchmark_results.csv" << endl;

    return 0;
}
