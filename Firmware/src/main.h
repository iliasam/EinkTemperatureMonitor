#ifndef _MAIN_H
#define _MAIN_H

#include <stdint.h>
#include <intrinsics.h>

extern volatile uint32_t uwTick;//taken from HAL

#if defined ( __ICCARM__ ) // IAR
    #define ENTER_CRITICAL(x)       x=__get_interrupt_state(); __disable_interrupt()
    #define LEAVE_CRITICAL(x)       __set_interrupt_state(x)

#elif defined (__CC_ARM) // KEIL
    #define ENTER_CRITICAL(x)       x=__disable_irq()
    #define LEAVE_CRITICAL(x)       if (!x) __enable_irq()
    #define NO_INIT                 __attribute__((zero_init))
#else
  #error ERROR
#endif

#define SET_TIMESTAMP(x)  (x = uwTick)
#define START_TIMER(x, duration)  (x = (uwTick + duration))
#define TIMER_ELAPSED(x)  ((uwTick > x) ? 1 : 0)
#define CHECK_TIMER(x, duration)  ((uwTick - x > duration) ? 1 : 0)

#endif
