/**
 * matplotlib-cppとnumpyを利用できるようにパッケージをインストールし、
 * `g++ ./fermi-distribution.cpp -I/usr/include/python3.9 -lpython3.9`でビルドできます
 */

#include "cmath"
// source: https://github.com/lava/matplotlib-cpp
#include "lib/matplotlibcpp.h"
#include "vector"

namespace plt = matplotlibcpp;

template <class F = float, class U = unsigned char>
std::vector<F> linspace(F init, F end, U size) {
  F inc = (end - init) / static_cast<F>(size - 1);

  std::vector<F> ret(size);
  ret[0] = init;
  ret[size - 1] = end;

  F aux = end;
  for (size_t i = size - 1; i >= 1; --i, aux -= inc) ret[i] = aux;

  return ret;
}

std::vector<double> calcFermiDistribution(std::vector<double> E, double Ef,
                                          double kT) {
  std::vector<double> result;
  for (decltype(E.size()) i = 0; i < E.size(); i++) {
    result.push_back(1 / (1 + std::exp((E[i] - Ef) / kT)));
  }
  return result;
}

int main() {
  std::vector<double> E = linspace<double>(0, 1.1, 100);
  double Ef = 0.55;
  double k = 0.0000000000000000000000138;
  double T1 = 300.0, T2 = 450.0;
  double e = 0.00000000000000000016;
  double kT1 = (k * T1) / e, kT2 = (k * T2) / e;

  plt::figure_size(720, 480);

  std::vector<double> y1 = calcFermiDistribution(E, Ef, kT1);
  std::vector<double> y2 = calcFermiDistribution(E, Ef, kT2);

  plt::title("Fermi Distribution");
  plt::xlabel("$E\\mathrm{[eV]}$");
  plt::ylabel("$f(E)$");

  plt::xlim(-0.25, 1.40);
  plt::ylim(-0.25, 1.40);

  plt::grid(true);
  plt::named_plot("$T=300\\mathrm{[K]}$", E, y1);
  plt::named_plot("$T=450\\mathrm{[K]}$", E, y2);
  plt::legend();

  plt::save("./fermi-distribution.png");
}
