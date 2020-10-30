#include "lak/debug.hpp"
#include "lak/intrin.hpp"

#include <iostream>

int main()
{
  // Make sure std::cout has been used before std::wcout so that std::cout
  // actually works under WSL.
  std::cout << LAK_SGR_RESET;

  auto instructions = lak::instruction_set::get();

  std::cout << std::boolalpha;
  std::cout << "MMX? " << instructions.MMX << "\n";
  std::cout << "SSE? " << instructions.SSE << "\n";
  std::cout << "SSE2? " << instructions.SSE2 << "\n";
  std::cout << "SSE3? " << instructions.SSE3 << "\n";
  std::cout << "SSSE3? " << instructions.SSSE3 << "\n";
  std::cout << "SSE4.1? " << instructions.SSE41 << "\n";
  std::cout << "SSE4.2? " << instructions.SSE42 << "\n";
  std::cout << "AVX? " << instructions.AVX << "\n";
  std::cout << "AVX2? " << instructions.AVX2 << "\n";
  std::cout << "AVX512F? " << instructions.AVX512F << "\n";
  std::cout << "AVX512PF? " << instructions.AVX512PF << "\n";
  std::cout << "AVX512ER? " << instructions.AVX512ER << "\n";
  std::cout << "AVX512CD? " << instructions.AVX512CD << "\n";
}

#include "../inc/lak/src/debug.cpp"
#include "../inc/lak/src/intrin.cpp"
#include "../inc/lak/src/strconv.cpp"
#include "../inc/lak/src/unicode.cpp"