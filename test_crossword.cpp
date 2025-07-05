#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    cout << "Testing crossword file loading..." << endl;
    
    ifstream file("src/game_data/words.txt");
    if (!file.is_open()) {
        cout << "ERROR: Could not open words.txt" << endl;
        return 1;
    }
    
    vector<string> words;
    string word;
    while (getline(file, word)) {
        if (!word.empty()) {
            words.push_back(word);
            cout << "Loaded word: " << word << endl;
        }
    }
    
    cout << "Total words loaded: " << words.size() << endl;
    file.close();
    
    cout << "File loading test completed successfully!" << endl;
    return 0;
} 