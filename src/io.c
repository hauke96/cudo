#include<stdlib.h>
#include<stdio.h>

#include "io.h"

void read_from_file(char* file_name, char** buffer, long* file_len)
{
	FILE *file_ptr;

	file_ptr = fopen(file_name, "rb"); 	// Open the file in binary mode
	fseek(file_ptr, 0, SEEK_END);		// Jump to the end of the file
	*file_len = ftell(file_ptr);		// Get the current byte offset in file
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
