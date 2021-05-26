bits 32
section .text
; multiboot header
        align 4
        dd 0x1BADB002            ;magic
        dd 0x00                  ;flags
        dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

global start
extern kmain

start:
    lgdt [gdtr]                 ; Load our own GDT, the GDTR of Grub may be invalid

    jmp CODE32_SEL:.setcs       ; Set CS to our 32-bit flat code selector
.setcs:
    mov ax, DATA32_SEL          ; Setup the segment registers with our flat data selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, stack_space        ; set stack pointer

    call kmain

; If we get here just enter an infinite loop
endloop:
    hlt                         ; halt the CPU
    jmp endloop

; Macro to build a GDT descriptor entry
%define MAKE_GDT_DESC(base, limit, access, flags) \
    (((base & 0x00FFFFFF) << 16) | \
    ((base & 0xFF000000) << 32) | \
    (limit & 0x0000FFFF) | \
    ((limit & 0x000F0000) << 32) | \
    ((access & 0xFF) << 40) | \
    ((flags & 0x0F) << 52))

section .data
align 4
gdt_start:
    dq MAKE_GDT_DESC(0, 0, 0, 0); null descriptor
gdt32_code:
    dq MAKE_GDT_DESC(0, 0x00ffffff, 10011010b, 1100b)
                                ; 32-bit code, 4kb gran, limit 0xffffffff bytes, base=0
gdt32_data:
    dq MAKE_GDT_DESC(0, 0x00ffffff, 10010010b, 1100b)
                                ; 32-bit data, 4kb gran, limit 0xffffffff bytes, base=0
end_of_gdt:

gdtr:
    dw end_of_gdt - gdt_start - 1
                                ; limit (Size of GDT - 1)
    dd gdt_start                ; base of GDT

CODE32_SEL equ gdt32_code - gdt_start
DATA32_SEL equ gdt32_data - gdt_start

section .bss
resb 8192                       ; 8KB for stack
stack_space: