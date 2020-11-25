#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

double faktorial(double x) {
  using namespace std;
  if(x <= 0) return 1;
  else return faktorial(x-1)*x;
}

double poisson(double mu, int k) {
    return pow(mu,k)*exp(-mu)/faktorial(k);
}

double prob(std::vector<int> daten, double mu) {
  double L = 1;
  for(int i=0; i<daten.size(); i++) {
    L *= poisson(mu,daten[i]);
  }
  return L;
}
double prob_n(vector<int> daten) {
  double L = 1;
  for(int i=0; i<daten.size(); i++) {
    L *= poisson(daten[i],daten[i]);
  }
  return L;
}

double lowest_ll = 0;
std::vector<int> daten;

double calculateDeltaLL(double mu) {
  using namespace std;
  double L_mu = prob(daten, mu);
  double LL = -2*log(L_mu);
  double deltaLL = LL - lowest_ll;
  return deltaLL;
}

double findTop(std::vector<double> deltaLL, double start, double steps) {
  for(int mu = start; mu<6; mu+=steps) {
    
  }
  
}

double findLL(double LL, std::vector<int> daten, double upper, double lower) {
  using namespace std;
  double mid;
  double LL_upper = calculateDeltaLL(upper);
  double LL_lower = calculateDeltaLL(lower);
  for(int i = 0; i < 100; i++) {
    mid = (upper+lower)/2;
    double LL_mu = calculateDeltaLL(mid);
    if(LL_mu > LL) {
      if(LL_upper > LL_lower) {
        upper = mid;
        LL_upper = LL_mu;
      } else {
        lower = mid;
        LL_lower = LL_mu;
      }
    } else {
      if(LL_upper > LL_lower) {
        lower = mid;
        LL_lower = LL_mu;
      } else {
        upper = mid;
        LL_upper = LL_mu;
      }
    }
  }
  std::cout << "upper " << upper << "  " << LL_upper << std::endl;
  std::cout << "lower " << lower << "  " << LL_lower << std::endl;
  return (upper+lower)/2;
}
int main() {
  using namespace std;
  vector<int> zaehler(11);

  ifstream fin("datensumme.txt");
  ofstream fout("likelihood.txt");
  ofstream fout2("nll.txt");
  ofstream fout3("deltanll.txt");
  int n_i;
  for(int i = 0 ; i < 234 ; ++i) {
    fin >> n_i;
    daten.push_back(n_i);
  }
  fin.close();

  lowest_ll = -2*log(prob(daten, 3.11538));
  
  cout << prob(daten, 3.11538) << endl;
  double LL_mu = -2*log(prob(daten, 3.11538));
  for(double mu = 0; mu<=6; mu+= 0.1) {
    double L_mu = prob(daten, mu);
    double LL = -2*log(L_mu);
    double deltaLL = LL - LL_mu;
    //cout << mu << " " << deltaLL << endl;
    fout << mu << " " << L_mu << endl;
    fout2 << mu << " " << LL << endl;
    fout3 << mu << " " << deltaLL << endl;
    
  }
  double lowerMu = findLL(1,daten,3.1,3.0);
  double upperMu = findLL(1,daten,3.3,3.1);
  double uncertainty = (upperMu - lowerMu)/2;
  cout << "mu = " << 3.11538 << endl;
  cout << "uncertainty: " << uncertainty << endl;
  cout << "std dev mu = " << 1.65365/sqrt(234) << endl;

  double Lambda = prob(daten, 3.11538)/prob_n(daten);
  cout << "Lambda = " << Lambda << endl;
  double LLambda = -2*log(Lambda);
  cout << "LLambda = " << LLambda << endl;
  double z = (LLambda - 233) / sqrt(233);
  cout << "z = " << z << endl;



}