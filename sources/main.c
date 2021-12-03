#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syscalls.h"
#include "hwaccess.h"

void print_sizeof(void)
{
    printf("sizeof(char)      = %ld \r\n", sizeof(char));
    printf("sizeof(uchar)     = %ld \r\n", sizeof(unsigned char));
    printf("sizeof(short)     = %ld \r\n", sizeof(short));
    printf("sizeof(ushort)    = %ld \r\n", sizeof(unsigned short));
    printf("sizeof(int)       = %ld \r\n", sizeof(int));
    printf("sizeof(uint)      = %ld \r\n", sizeof(unsigned int));
    printf("sizeof(long)      = %ld \r\n", sizeof(long));
    printf("sizeof(ulong)     = %ld \r\n", sizeof(unsigned long));
    printf("sizeof(intptr_t)  = %ld \r\n", sizeof(intptr_t));
    printf("sizeof(uintptr_t) = %ld \r\n", sizeof(uintptr_t));
    printf("\r\n");
}

void print_linker(void)
{
    extern uint64_t __start;
    extern uint64_t __text_start;
    extern uint64_t __text_end;
    extern uint64_t __data_start;
    extern uint64_t __data_end;
    extern uint64_t __bss_start;
    extern uint64_t __bss_end;
    extern uint64_t __heap_start;
    extern uint64_t __heap_end;
    extern uint64_t __stack_start;
    extern uint64_t __stack_end;
    extern uint64_t __end;
    extern uint64_t __text_size;
    extern uint64_t __data_size;
    extern uint64_t __bss_size;
    extern uint64_t __heap_size;
    extern uint64_t __stack_size;

    printf("__start       = 0x%016lX \r\n", (uintptr_t)&__start);
    printf("__text_start  = 0x%016lX \r\n", (uintptr_t)&__text_start);
    printf("__text_end    = 0x%016lX \r\n", (uintptr_t)&__text_end);
    printf("__data_start  = 0x%016lX \r\n", (uintptr_t)&__data_start);
    printf("__data_end    = 0x%016lX \r\n", (uintptr_t)&__data_end);
    printf("__bss_start   = 0x%016lX \r\n", (uintptr_t)&__bss_start);
    printf("__bss_end     = 0x%016lX \r\n", (uintptr_t)&__bss_end);
    printf("__heap_start  = 0x%016lX \r\n", (uintptr_t)&__heap_start);
    printf("__heap_end    = 0x%016lX \r\n", (uintptr_t)&__heap_end);
    printf("__stack_start = 0x%016lX \r\n", (uintptr_t)&__stack_start);
    printf("__stack_end   = 0x%016lX \r\n", (uintptr_t)&__stack_end);
    printf("__end         = 0x%016lX \r\n", (uintptr_t)&__end);
    printf("__text_size   = 0x%016lX \r\n", (uintptr_t)&__text_size);
    printf("__data_size   = 0x%016lX \r\n", (uintptr_t)&__data_size);
    printf("__bss_size    = 0x%016lX \r\n", (uintptr_t)&__bss_size);
    printf("__heap_size   = 0x%016lX \r\n", (uintptr_t)&__heap_size);
    printf("__stack_size  = 0x%016lX \r\n", (uintptr_t)&__stack_size);
    printf("\r\n");
}

void print_pointer(void)
{
    static uint32_t svrv         = 0;
    uint32_t        avalv_noinit;
    uint32_t        avalv_init   = 0;
    uint32_t*       pvalv        = (uint32_t*)malloc(sizeof(uint32_t));

    printf("&svrv         = %p \r\n", &svrv);
    printf("&avalv_noinit = %p \r\n", &avalv_noinit);
    printf("&avalv_init   = %p \r\n", &avalv_init);
    printf("&pvalv        = %p \r\n", pvalv);
    printf("\r\n");

    free(pvalv);
}

extern uint32_t __get_vbar_el2();
extern uint32_t __get_hcr_el2();
extern uint32_t __get_elr_el2();
extern uint32_t __get_current_el();
extern uint32_t __get_current_sp();

static uint64_t hoge_r32(const uintptr_t addr)
{
    return *((volatile uint32_t*)addr);
}

void main(void)
{
    char cmd[128] = { 0 };

    hw_uart_puts("Hello baremetal. \r\n");
    hw_uart_puts("\r\n");

    printf("      hoge: 0x%016X \r\n", hoge_r32(BCM2837B0_AUX_MU_LSR_REG));
    printf("  vbar_el2: 0x%016X \r\n", __get_vbar_el2());
    printf("   hcr_el2: 0x%016X \r\n", __get_hcr_el2());
    printf("   elr_el2: 0x%016X \r\n", __get_elr_el2());
    printf("current_el: 0x%016X \r\n", __get_current_el());
    printf("current_sp: 0x%016X \r\n", __get_current_sp());

    // print_sizeof();
    // print_linker();
    // print_pointer();

    hw_uart_puts("Input 'menu' to show menu. \r\n");
    hw_uart_puts("> ");

    while (1)
    {
        int32_t len = 0;

        cmd[0] = '\0';
        len = _read(STDIN_FILENO, cmd, sizeof(cmd) - 1);

        if ((0 < len) && ((sizeof(cmd) - 1) > (uint32_t)len))
        {
            char* p = NULL;

            p = strchr(cmd, '\r');
            if (NULL != p) { *p = '\0'; }
            p = strchr(cmd, '\n');
            if (NULL != p) { *p = '\0'; }

            if (0 == strcmp(cmd, "reset"))
            {
                hw_reset();
            }

            else if (0 == strcmp(cmd, "menu"))
            {
                hw_uart_puts("menu: Show menu. \r\n");
                hw_uart_puts("reset: Reset board. \r\n");
            }

            else
            {
                hw_uart_puts("Unknown command \r\n");
                hw_uart_puts("Input 'menu' to show menu. \r\n");
            }

            hw_uart_puts("> ");
        }
    }
}
