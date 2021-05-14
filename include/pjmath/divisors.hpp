
#include "definitions.hpp"

#include <set>
#include <cstdint>

namespace pjmath
{
  template <typename Integer>
  std::set<Integer> properDivisorsOf(Integer number)
  {
    static_assert(std::is_integral_v<Integer>);
    std::set<Integer> divisors;

    for (Integer possibleDivisor = 2; possibleDivisor < number; possibleDivisor++)
    {
      Integer quotient = number / possibleDivisor;
      Integer remainder = number % possibleDivisor;

      if (possibleDivisor > quotient)
      {
        break;
      }
      if (remainder != 0)
      {
        continue;
      }

      if (possibleDivisor == quotient)
      {
        divisors.insert(quotient);
        break;
      }

      divisors.insert(possibleDivisor);
      divisors.insert(quotient);
    }
    return divisors;
  }

  template <typename Integer>
  std::set<Integer> divisorsOf(Integer n)
  {
    auto divisors = properDivisorsOf(n);
    divisors.insert(n);
    divisors.insert(1);
    return divisors;
  }

}