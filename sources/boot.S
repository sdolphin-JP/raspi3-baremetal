.section ".text.boot"

.globl __boot
__boot:

    // b __boot_el2
    b __boot_el1


__boot_el2:

    // set sp in EL1.
    ldr x20, =__stack_end
    msr sp_el1, x20

    // enable AArch64 in EL1.
    mov x20, #(1 << 31)         // AArch64
    orr x20, x20, #(1 << 1)     // SWIO hardwired on Pi3
    msr hcr_el2, x20

    // set vector address in EL1.
    // ldr x20, =__vector_table
    // msr vbar_el1, x20

    // change execution level to EL1.
    adr x20, __boot_el1
    msr elr_el2, x20
    mov x20, #0x5         // AARCH64_EL1H
    msr spsr_el2, x20
    eret


__boot_el1:

    // set sp
    ldr x20, =__stack_end
    mov sp, x20

    //
    // x0-31 and w0-w30 share the area.
    //  x0 - x30: 64bit general register
    //  w0 - w30: 32bit general register
    //
    // xzr: Always zero register.
    // wzr: Always zero register.
    //

    // clear bss.
    ldr  x20, =__bss_start
    ldr  w21, =__bss_size
1:  cbz  w21, 2f
    str  xzr, [x1], #8
    sub  w21, w21, #8
    cbnz w21, 1b
2:  nop

    // start main routine.
    bl main
    b  __hang


__hang:
    wfi
    b __hang
