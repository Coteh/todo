#include "CLIHelpers.h"
#include <stdio.h>
#include <string.h>

int get_line(char *buffer, int bsize) {
	int ch, len;

	fgets(buffer, bsize, stdin);

	/* remove unwanted characters from the buffer */
	buffer[strcspn(buffer, "\r\n")] = '\0';

	len = strlen(buffer);

	/* clean input buffer if needed */
	if (len == bsize - 1)
	while ((ch = getchar()) != '\n' && ch != EOF);

	return len;
}

void clearInput(){
	fseek(stdin, 0, SEEK_END);
}
