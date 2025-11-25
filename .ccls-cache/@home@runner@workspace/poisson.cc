#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

double poisson(double mu, int k) {
  return pow(mu, k) * exp(-mu) / tgamma(k + 1);
}

double mean(const vector<int> &zaehler) {
  double sum = 0.0;
  int N = 0;
  for (unsigned int k = 0; k < zaehler.size(); ++k) {
    sum += k * zaehler[k];
    N += zaehler[k];
  }
  return sum / N;
}

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

  cout << "Results written to hist.txt" << endl;

  // Exercise 1c

  double mu = mean(zaehler);
  cout << "mu = " << mu << endl;

  ofstream poi("histpoi.txt");
  if (!outfile.is_open()) {
    cerr << "Error: Could not open file histpoi.txt for writing" << endl;
    return 1;
  }

  for (int k = 0; k <= 10; ++k) {
    double expected = N * poisson(mu, k);
    poi << k << " " << zaehler[k] << " " << expected << endl;
  }

  poi.close();

  cout << "Results written to histpoi.txt" << endl;
  return 0;
}