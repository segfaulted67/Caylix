CC = cc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

ode: ode_test.c
	$(CC) $(CFLAGS) -o ode_test ode_test.c $(LDFLAGS)

fft: fft_test.c
	$(CC) $(CFLAGS) -o fft_test fft_test.c $(LDFLAGS)

clean:
	rm ode_test fft_test

.PHONY:
	ode fft clean
