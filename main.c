#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "extended_io.h"

int main(void)
{
	char * data = "movi reg0, #10";
	char ** words;
	int num_of_words = 0;
	int num_of_frees = 0;
	words = get_words_from_string(data, &num_of_words, &num_of_frees);

	for(int i = 0; i < num_of_words; i++)
	{
		printf("%s\n", words[i]);
	}
	int length_1 = strlen(words[0]);
	int length_2 = strlen(words[2]);
	printf("%d\t%d\n", length_1, length_2);
    return 0;
}
