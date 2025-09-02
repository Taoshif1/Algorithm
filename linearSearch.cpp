// Includes all standard libraries, common in competitive programming
#include <bits/stdc++.h>
#include <fstream> // for file output

// Use the standard and chrono namespaces to avoid writing "std::"
using namespace std;
using namespace std::chrono;

/**
 * @brief Generates a vector of high-quality random integers.
 * @param size The number of integers to generate.
 * @return A vector of the specified size containing random integers.
 */
vector<int> generateRandomVector(int size) {
    vector<int> vec(size);

    // Modern C++ random number generation
    random_device rd;      // Obtains a truly random seed from the hardware
    mt19937 gen(rd());     // Mersenne Twister engine, a high-quality generator
    uniform_int_distribution<> distrib(0, 100000); // Ensures numbers are uniform in this range

    for (int i = 0; i < size; ++i) {
        vec[i] = distrib(gen);
    }
    return vec;
}


/**
 * @brief Performs a linear search for a target value in a vector.
 * The vector is passed by constant reference (`const&`) for efficiency,
 * as it prevents making a slow copy of the whole vector.
 * @param arr The vector to search through.
 * @param target The value to search for.
 * @return The index of the target if found, otherwise -1.
 */
int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i; // Target found
        }
    }
    return -1; // Target not found
}


int main() {
    // A list of input sizes 'n' to benchmark
    vector<int> n_values = {1, 10, 100, 1000, 10000};

    // Number of times to repeat the test for each 'n' to get a stable average
    int runs_per_n = 30;

    // Open CSV file
    ofstream csv("linear_search.csv");
    csv << "Input Size,Avg Time (ns)\n";

    // --- Print Report Header ---
    cout << "--- Linear Search Benchmark ---" << endl;
    cout << "Averaged over " << runs_per_n << " runs for each input size." << endl;
    cout << "------------------------------------------" << endl;
    cout << "Input Size (n) | Avg. Time (nanoseconds)" << endl;
    cout << "------------------------------------------" << endl;

    // --- Main Benchmarking Loop ---
    // This loop iterates through each value of 'n' (1, 10, 100, ...)
    for (int n : n_values) {

        // Use 'long long' to store total time, preventing overflow with many runs
        long long total_duration = 0;

        // --- Averaging Loop ---
        // This inner loop runs the test 'runs_per_n' times for the current 'n'
        for (int i = 0; i < runs_per_n; ++i) {

            // 1. Generate fresh data for each run to ensure fairness
            vector<int> data = generateRandomVector(n);
            int target = -1; // Guarantees worst-case (element is not present)

            // 2. Time the algorithm
            auto start = high_resolution_clock::now();
            linearSearch(data, target);
            auto end = high_resolution_clock::now();

            // 3. Add the duration of this single run to our total
            total_duration += duration_cast<nanoseconds>(end - start).count();
        }

        long long average_duration = total_duration / runs_per_n;

        // Print + Save at the same time
        cout << setw(10) << n << " | " << setw(15) << average_duration << endl;
        csv << n << "," << average_duration << "\n";  // save to CSV
}
        csv.close();  // close file

    return 0;
}
