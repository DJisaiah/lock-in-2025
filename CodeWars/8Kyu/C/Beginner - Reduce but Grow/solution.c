#include <stddef.h>
// size_t used for indexing or counting in C. never neg
int grow(size_t size, const int arr[size]) {
  int result = 1;
  for (size_t i = 0; i < size; i++) {
    result *= arr[i];
  }
  return result;
}
