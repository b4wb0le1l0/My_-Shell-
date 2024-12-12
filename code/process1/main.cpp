#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

const int BLOCK_SIZE = 8192;

void io_thpt_write(const string& file_path, size_t iterations) 
{
    ofstream ofs(file_path, ios::binary);
    if (!ofs) 
    {
        cerr << "Error opening file: " << file_path << endl;
        return;
    }

    vector<char> buffer(BLOCK_SIZE, 'F');

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i) 
    {
        ofs.write(buffer.data(), BLOCK_SIZE);
    }
    auto end = chrono::high_resolution_clock::now();

    double seconds = chrono::duration_cast<chrono::seconds>(end - start).count();
    cout << "Wrote " << iterations * BLOCK_SIZE / 1024 << " KB in " << seconds << " seconds." << endl;

    ofs.close();
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        cerr << "Usage: " << argv[0] << " <iterations>" << endl;
        return 1;
    }

    size_t iterations = static_cast<size_t>(std::atoi(argv[1]));
    string file_path = "output_io_thpt_write.dat";

    io_thpt_write(file_path, iterations);

    return 0;
}
