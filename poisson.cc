#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

double poisson(double mu, int k) { return 0; }

int main() {
  vector<int> zaehler(11, 0);

  ifstream infile("datensumme.txt");
  if (!infile.is_open()) {
    cerr << "Error: Could not open file datensumme.txt" << endl;
    return 1;
  }

  int zahl;
  int N = 0;

  while (infile >> zahl) {
    if (zahl >= 0 && zahl <= 10) {
      zaehler[zahl] += 1;
      N++;
    }
  }

  infile.close();
  cout << "Frequencies:" << endl;

  for (unsigned int k = 0; k < zaehler.size(); ++k) {
    cout << k << ": " << zaehler[k] << endl;
  }

  // Write results to hist.txt
  ofstream outfile("hist.txt");
  if (!outfile.is_open()) {
    cerr << "Error: Could not open file hist.txt for writing" << endl;
    return 1;
  }

  for (unsigned int k = 0; k < zaehler.size(); ++k) {
    outfile << k << " " << zaehler[k] << endl;
  }

  outfile.close();

  cout << "Results written to hist.txt" << endl;

  return 0;
}