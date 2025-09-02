// ===================================================================
//                      MERGE SORT BENCHMARK PROGRAM
// ===================================================================
//
// This program benchmarks Merge Sort on arrays of different input sizes.
// Results are averaged over multiple runs for stability and appended
// to the same CSV as other algorithms.
//
// Key Notes:
// - Merge Sort is a divide-and-conquer sorting algorithm.
// - The target is the array itself; we time the sorting process only.
// - Time complexity: O(n log n) in worst case.
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
//                         MERGE SORT
// ===================================================================

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// ===================================================================
//                          MAIN FUNCTION
// ===================================================================

int main() {
    vector<int> n_values = {1, 10, 100, 1000, 10000};
    int runs_per_n = 20;

    ofstream csv("benchmark_results.csv", ios::app); // Append mode
    if (!csv.is_open()) {
        cout << "Error opening CSV file!" << endl;
        return 1;
    }

    cout << "--- Merge Sort Benchmark ---" << endl;
    cout << "Averaged over " << runs_per_n << " runs per input size.\n" << endl;

    for (int n : n_values) {
        long long total_duration = 0;

        for (int i = 0; i < runs_per_n; ++i) {
            vector<int> data = generateRandomVector(n);

            auto start = high_resolution_clock::now();
            mergeSort(data, 0, data.size() - 1);
            auto end = high_resolution_clock::now();

            total_duration += duration_cast<nanoseconds>(end - start).count();
        }

        long long average_duration = total_duration / runs_per_n;

        cout << "n=" << n << " | Avg Time = "
             << average_duration << " ns" << endl;

        csv << "MergeSort," << n << "," << average_duration << "\n";
    }

    csv.close();
    cout << "\nResults appended to benchmark_results.csv" << endl;

    return 0;
}
