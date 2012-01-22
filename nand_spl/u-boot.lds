OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
 . = 0x00000000;
 . = ALIGN(4);
 .text :
 {
   start.o (.text)
   cpu_init.o (.text)
   nand_boot_s3c.o (.text)
   *(.text)
 }
 . = ALIGN(4);
 .rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }
 . = ALIGN(4);
 .data : {
  *(.data)
 __datarel_start = .;
  *(.data.rel)
 __datarelrolocal_start = .;
  *(.data.rel.ro.local)
 __datarellocal_start = .;
  *(.data.rel.local)
 __datarelro_start = .;
  *(.data.rel.ro)
 }
 . = ALIGN(4);
 __rel_dyn_start = .;
 .rel.dyn : { *(.rel.dyn) }
 __rel_dyn_end = .;
 __dynsym_start = .;
 .dynsym : { *(.dynsym) }
 . = .;
 __u_boot_cmd_start = .;
 .u_boot_cmd : { *(.u_boot_cmd) }
 __u_boot_cmd_end = .;
 . = ALIGN(4);
 __bss_start = .;
 .bss (NOLOAD) : { *(.bss) . = ALIGN(4); }
 _end = .;
 .bss __rel_dyn_start (OVERLAY) : {
  __bss_start = .;
  *(.bss)
  . = ALIGN(4);
  __bss_end__ = .;
 }
 /DISCARD/ : { *(.dynstr*) }
 /DISCARD/ : { *(.dynamic*) }
 /DISCARD/ : { *(.plt*) }
 /DISCARD/ : { *(.interp*) }
 /DISCARD/ : { *(.gnu*) }
}
