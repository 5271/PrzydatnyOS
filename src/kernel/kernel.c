/* This file is under BSD 3-Clause License and it's part of Iterkocze PrzydatnyOS
Copyright (c) 2021, Iterkocze-Company
All rights reserved. */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../utility/strcmp/include/strcmp.h"
#include "../drivers/io/include/io.h"
#include "../drivers/vga/include/vga.h"
#include "../drivers/keyboard/include/keyboard.h"

#include "../drivers/io/io.c"
#include "../drivers/vga/vga.c"
#include "../drivers/keyboard/keyboard.c"
#include "../utility/etc/cmd.c"
#include "../utility/strcmp/strcmp.c"

void kernel_main(void) 
{
	terminal_initialize();
	cmd_init();
	kernel_writestring("Witaj w systemie PrzydatnyOS!\n");
	kernel_writestring("> ");
	cmd_handler();
}