#include "syscall.h"
#include "i386.h"

void meeseks1_func(void);

void task(void) {
  //syscall_meeseeks((uint32_t)&meeseks1_func, 40, 25);
  
  int8_t* x = (int8_t*) 0x200000;  
  int8_t* y = (int8_t*) 0x200004;
  // breakpoint();
  syscall_look(x, y);

  while (1) {
    __asm volatile("nop");
  }
}

void meeseks1_func(void) {
  // Do Nothing!
  while (1) {
    __asm volatile("nop");
  }

  int8_t deltax, deltay;

  while (true) {
    syscall_look(&deltax, &deltay);
    syscall_move(deltax, deltay);
    continue;
    while (deltax < 0) {
      syscall_move(-1, 0);
      deltax++;
    }
    while (deltay < 0) {
      syscall_move(0, -1);
      deltay++;
    }
    while (deltax > 0) {
      syscall_move(1, 0);
      deltax--;
    }
    while (deltay > 0) {
      syscall_move(0, 1);
      deltay--;
    }
  }
}
