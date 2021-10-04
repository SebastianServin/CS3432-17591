#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>	   // malloc & free
#include <stdint.h>	   // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h"	   // built-in functions to read and write to a specific file

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

bool equals(char *strOne, char strTwo[])
{
	char *strTwoPointer = strTwo;
	for (; *strOne; *strOne++)
	{
		if (*strOne != *strTwoPointer)
		{
			return false;
		}
		*strTwoPointer++;
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
}

void addi(char *tokens)
{
	*tokens++;
	int store_in = atoi(tokens);

	tokens = strtok(NULL, " ");
	*tokens++;
	int register_one = atoi(tokens);

	tokens = strtok(NULL, " ");
	int number = atoi(tokens);

	reg[store_in] = reg[register_one] + number;
}

void add(char *tokens)
{
	*tokens++;
	int store_in = atoi(tokens);

	tokens = strtok(NULL, " ");
	*tokens++;
	int register_one = atoi(tokens);

	tokens = strtok(NULL, " ");
	*tokens++;
	int register_two = atoi(tokens);

	reg[store_in] = reg[register_one] + reg[register_two];
}

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char *instr)
{

	char *tokens;
	tokens = strtok(instr, " ");
	int expressionInt = customSwitch(tokens);

	tokens = strtok(NULL, " ");

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
		printf("LW \n");
		break;

	case 2:
		printf("SW \n");
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
	for (int i = 0; i < 32; i++)
	{
		printf("Memory X%i: %i\n", i, reg[i]);
	}
}

/**
 * Your code goes in the main
 *
 */
int main()
{
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER

	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	// Below is a sample program to a write-read. Overwrite this with your own code.
	// write_read_demo();
	char s[] = "ADDI X16 X5 15";
	char *p = s;
	print_regs();
	printf("\n");
	printf("\n");
	interpret(p);
	print_regs();

	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	// CHANGE TOKENIZER
	return 0;
}
