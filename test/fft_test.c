#define CX_IMPLEMENTATION
#define CX_SINGLE_PRECISION_FLOAT
#define CX_ANSI_ENABLE
#include "../caylix.h"

#include <stdio.h>
#include <stdlib.h>

#define N (1 << 6)

int main()
{
  CX_COMPLEX x[N] = { 0 };

  int k1 = 500, k2 = 1700;
  for (int n = 0; n < N; n++) {
    x[n] = cos(2.0 * CX_PI * k1 * n / N)
           + 0.5 * cos(2.0 * CX_PI * k2 * n / N);
  }

  CX_COMPLEX X[N] = { 0 };

  // cx_dft(x, X, N);
  cx_fft(x, X, N);

  printf("Original Samples:\n");
  for (int k = 0; k < N; k++) {
    CX_INFO("x[%d] = %.6f + %.6fi", k, creal(x[k]), cimag(x[k]));
  }

  CX_PRINTLN();

  printf("FFT Results:\n");
  for (int k = 0; k < N; k++) {
    CX_INFO("X[%d] = %.6f + %.6fi", k, creal(X[k]), cimag(X[k]));
  }

  CX_PRINTLN();

	return 0;
}
