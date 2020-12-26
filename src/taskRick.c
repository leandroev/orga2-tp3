#include "stddef.h"
#include "syscall.h"
#include "i386.h"

void meeseks1_func(void);

void task(void) {
  int8_t x, y;
  for (int j = 0; j < 1; j++) {
    syscall_meeseeks((uint32_t)&meeseks1_func, 0, 0);
    for (int i = 0; i < 10; i++) {
      syscall_look(&x, &y);
    }
  }

  while (1) {
    __asm volatile("nop");
  }
}

void meeseks1_func(void) {
  int8_t x, y;

  while (1) {
    syscall_look(&x, &y);

    int8_t movx = x;
    if (movx > 0) movx = 1;
    if (movx < 0) movx = -1;

    int8_t movy = y;
    if (movy > 0) movy = 1;
    if (movy < 0) movy = -1;      

    // Nos movemos a lo sumo 1.
    if (movx != 0) movy = 0;

    syscall_move(movx, movy);
  }
}
