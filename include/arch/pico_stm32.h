#define dbg(...) do {} while(0)
/* #define dbg printf */

/*************************/

/*** MACHINE CONFIGURATION ***/
/* Temporary (POSIX) stuff. */
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

extern volatile uint32_t __stm32_tick;


#ifdef PICO_SUPPORT_DEBUG_MEMORY
static inline void *pico_zalloc(int len)
{
    /* dbg("%s: Alloc object of len %d, caller: %p\n", __FUNCTION__, len, __builtin_return_address(0)); */
    return calloc(len, 1);
}

static inline void pico_free(void *tgt)
{
    /* dbg("%s: Discarded object @%p, caller: %p\n", __FUNCTION__, tgt, __builtin_return_address(0)); */
    free(tgt);
}
#else
# define pico_zalloc(x) calloc(x, 1)
# define pico_free(x) free(x)
#endif



static inline unsigned long PICO_TIME(void)
{
    register uint32_t tick = __stm32_tick;
    return tick / 1000;
}

static inline unsigned long PICO_TIME_MS(void)
{
    return __stm32_tick;
}

static inline void PICO_IDLE(void)
{
    unsigned long tick_now = __stm32_tick;
    while(tick_now == __stm32_tick) ;
}

