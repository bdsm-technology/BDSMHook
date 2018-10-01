#include <iostream>
#include <cassert>

extern "C" void MSHookFunction(void *symbol, void *replace, void **result);

int test(int a, int b) {
  std::cout << "a: " << a << ", b: " << b << std::endl;
  return a + b;
}

int (*test$src)(int a, int b);

int test$new(int a, int b) {
  std::cout << "HOOKED a: " << a << ", b: " << b << std::endl;
  auto ret = test$src(a + 233, b - 666);
  std::cout << "HOOKED result: " << ret << std::endl;
  return ret - 888;
}

int main() {
  std::cout << "Before hook: test(123, 456): " << test(123, 456) << std::endl;
  std::cout << "Hooking..." << std::endl;
  MSHookFunction((void*)test, (void*)test$new, (void **)&test$src);
  std::cout << "After  hook: test(123, 456): ";
  auto ret = test(123, 456);
  std::cout << ret << std::endl;
  assert(ret == -742);
}