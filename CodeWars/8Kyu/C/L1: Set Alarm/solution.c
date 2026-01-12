#include <stdbool.h>

bool set_alarm(bool employed, bool vacation) {
  return employed && !vacation;
}
