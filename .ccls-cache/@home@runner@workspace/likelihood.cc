#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

double poisson(double mu, int k) {
  return pow(mu, k) * exp(-mu) / tgamma(k + 1);
}

double prob(const vector<int> &daten, double mu) {
  double L = 1.0;
  for (int k : daten) {
    L *= poisson(mu, k);
  }
  return L;
}

int main() {
  vector<int> daten;

  ifstream fin("datensumme.txt");
  int zahl;

  while (fin >> zahl) {
    daten.push_back(zahl);
  }
  fin.close();

  double mu = 3.11538; // sample mean
  double L = prob(daten, mu);

  cout << L << endl;

  return 0;
}
