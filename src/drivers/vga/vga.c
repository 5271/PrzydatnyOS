/* This file is under BSD 3-Clause License and it's part of Iterkocze PrzydatnyOS
Copyright (c) 2021, Iterkocze-Company
All rights reserved. */

#include <stdint.h>
#include <stddef.h>

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4; //Robimy coś chyba takiego: fg = 01001001 bg = 00000000  po << ret = 01001010?
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
	{
		len++;
	}
	return len;
}
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) 
	{
		for (size_t x = 0; x < VGA_WIDTH; x++) 
		{
			const size_t index = y * VGA_WIDTH + x; 
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	if(c == '\n')
	{
		terminal_column = 0;
		terminal_row++;
		return;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) 
	{
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
		{
			terminal_row = 0;
		}
	}
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
	{
		terminal_putchar(data[i]);
	}
}
 
void kernel_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void add_newline()
{
	terminal_row++;
	terminal_column = 0;
}

static void clear()
{
	for (int i = 0; i<80; i++)
	{
		terminal_buffer[i] = 0;
	}

	for (int i = 0; i<25; i++)
	{
		terminal_buffer[i] = 0;
	}
}