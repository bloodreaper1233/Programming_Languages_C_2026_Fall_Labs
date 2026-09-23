#include <stdio.h>

/*
    Task:
    Write a function `int sum_to_n(int n)` that computes
    the sum of all integers from 1 up to n using a for loop.

    In main():
      - Ask user for a positive integer n
      - If n < 1, print an error
      - Otherwise, call sum_to_n and print the result
*/

int sum_to_n(int n) {
  int sum = 0;  // sum starts
  for (int i = 1; i <= n; i++) {
    sum += i;
  }
  return sum;
}

int main(void) {
  int n;

  printf("Enter a positive integer n: ");
  if (scanf("%d", &n) != 1) {
    printf("error:Invalid input 1.\n");
    return 1;
  }

  if (n < 1) {
    printf("error:n must be greater than or equal to 1.\n");
  } else {
    int result = sum_to_n(n);
    printf("som from 1 to %d is:%d\n", n, result);
  }

  return 0;
}
