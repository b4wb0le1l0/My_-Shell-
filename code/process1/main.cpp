#include <iostream>
#include <windows.h>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

const int BLOCK_SIZE = 8192;

void io_thpt_write(const string& file_path, size_t iterations) 
{
    HANDLE hFile = CreateFile(
        file_path.c_str(),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_FLAG_NO_BUFFERING,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) 
    {
        cerr << "Error opening file: " << GetLastError() << endl;
        return;
    }

    vector<char> buffer(BLOCK_SIZE, 'F');

    auto start = chrono::high_resolution_clock::now();

    DWORD bytesWritten;
    for (size_t i = 0; i < iterations; ++i) 
    {
        if (!WriteFile(hFile, buffer.data(), BLOCK_SIZE, &bytesWritten, NULL)) 
        {
            cerr << "Error writing to file: " << GetLastError() << endl;
            CloseHandle(hFile);
            return;
        }
    }

    auto end = chrono::high_resolution_clock::now();

    double seconds = chrono::duration_cast<chrono::seconds>(end - start).count();
    cout << "Wrote " << iterations * BLOCK_SIZE / 1024 << " KB in " << seconds << " seconds." << endl;

    CloseHandle(hFile);
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
