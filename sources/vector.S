.section ".vectors"

.globl __vector_table
__vector_table:

    .set VBAR, __vector_table

    /* Synchronous / Current EL with SP0 */
    .org VBAR
        b .

    /* IRQ/vIRQ / Current EL with SP0 */
    .org (VBAR + 0x80)
        b .

    /* FIQ/vFRQ / Current EL with SP0 */
    .org (VBAR + 0x100)
        b .

    /* SError/vSError / Current EL with SP0 */
    .org (VBAR + 0x180)
        b .


    /* Synchronous / Current EL with SPx */
    .org (VBAR + 0x200)
        b .

    /* IRQ/vIRQ / Current EL with SPx */
    .org (VBAR + 0x280)
        b .

    /* FIQ/vFRQ / Current EL with SPx */
    .org (VBAR + 0x300)
        b .

    /* SError/vSError / Current EL with SPx */
    .org (VBAR + 0x380)
        b .


    /* Synchronous / Lower EL using AArch64 */
    .org (VBAR + 0x400)
        b .

    /* IRQ/vIRQ / Lower EL using AArch64 */
    .org (VBAR + 0x480)
        b .

    /* FIQ/vFRQ / Lower EL using AArch64 */
    .org (VBAR + 0x500)
        b .

    /* SError/vSError / Lower EL using AArch64 */
    .org (VBAR + 0x580)
        b .


    /* Synchronous / Lower EL using AArch32 */
    .org (VBAR + 0x600)
        b .

    /* IRQ/vIRQ / Lower EL using AArch32 */
    .org (VBAR + 0x680)
        b .

    /* FIQ/vFRQ / Lower EL using AArch32 */
    .org (VBAR + 0x700)
        b .

    /* SError/vSError / Lower EL using AArch32 */
    .org (VBAR + 0x780)
        b .
