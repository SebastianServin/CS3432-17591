#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>		 // malloc & free
#include <stdint.h>		 // use guaranteed 64-bit integers
#include "sservinLab1.h" // Create header file and reference thatm
#include "memory.h"		 // built-in functions to read and write to a specific file

int32_t *reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char *instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs()
{
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for (int i = 0; i < 32; i++)
		reg[i] = i;
}

// Checks if a string equals another
bool equals(char *strOne, char strTwo[])
{
	char *strTwoPointer = strTwo;
	for (; *strOne; strOne++)
	{
		if (*strOne != *strTwoPointer)
		{
			return false;
		}
		strTwoPointer++;
	}

	return true;
}

// Returns an int based on what the string is.
int customSwitch(char *str)
{

	if (equals(str, "LW"))
		return 1;
	if (equals(str, "SW"))
		return 2;
	if (equals(str, "ADD"))
		return 3;
	if (equals(str, "ADDI"))
		return 4;
	if (equals(str, "AND"))
		return 5;
	if (equals(str, "OR"))
		return 6;
	if (equals(str, "XOR"))
		return 7;

	return -1;
}

void addi(char **tokens)
{
	// Loops through string to get the number where addition will be stored.
	int32_t store_in = -1;
	char *to_store_in_pointer = *tokens;
	to_store_in_pointer++;
	for (; *to_store_in_pointer; to_store_in_pointer++)
	{
		if (store_in == -1)
		{
			store_in = *to_store_in_pointer - '0';
		}
		else
		{
			store_in = store_in * 10;
			store_in = store_in + (*to_store_in_pointer - '0');
		}
	}

	// Loops through string to get the first nunmber which will be added.
	tokens++;
	int32_t add_one = -1;
	char *add_one_pointer = *tokens;
	add_one_pointer++;
	for (; *add_one_pointer; add_one_pointer++)
	{
		if (add_one == -1)
		{
			add_one = *add_one_pointer - '0';
		}
		else
		{
			add_one = add_one * 10;
			add_one = add_one + (*add_one_pointer - '0');
		}
	}

	// Loops through string to get the second number which will be added.
	tokens++;
	bool negative = false;
	int32_t add_two = -1;
	char *add_two_pointer = *tokens;
	if (*add_two_pointer == '-')
	{
		add_two_pointer++;
		negative = true;
	}
	for (; *add_two_pointer; add_two_pointer++)
	{
		if (*add_two_pointer == '\n' || *add_two_pointer == '\0')
		{
			break;
		}
		if (add_two == -1)
		{
			add_two = *add_two_pointer - '0';
		}
		else
		{
			add_two = add_two * 10;
			add_two = add_two + (*add_two_pointer - '0');
		}
	}

	// Checks if number is negative
	if (negative)
	{
		add_two = add_two * -1;
	}
	reg[store_in] = reg[add_one] + add_two;
}

void add(char **tokens)
{
	// Loops through string to get the number where addition will be stored.
	int32_t store_in = -1;
	char *to_store_in_pointer = *tokens;
	to_store_in_pointer++;
	for (; *to_store_in_pointer; to_store_in_pointer++)
	{
		if (store_in == -1)
		{
			store_in = *to_store_in_pointer - '0';
		}
		else
		{
			store_in = store_in * 10;
			store_in = store_in + (*to_store_in_pointer - '0');
		}
	}

	// Loops through string to get the first number which will be added.
	tokens++;
	int32_t add_one = -1;
	char *add_one_pointer = *tokens;
	add_one_pointer++;
	for (; *add_one_pointer; add_one_pointer++)
	{
		if (add_one == -1)
		{
			add_one = *add_one_pointer - '0';
		}
		else
		{
			add_one = add_one * 10;
			add_one = add_one + (*add_one_pointer - '0');
		}
	}

	// Loops through string to get the second number which will be added.
	tokens++;
	int32_t add_two = -1;
	char *add_two_pointer = *tokens;
	add_two_pointer++;

	for (; *add_two_pointer; add_two_pointer++)
	{
		if (*add_two_pointer == '\n' || *add_two_pointer == '\0')
		{
			break;
		}
		if (add_two == -1)
		{
			add_two = *add_two_pointer - '0';
		}
		else
		{
			add_two = add_two * 10;
			add_two = add_two + (*add_two_pointer - '0');
		}
	}

	reg[store_in] = reg[add_one] + reg[add_two];
}

void sw(char **tokens)
{
	// Loops through string to get the number where info will be read from.
	char *mem_file = "mem.txt";
	int32_t get_from = -1;
	char *get_from_pointer = *tokens;
	get_from_pointer++;
	for (; *get_from_pointer; get_from_pointer++)
	{
		if (get_from == -1)
		{
			get_from = *get_from_pointer - '0';
		}
		else
		{
			get_from = get_from * 10;
			get_from = get_from + (*get_from_pointer - '0');
		}
	}
	tokens++;

	bool negative = false;
	bool offset_initialized = false;
	int32_t offset;
	char *offset_pointer = *tokens;

	// Loops through string to get offset

	if (*offset_pointer == '-')
	{
		negative = true;
		offset_pointer++;
	}
	for (; *offset_pointer; offset_pointer++)
	{
		if (*offset_pointer == '(')
		{
			break;
		}
		if (!offset_initialized)
		{
			offset_initialized = true;
			offset = *offset_pointer - '0';
		}
		else
		{
			offset = offset * 10;
			offset = offset + (*offset_pointer - '0');
		}
	}

	if (negative)
	{
		offset = offset * -1;
	}

	offset_pointer++;

	bool memory_address_initialized = false;
	int32_t memory_address;

	// Loops through string to get memory address.
	for (; *offset_pointer; offset_pointer++)
	{
		if (*offset_pointer == ')')
		{
			break;
		}
		if (!memory_address_initialized)
		{
			memory_address_initialized = true;
			memory_address = *offset_pointer - '0';
		}
		else
		{
			memory_address = memory_address * 10;
			memory_address = memory_address + (*offset_pointer - '0');
		}
	}

	int32_t store_in = offset + memory_address;

	int32_t data_to_write = reg[get_from];

	int32_t write = write_address(data_to_write, store_in, mem_file);
	if (write == (int32_t)NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
}

void lw(char **tokens)
{
	// Loops through string to get the number where info will be stored.
	char *mem_file = "mem.txt";
	int32_t store_in = -1;
	char *to_store_in_pointer = *tokens;
	to_store_in_pointer++;
	for (; *to_store_in_pointer; to_store_in_pointer++)
	{
		if (store_in == -1)
		{
			store_in = *to_store_in_pointer - '0';
		}
		else
		{
			store_in = store_in * 10;
			store_in = store_in + (*to_store_in_pointer - '0');
		}
	}
	tokens++;

	// Loops through string to get offset
	bool offset_initialized = false;
	bool negative = false;
	int32_t offset;
	char *offset_pointer = *tokens;

	if (*offset_pointer == '-')
	{
		negative = true;
		offset_pointer++;
	}
	for (; *offset_pointer; offset_pointer++)
	{
		if (*offset_pointer == '(')
		{
			break;
		}
		if (!offset_initialized)
		{
			offset_initialized = true;
			offset = *offset_pointer - '0';
		}
		else
		{
			offset = offset * 10;
			offset = offset + (*offset_pointer - '0');
		}
	}

	if (negative)
	{
		offset = offset * -1;
	}

	offset_pointer++;

	// Loops through string to get memory address.
	bool memory_address_initializd = false;
	int32_t memory_address;

	for (; *offset_pointer; offset_pointer++)
	{
		if (*offset_pointer == ')')
		{
			break;
		}
		if (!memory_address_initializd)
		{
			memory_address_initializd = true;
			memory_address = *offset_pointer - '0';
		}
		else
		{
			memory_address = memory_address * 10;
			memory_address = memory_address + (*offset_pointer - '0');
		}
	}

	int32_t get_from = offset + memory_address;
	int32_t read = read_address(get_from, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", get_from, get_from, read, read); // %lu -> format as an long-unsigned
	reg[store_in] = read;
}
/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char *instr)
{
	char **tokens;
	tokens = tokenize(instr);
	int expressionInt = customSwitch(*tokens);
	tokens++;

	/*
	1 -> LW
	2 -> SW
	3 -> ADD
	4 -> ADDI
	5 -> AND
	6 -> OR
	7 -> XOR
	*/
	switch (expressionInt)
	{
	case 1:
		lw(tokens);
		break;

	case 2:
		sw(tokens);
		break;

	case 3:
		add(tokens);
		break;

	case 4:
		addi(tokens);
		break;

	case 5:
		printf("AND \n");
		break;

	case 6:
		printf("OR \n");
		break;
	case 7:
		printf("XOR \n");
		break;

	default:
		printf("NO INSTRUCTION FOUND \n");
		break;
	}

	return true;
}

/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo()
{
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98;		   // equal to 152
	char *mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if (write == (int32_t)NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

void print_regs()
{
	int col_size = 10;
	for (int i = 0; i < 8; i++)
	{
		printf("X%02i:%.*lld", i, col_size, (long long int)reg[i]);
		printf(" X%02i:%.*lld", i + 8, col_size, (long long int)reg[i + 8]);
		printf(" X%02i:%.*lld", i + 16, col_size, (long long int)reg[i + 16]);
		printf(" X%02i:%.*lld\n", i + 24, col_size, (long long int)reg[i + 24]);
	}
}

/**
 * Your code goes in the main
 *
 */
int main()
{
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();

	printf("RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\n Please enter all numbers in decimal fomtat.\n Enter 'EOF' character to end program\n");

	char *instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while (!is_null)
	{
		interpret(instruction);
		printf("\n");
		print_regs();
		printf("\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}
