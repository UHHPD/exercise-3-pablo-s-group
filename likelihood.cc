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

  // Exercise 1a
  double mu = 3.11538; // sample mean
  double L = prob(daten, mu);

  cout << L << endl;

  // Exercise 1b
  ofstream fout("likelihood.txt");
  for (double mu = 0.0; mu <= 6.0; mu += 0.1) {
    double L = prob(daten, mu);
    fout << mu << " " << L << "\n";
  }

  fout.close();

  // Exercise 1c
  ofstream fout_nll("nll.txt");
  for (double mu = 0.0; mu <= 6.0; mu += 0.1) {
    double L = prob(daten, mu);

    double nll = -2.0 * log(L);

    fout_nll << mu << " " << nll << "\n";
  }

  fout_nll.close();

  // Exercise 1d
  double Lhat = prob(daten, 3.11538);
  double nll_hat = -2.0 * log(Lhat);

  ofstream fout_deltanll("deltanll.txt");
  for (double mu = 0.0; mu <= 6.0; mu += 0.1) {
    double L = prob(daten, mu);
    double nll = -2.0 * log(L);

    double deltanll = nll - nll_hat;
    fout_deltanll << mu << " " << deltanll << "\n";
  }
  fout_deltanll.close();

  // Exercise 1e
  double mu_hat = 3.11538;

  double L_model = prob(daten, mu_hat); 

  double L_sat = 1.0;
  for (int k : daten) {
    L_sat *= poisson(k, k);
  }

  double lambda = L_model / L_sat;
  double minus2logLambda = -2.0 * log(lambda);

  cout << "-2 ln Lambda = " << minus2logLambda << endl;

  int ndof = daten.size() - 1;
  double mean = ndof;
  double sigma = sqrt(2.0 * ndof);

  double z = (minus2logLambda - mean) / sigma;

  cout << "z = " << z << endl;

  return 0;
}
