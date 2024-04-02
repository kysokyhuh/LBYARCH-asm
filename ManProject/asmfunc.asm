section .data
vector_data dq 2.0

section .text
bits 64
default rel
global stencil_asm

stencil_asm:
    mov rsi, rdx       ; Save output pointer
    mov rdi, rcx       ; Save input pointer
    mov rcx, rax       ; Counter for loop iterations

    xor r8, r8         ; Initialize index for output array

loop_start:
    cmp r8, rcx        ; Compare loop counter with vector size
    jge loop_end       ; If counter exceeds size, jump to end

    movsd xmm0, [rdi + r8 * 8]  ; Load X[i] to xmm0
    movsd xmm1, [rdi + r8 * 8 + 8]  ; Load X[i + 1] to xmm1
    movsd xmm2, [rdi + r8 * 8 + 16] ; Load X[i + 2] to xmm2
    movsd xmm3, [rdi + r8 * 8 + 24] ; Load X[i + 3] to xmm3
    movsd xmm4, [rdi + r8 * 8 + 32] ; Load X[i + 4] to xmm4
    movsd xmm5, [rdi + r8 * 8 + 40] ; Load X[i + 5] to xmm5
    movsd xmm6, [rdi + r8 * 8 + 48] ; Load X[i + 6] to xmm6
    movsd xmm7, [rdi + r8 * 8 + 56] ; Load X[i + 7] to xmm7

    addsd xmm0, xmm1  ; Add xmm1 to xmm0
    addsd xmm0, xmm2  ; Add xmm2 to xmm0
    addsd xmm0, xmm3  ; Add xmm3 to xmm0
    addsd xmm0, xmm4  ; Add xmm4 to xmm0
    addsd xmm0, xmm5  ; Add xmm5 to xmm0
    addsd xmm0, xmm6  ; Add xmm6 to xmm0
    addsd xmm0, xmm7  ; Add xmm7 to xmm0

    
    movsd [rsi + r8 * 8], xmm0  ; Store the sum in output array

    inc r8           ; Increment index for storing result
    jmp loop_start      ; Repeat loop

loop_end:
    ret                 ; Return
