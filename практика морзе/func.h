#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define SIZE_NAME_FILE 128
#define MAX_SIZE 512
#define ANSI_COLOR_RED     "\x1b[1;31m"
#define ANSI_COLOR_YELLOW    "\x1b[1;33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void flash_morz(char* str);
void run_program();
void choose_file_option(char* filename, bool* file_exists);
void convert_text_to_morse(char* str, char* filename, bool file_exists);
void display_file_contents(char* filename, bool file_exists);
int input_case();
void morse_file_to_str(char* filename, bool file_exists);
char* str_to_morse(const char* str);
char* morse_to_str(const char* morse);

