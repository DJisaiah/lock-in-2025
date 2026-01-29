#include <stddef.h>

int square_sum(const int values[/* count */], size_t count) {
  int sum = 0;
  for (size_t i = 0; i < count; i++) {
    sum += values[i] * values[i];
  }
  return sum;
}
