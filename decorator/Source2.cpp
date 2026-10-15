#include <iostream>
#include <functional>
#include <chrono>

using Operation = std::function<double(double)>;

Operation withLogging(Operation func, const std::string& name) {
  return [func, name](double x) {
    std::cout << "Вызываем " << name << "(" << x << ")\n";
    double result = func(x);
    std::cout << "Результат: " << result << "\n";
    return result;
    };
}

Operation withTiming(Operation func, const std::string& name) {
  return [func, name](double x) {
    auto start = std::chrono::high_resolution_clock::now();
    double result = func(x);
    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << name << " выполнено за " << ms << " мс\n";
    return result;
    };
}

int main() {
  Operation square = [](double x) { return x * x; };

  std::cout << "Без декораторов\n";
  std::cout << "square(5) = " << square(5) << "\n\n";

  std::cout << "С логированием\n";
  Operation loggedSquare = withLogging(square, "square");
  std::cout << "Результат: " << loggedSquare(5) << "\n\n";

  std::cout << "С таймером\n";
  Operation timedSquare = withTiming(square, "square");
  std::cout << "Результат: " << timedSquare(5) << "\n\n";

  std::cout << "С логированием и таймером\n";
  Operation fullSquare = withTiming(withLogging(square, "square"), "square");
  std::cout << "Результат: " << fullSquare(5) << "\n";

  return 0;
}