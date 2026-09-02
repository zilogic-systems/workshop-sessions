#include <stdio.h>
#include <add.h>
#include <sub.h>
#include <mul.h>
#include <div.h>

int main(void)
{
  int x = 2;
  int y = 3;
  int sum;
  int diff;
  long int product;
  float quotient;

  sum = add(x, y);
  diff = sub(y, x);
  product = mul(x, y);
  quotient = div((float)y, (float)x);

  printf("Sum: %d\n", sum);
  printf("Diff: %d\n", diff);
  printf("Product: %ld\n", product);
  printf("Quotient: %f\n", quotient);

}
