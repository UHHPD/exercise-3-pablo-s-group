#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream infile("hist.txt");
    if (!infile.is_open()) {
        cerr << "Error: Could not open hist.txt" << endl;
        return 1;
    }

    vector<int> values;
    vector<int> counts;
    int val, count;

    // Read histogram data from file
    while (infile >> val >> count) {
        values.push_back(val);
        counts.push_back(count);
    }

    infile.close();

    // Find maximum count for scaling
    int max_count = 0;
    for (int c : counts)
        if (c > max_count) max_count = c;

    cout << "Histogram (scaled to 50 characters max):\n\n";

    // Print histogram
    for (size_t i = 0; i < values.size(); ++i) {
        int bar_length = (max_count > 0) ? (counts[i] * 50 / max_count) : 0;
        cout << setw(2) << values[i] << " | ";
        for (int j = 0; j < bar_length; ++j)
            cout << '#';
        cout << " (" << counts[i] << ")\n";
    }

    return 0;
}
