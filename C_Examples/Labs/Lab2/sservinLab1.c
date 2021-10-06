#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c)
{
   if (c == ' ' || c == '\t' || c == '\0')
   {
      return true;
   }

   return false;
}

/* Returns a pointer to the first character of the next
   space-separated word*/
char *word_start(char *str)
{
   while (delim_character(*str))
   {
      *str++;
   }
   return str;
}

char *delete_word(char *str)
{
   while (!delim_character(*str)) {
      *str++;
   }

   return str;
}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char *str)
{
}

// Counts the number of words or tokens
int count_tokens(char *str)
{
   int count = 0;
   bool wordDetected = false;
   for(; *str; *str++) {
      if (!delim_character(*str) && !wordDetected) {
         wordDetected = true;
         count++;
      }
      if (delim_character(*str) && wordDetected) {
         wordDetected = false;
      }
   }

   return count;
}

// Gets the length of a token (finish - start) and copies it from the original string to the new one.
char *copy_str(char *inStr, int length)
{
   char *toReturn = (char *)malloc(length * sizeof(char));
   int index = 0;
   for (int i = 0; i < length; i++)
   {
      toReturn[i] = inStr[index];
      index++;
   }
   return toReturn;
}

// Loops through string, finds where a token ends and copies it into a new variable.
// New string is then assigned to the double pointer.
char **tokenize(char *str)
{
   char *numberOfTokensToCount = str;
   int numberOfTokens = count_tokens(numberOfTokensToCount);
   int c = 0;
   char **words = (char **)malloc(numberOfTokens * sizeof(char *));
   int count = 0;
   int start = 0;
   int finish = -1;

   str = word_start(str);
   while (c != numberOfTokens)
   {
      if (delim_character(str[count]))
      {
         char *temp = (char *)malloc((count) * sizeof(char));
         temp = copy_str(str, count);
         words[c] = temp;
         count = -1;
         c++;
         str = delete_word(str);
         str = word_start(str);
      }
      count++;
   }
   return words;
}

// Loops through double pointer and prints tokens.
void print_all_tokens(char **tokens)
{
   int count = 0;
   for (; *tokens; *tokens++)
   {
      printf("Tokens[%i]: ", count);
      printf("%s\n", *tokens);
      count++;
   }
}

// int main()
// {
//    char str[] = "ADD X146 X5 X15";
//    char *pointerToCount = str;
//    int numberOfTokens = count_tokens(pointerToCount);
//    char *pointerStr = str;
//    // char **tokens = (char **)malloc((numberOfTokens) * sizeof(char));
//    // char **tokens = tokenize(pointerStr);
//    // print_all_tokens(tokenize(pointerStr));
// }