#include <iostream>
#include <unistd.h>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    cout << "Start" << endl;
    auto begin_t =  chrono::steady_clock::now();
    this_thread::sleep_for(std::chrono::seconds(1));
    auto end_t = chrono::steady_clock::now();
    auto elapsed_secs = chrono::duration_cast<chrono::seconds>(end_t - begin_t);
    cout << "Elapsed " << elapsed_secs.count() << " secs" << endl;
}

