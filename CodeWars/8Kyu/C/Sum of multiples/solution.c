//  for invalid input, return -1

int sum_mul(int n, int m) {
    if (m <= 0 || n <= 0) return -1;
    int sum = 0;
    for (int i = n; i < m; i += n) {
      sum += i;
    }
    return sum;
}
