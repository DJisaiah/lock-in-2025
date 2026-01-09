#include <stddef.h>

// In C, instead of returning an array, you are expected to
// assign the results to the two output parameters
// `positives_count` and `negatives_sum`.
// If the input is an empty array, you must assign 0 to both.

void count_positives_sum_negatives(
    const int values[/* count */], size_t count,
    int *positives_count, int *negatives_sum
)
{
    *positives_count = 0;
    *negatives_sum = 0;
    
    for (size_t i = 0; i < count; i++) {
    // if values was null we could get a segfault (trying to access address 0 which is reserved by os)
    // can move this out the loop for more efficiency
      if (values == NULL || count == 0) {
          return;
      }
      if (*(values + i) > 0) { // same as values[i]
          (*positives_count)++; // ++ has greater precendence than *
      } else if (*(values + i) < 0) {
          *negatives_sum += *(values + i);
      }
    }
}

// size_t had to be passed since when an array is passed it decays to a pointer
// if we try to pass a size in the parameter list C will just ignore it. 
// we pass pointers of positive_count and negative count to escape the scope limit
