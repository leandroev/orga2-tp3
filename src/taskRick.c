#include "stddef.h"
#include "syscall.h"
#include "i386.h"

void meeseks1_func(void);
void meeseks3_func(void);

void task(void) {
  syscall_meeseeks((uint32_t)&meeseks1_func, 3, 10);
  syscall_meeseeks((uint32_t)&meeseks3_func, 10, 3);

  while (1) {
    __asm volatile("nop");
  }
}

void meeseks1_func(void) {
  for (int i = 0; i < 1000; i++) {
    syscall_move(-1, 0);
  }
  while (1) {
    __asm volatile("nop");
  }
}

void meeseks3_func(void) {
  for (int i = 0; i < 1000; i++) {
    syscall_move(0, -1);
  }
  while (1) {
    __asm volatile("nop");
  }
}
