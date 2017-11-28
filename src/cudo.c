#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "cudo.h"

#define DEBUG

#ifdef DEBUG
	#define debug(format) printf(format);
#else
	#define debug(format)
#endif

//TODO change names like filelen to file_len or something similar
void read_from_file(char* file_name, char** buffer, long* file_len)
{
	FILE *file_ptr;

	file_ptr = fopen(file_name, "rb"); 	// Open the file in binary mode
	fseek(file_ptr, 0, SEEK_END);		// Jump to the end of the file
	*file_len = ftell(file_ptr);			// Get the current byte offset in file
	rewind(file_ptr);					// Jump back to the beginning

	*buffer = (char *)calloc(*file_len + 1, sizeof(char)); // file length + \0
	fread(*buffer, sizeof(char), *file_len, file_ptr); // Read in the entire file
	fclose(file_ptr); // Close the file
}

void write_to_file(char *file_name, char *buffer, long file_len)
{
	FILE *file_ptr;

	file_ptr = fopen(file_name, "w");
	fwrite(buffer, sizeof(char), file_len, file_ptr);
	//TODO check error flag

	fclose(file_ptr);
}

void print_binary_file(char *filename_1, char *filename_2, char *output_file)
{
	char *buffer[2];
	long  filelen[2];
	char *dest_buffer;
	long  dest_filelen;		// length of the longest file

 	//TODO consider to extract the read-calls
	read_from_file(filename_1, &buffer[0], &filelen[0]);
	read_from_file(filename_2, &buffer[1], &filelen[1]);

	dest_filelen = filelen[0] > filelen[1] ? filelen[0] : filelen[1];

	dest_buffer = calloc(dest_filelen, sizeof(char));
	memcpy(dest_buffer, buffer[0], filelen[0]);

	for (int i = 0; i < filelen[1]; i++)
	{
		if (i < dest_filelen)
		{
			dest_buffer[i] ^= buffer[1][i];
		}
	}

	write_to_file(output_file, dest_buffer, dest_filelen);
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

	print_binary_file(argv[1], argv[2], argv[3]);

	return 0;
}
