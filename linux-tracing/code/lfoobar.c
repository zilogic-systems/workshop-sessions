#include <sys/types.h>
#include <unistd.h>

void bar() {
  getpid();
}

void foo() {
  bar();
}

int main() {
  foo();
  bar();
}
