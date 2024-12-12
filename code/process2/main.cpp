#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <numeric>
#include <cstdlib> // Для std::atoi

using namespace std;

void binary_search(const vector<int>& sorted_array, int target) 
{
    size_t left = 0;
    size_t right = sorted_array.size() - 1;
    while (left <= right) 
    {
        size_t mid = left + (right - left) / 2;
        if (sorted_array[mid] == target) 
        {
            return;
        } 
        else if (sorted_array[mid] < target) 
        {
            left = mid + 1;
        } 
        else 
        {
            right = mid - 1;
        }
    }
    cout << "Target " << target << " not found." << endl;
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        cerr << "Usage: " << argv[0] << " <num_iterations>" << endl;
        return 1;
    }

    size_t num_iterations = static_cast<size_t>(std::atoi(argv[1]));

    vector<int> array(1000000);
    iota(array.begin(), array.end(), 0);

    random_device rd;
    mt19937 gen(rd());

    double total_seconds = 0.0;

    for (size_t i = 0; i < num_iterations; ++i) 
    {
        uniform_int_distribution<> dis(0, 999999);
        int target = dis(gen);

        auto start = chrono::high_resolution_clock::now();
        binary_search(array, target);
        auto end = chrono::high_resolution_clock::now();

        double seconds = chrono::duration_cast<chrono::seconds>(end - start).count();
        total_seconds += seconds;
    }

    return 0;
}
