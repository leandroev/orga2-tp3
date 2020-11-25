#include "stddef.h"
#include "syscall.h"
#include "i386.h"

void meeseks2_func(void);
void meeseks4_func(void);

void task(void) {
  syscall_meeseeks((uint32_t)&meeseks2_func, 75, 30);
  syscall_meeseeks((uint32_t)&meeseks4_func, 70, 35);

  while (1) {
    __asm volatile("nop");
  }
}

void meeseks2_func(void) {
  for (int i = 0; i < 1000; i++) {
    syscall_move(1, 0);
  }
  while (1) {
    __asm volatile("nop");
  }
}

void meeseks4_func(void) {
  for (int i = 0; i < 1000; i++) {
    syscall_move(0, 1);
  }
  while (1) {
    __asm volatile("nop");
  }
}
