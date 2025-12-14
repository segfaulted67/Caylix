#define CX_IMPLEMENTATION
#define CX_SINGLE_PRECISION_FLOAT
#define CX_ANSI_ENABLE
#include "../caylix.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N (1 << 3)
int main() {
  CX_COMPLEX x[N] = {
        1.0 + 2.0*I,
        -1.0 + 1.0*I,
        0.5 - 0.5*I,
        2.0 - 1.0*I,
        1.0,
        2.0,
        0.0,
        0.0,
    };


  CX_COMPLEX X[N] = { 0 };
  CX_COMPLEX fft_X[N] = { 0 };
  CX_COMPLEX x_inv[N] = { 0 };
  cx_dft(x, X, N);
  cx_fft(x, fft_X, N);
  cx_dft_inverse(X, x_inv, N);

  printf("Original Array:\n");
  for (int k = 0; k < N; k++) {
    printf("x[%d] = %.6f + %.6fi\n", k, creal(x[k]), cimag(x[k]));
  }

  CX_PRINTLN();

  printf("FFT Results:\n");
  for (int k = 0; k < N; k++) {
    printf("X[%d] = %.6f + %.6fi\n", k, creal(fft_X[k]), cimag(fft_X[k]));
  }

  CX_PRINTLN();

  return 0;
}
