#include "lak/array.hpp"
#include "lak/debug.hpp"
#include "lak/profile.hpp"
#include "lak/vec_intrin.hpp"

#include <iostream>

struct scoped_timer
{
  const lak::astring name;
  const uint64_t start;
  scoped_timer(const lak::astring &timer_name)
  : name(timer_name), start(lak::performance_counter())
  {
  }

  ~scoped_timer()
  {
    const uint64_t end = lak::performance_counter();
    const f64_t diff   = static_cast<f64_t>(end - start);
    std::cout << name << ": " << std::fixed
              << (diff / lak::performance_frequency()) << "sec\n";
  }
};

#define SCOPED_TIMER(NAME)                                                    \
  const auto UNIQUIFY(SCOPED_TIMER_) = scoped_timer(NAME)

int main()
{
  // Make sure std::cout has been used before std::wcout so that std::cout
  // actually works under WSL.
  std::cout << LAK_SGR_RESET;

  auto instructions = lak::instruction_set::get();

  std::cout << std::boolalpha << std::fixed;
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

  std::cout << "\n";

  lak::array<lak::vec4f64_t> vectors;
  vectors.resize(32'000'000);
  for (auto &vec : vectors) vec = lak::vec4f64_t{1.0, 2.0, 3.0, 4.0};

  lak::vec4f64_t out;
  lak::vec4f64_t *volatile out_ptr = &out;

  for (int j = 0; j < 2; ++j)
  {
    for (int i = 0; i < 5; ++i)
    {
      lak::vec4f64_t max = {0.0, 0.0, 0.0, 0.0};
      {
        SCOPED_TIMER("control");
        for (auto &vec : vectors)
        {
          max.x = std::max(max.x, vec.x);
          max.y = std::max(max.y, vec.y);
          max.z = std::max(max.z, vec.z);
          max.w = std::max(max.w, vec.w);
        }
      }
      *out_ptr = max;
    }

    std::cout << "\n";

    for (int i = 0; i < 5; ++i)
    {
      lak::m256d_t max = _mm256_set1_pd(0.0);
      {
        SCOPED_TIMER("intrinsic");
        for (auto &vec : vectors)
        {
          max = _mm256_max_pd(lak::to_wide(vec), max);
        }
      }
      *out_ptr = lak::to_vec4(max);
    }

    std::cout << "\n";
  }
}

#include "../inc/lak/src/debug.cpp"
#include "../inc/lak/src/intrin.cpp"
#include "../inc/lak/src/memmanip.cpp"
#include "../inc/lak/src/profile.cpp"
#include "../inc/lak/src/strconv.cpp"
#include "../inc/lak/src/unicode.cpp"