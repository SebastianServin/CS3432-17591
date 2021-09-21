#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c)
{
   if (c == ' ' || c == '\t')
   {
      return true;
   }

   return false;
}

// counts the number of words or tokens
int count_tokens(char *str)
{
   int count = 0;
   for (char c = *str; c; c = *++str)
   {
      // Adds one if the character is a space.
      if (delim_character(c))
      {
         count++;
      }
   }

   return count;
}

// Gets the length of a token (finish - start) and copies it from the original string to the new one.
char *copy_str(char *inStr, int start, int finish)
{
   char *toReturn = (char *)malloc((finish - start) * sizeof(char));

   int length = finish - start; 
   int index = start;
   for (int i = 0; i < length; i++) {
      toReturn[i] = inStr[index];
      index++;
   }
   return toReturn;
}


// Loops through string, finds where a token ends and copies it into a new variable.
// New string is then assigned to the double pointer.
char **tokenize(char *str)
{
   int numberOfTokens = count_tokens(str);
   int c = 0;
   char **words = (char **)malloc(numberOfTokens * sizeof(char *));
   int count = 0;
   int start = 0;
   int finish = 0;
   for (int i = 0; i < strlen(str); i++)
   {
      if (delim_character(str[i]) && i != strlen(str) - 1)
      {
         finish = count;
         char *temp = (char *)malloc((finish - start) * sizeof(char));
         temp = copy_str(str, start, finish);
         start = count + 1;
         words[c] = temp;
         ++c;
      }
      ++count;
   }


   // Copy last token here
   finish = count;
   char *temp = (char *)malloc((finish - start) * sizeof(char));
   temp = copy_str(str, start, finish);
   start = count;
   words[c] = temp;

   return words;
}

// Loops through double pointer and prints tokens.
void print_all_tokens(char **tokens)
{
   int count = 0;
   for (; *tokens; *tokens++) {
      printf("Tokens[%i]: ", count);
      printf("%s\n", *tokens);
      count++;
   }
}

int main()
{
   printf("Please enter the input string: ");
   char str[10000];
   gets(str);
   char *pointerStr = str;
   int numberOfTokens = count_tokens(pointerStr);
   char **tokens = (char **)malloc((numberOfTokens) * sizeof(char));
   print_all_tokens(tokenize(pointerStr));
}