#include <stdio.h>
#include <stdlib.h>

/* If we are compiling on WIndows compile these functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

void add_history(char* unused) {}

/* Otherwise include the editline headers */
/* I think this will only work on Mac */
#else
#include <editline/readline.h>
#ifdef __linux__
#include <editline/history.h>
#endif
#endif

int main(int argc, char** argv) {
  /* Print Version and Exit Information */
  puts("Krisp Version 0.2.2");
  puts("Press Ctrl+c to Exit\n");

  /* In a never ending loop */
  while (1) {
    /* Output our prompt and get input */
    char* input = readline("krisp> ");

    /* Add input to history */
    add_history(input);

    /* Echo input back to user */
    printf("No you're a %s\n", input);

    /* Free retrieved input */
    free(input);
  }

  return 0;
}
