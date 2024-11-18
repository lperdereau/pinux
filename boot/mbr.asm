;master boot record, 512 byte boot sector
[bits 16]

[org 0x7c00]


KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

call load_kernel
call switch_to_32bit

jmp $

%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/switch-to-32bit.asm"

[bits 16]
load_kernel:
	mov bx, KERNEL_OFFSET ; bx -> destination
	mov dh, 2             ; dh -> num sectors
    mov dl, [BOOT_DRIVE]  ; dl -> disk
    call disk_load
    ret

[bits 32]
BEGIN_32BIT:
	call KERNEL_OFFSET ; give control to kernel
    jmp $ ; loop in case kernel returns

BOOT_DRIVE db 0

times 510 - ($-$$) db 0
dw 0xaa55
