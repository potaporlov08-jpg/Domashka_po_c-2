#include <iostream>
#include <functional>
#include <string>
#include <stdexcept>

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
  double a, b;
  std::cout << "Введите два числа: ";
  std::cin >> a >> b;

  calc.setStrategy([](double x, double y) { return x + y; });
  std::cout << "Сложение: " << calc.realisation(a, b) << "\n";

  calc.setStrategy([](double x, double y) { return x - y; });
  std::cout << "Вычитание: " << calc.realisation(a, b) << "\n";

  calc.setStrategy([](double x, double y) { return x * y; });
  std::cout << "Умножение: " << calc.realisation(a, b) << "\n";

  calc.setStrategy([](double x, double y) {
    if (y == 0) throw std::runtime_error("Деление на ноль!");
    return x / y;
  });
  try {
    std::cout << "Деление: " << calc.realisation(a, b) << "\n";
  } catch (const std::exception& e) {
    std::cout << "Ошибка: " << e.what() << "\n";
  }
}
