#include<stdio.h>
#include<string.h>

#include "cudo.h"
#include "io.h"

#define DEBUG

#ifdef DEBUG
	#define debug(format) printf(format);
#else
	#define debug(format)
#endif

void print_binary_file(char *src_buffer_original, char *src_buffer_to_compare, long amount_chars_to_compare, char *dest_buffer)
{
	for (int i = 0; i < amount_chars_to_compare; i++)
	{
		dest_buffer[i] = src_buffer_original[i] ^ src_buffer_to_compare[i];
	}
}

void run_comparison(char *input_file_1, char *input_file_2, char *output_file)
{
	char *buffer[2];
	long  filelen[2];
	char *dest_buffer;
	long  dest_file_len;		// length of the longest file
	long  amount_chars_to_compare;

	read_from_file(input_file_1, &buffer[0], &filelen[0]);
	read_from_file(input_file_2, &buffer[1], &filelen[1]);

	if(filelen[0] > filelen[1])
	{
		dest_file_len = filelen[0];
		dest_buffer = buffer[0];
		amount_chars_to_compare = filelen[1];
	}
	else
	{
		dest_file_len = filelen[1];
		dest_buffer = buffer[1];
		amount_chars_to_compare = filelen[0];
	}

	print_binary_file(buffer[0], buffer[1], amount_chars_to_compare, dest_buffer);

	write_to_file(output_file, dest_buffer, dest_file_len);
}

int main (int argc, char **argv)
{
	 /* We check !=4 because argument 0 is the path of the application  */
	if (argc != 4)
	{
		printf("%s\n\n%s\n%s\n%s\n",
			"There must be exactly three arguments",
			"	original file path",
			"	file to compare",
			"	output file");
		return 1;
	}

	run_comparison(argv[1], argv[2], argv[3]);

	return 0;
}
