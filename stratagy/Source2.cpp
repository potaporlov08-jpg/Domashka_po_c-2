#include <iostream>
#include <functional>
#include <string>

using MathStrategy = std::function<double(double, double)>;

class Calculator {
public:
  void setStrategy(MathStrategy strategy) {
    strategy_ = strategy;
  }

  double realisation(double a, double b) {
    if (strategy_) return strategy_(a, b);
    throw std::runtime_error("Стратегия не установлена");
  }

private:
  MathStrategy strategy_;
};

int main() {
  Calculator calc;
  int a;
  int b;
  std::cin >> a >> b;
  calc.setStrategy([](double a, double b) { return a + b; });
  std::cout << "Сложение: " << calc.realisation(10, 5) << "\n";

  calc.setStrategy([](double a, double b) { return a - b; });
  std::cout << "Вычитание: " << calc.realisation(10, 5) << "\n";

  calc.setStrategy([](double a, double b) { return a * b; });
  std::cout << "Умножение: " << calc.realisation(10, 5) << "\n";

  calc.setStrategy([](double a, double b) { return a / b; });
  std::cout << "Деление: " << calc.realisation(10, 5) << "\n";
}
