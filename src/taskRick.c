#include "stddef.h"
#include "syscall.h"
#include "i386.h"

void meeseks1_func(void);
void meeseks2_func(void);

void task(void) {

  syscall_meeseeks((uint32_t)&meeseks1_func, 21, 24);
  syscall_meeseeks((uint32_t)&meeseks2_func, 6, 6);

  while (1) {
    __asm volatile("nop");
  }
}

void meeseks1_func(void) {
  int8_t x;
  int8_t y;
  syscall_look(&x, &y);
  while (1) {
    for (int i = 0; i < 80; i++) {
      syscall_move(-1, 0);
    }
    syscall_move(0, -1);
  }
}

void meeseks2_func(void) {
  while (1) {
    for (int i = 0; i < 80; i++) {
      syscall_move(1, 0);
    }
    syscall_move(0, 1);
  }
}
