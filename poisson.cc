#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double faktorial(double x) {
  if(x <= 0) return 1;
  else return faktorial(x-1)*x;
}

double poisson(double mu, int k) {
    return pow(mu,k)*exp(-mu)/faktorial(k);
}


int main() {
    using namespace std;
    vector<int> zaehler(11);

    ifstream fin("datensumme.txt");
    ofstream fout("hist.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        zaehler[n_i] += 1;

    }
    fin.close();
    
    ofstream fout2("histpoi.txt");
    for(unsigned int k=0; k< zaehler.size(); k++) {
      cout << k << ":" << zaehler[k] << endl;
      fout << k << " " << zaehler[k] << endl;
      fout2 << k << " " << zaehler [k] << " " << poisson(3.11538, k)*234 << endl;
      cout << k << " " << zaehler [k] << " " << poisson(3.11538, k)*234 << endl;
    }
}