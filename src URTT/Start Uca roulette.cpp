#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

// ASCII escape codes for colors
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

// Function to simulate CPU "thinking..."
void cpuThinking() {
    cout << "CPU is thinking";
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << endl;
}
