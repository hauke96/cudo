#include<stdio.h>

void print_binary_file
(
	char *src_buffer_original,
	char *src_buffer_to_compare,
	long amount_chars_to_compare,
	char *dest_buffer
);

void run_comparison
(
	char *input_file_1,
	char *input_file_2,
	char *output_file
);
