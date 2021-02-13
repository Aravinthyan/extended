// standard header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// created header files
#include "extended_io.h"

void *xmalloc(size_t size)
{
    void *data = malloc(size);

    // if the requested data is not given in other words returned NULL exit
    if (data == NULL)
    {
        fprintf(stderr, "virtual memory exhausted");
        exit(-1);
    }

    // return the data variable
    return data;
}

void *xrealloc(void *ptr, size_t size)
{
    void *data = realloc(ptr, size);

    // if the requested data is not given in other words returned NULL exit
    if (data == NULL)
    {
        fprintf(stderr, "virtual memory exhausted");
        exit(-1);
    }

    // return the data variable
    return data;
}

char *read_variable_string_from_stdin(void)
{
    // varaible to hold the size of string
    unsigned int amount = 0;

    // create a dynamic string of size/length 5
    char *data = (char *)xmalloc(5 * sizeof(char));

    // amount characters filled in string
    unsigned int filled = 0;

    // get an input character
    char input = (char)getchar();

    /* provided the input character is not a new line and it is not EOF continue
    reading */
    while (input != '\n' && input != EOF)
    {
        /* if filled is equal to amount, and there is still more to read then
        resize the string size in heap */
        if (filled == amount)
        {
            amount += 5;
            // create a new string of this size
            data = (char *)xrealloc((void *)data, amount * sizeof(char));
        }
        // equate current position in the character array to input read
        data[filled] = input;
        input = (char)getchar();
        filled++;
    }
    // place null terminator to end string
    data[filled] = '\0';

    // return read string
    return data;
}

char *get_all_data_file(const char *filename)
{
    // open file to get data
    FILE *input_file = fopen(filename, "r");

    if (input_file == NULL)
    {
        fprintf(stderr, "Couldn't open file %s\n", filename);
    }

    // varaible to hold the size of string
    unsigned int amount = 0;

    // create a dynamic string of size/length 5
    char *data = (char *)xmalloc(5 * sizeof(char));

    // amount characters filled in string
    unsigned int filled = 0;

    // get an input character
    char input = (char)fgetc(input_file);

    /* provided the input character is not a new line and it is not EOF continue
    reading */
    while (input != EOF)
    {
        /* if filled is equal to amount, and there is still more to read then
        resize the string size in heap */
        if (filled == amount)
        {
            amount += 5;
            // create a new string of this size
            data = (char *)xrealloc((void *)data, amount * sizeof(char));
        }
        // equate current position in the character array to input read
        data[filled] = input;
        input = (char)fgetc(input_file);
        filled++;
    }
    // place null terminator to end string
    data[filled] = '\0';

    return data;
}

char **get_words_from_string(const char *input_string, int *num_of_words, 
                             int *num_of_frees)
{
    // amount holds the number of words that can be taken from string
    // intialy 5
    unsigned int amount = 5;

    // start with asumming that there are 5 words in the string
    char **words = (char **)xmalloc(amount * sizeof(char *));

    // this is the defualt size of each word
    unsigned int word_size = 5;

    // allocate each word size as 5 as default
    for (int i = 0; i < amount; i++)
    {
        words[i] = (char *)xmalloc(word_size * sizeof(char));
    }

    // this is used to go through the string
    unsigned int index = 0;
    /* this is used to see how many words of the allocated amount has actually
    been filled */
    unsigned int amount_level = 0;
    // this is used to see how many characters have been filled
    unsigned int word_size_level = 0;

    // this is a flag used to see if the end of a word has been reached
    char clean = 0;

    // until space or \n or tab is not reached
    while(input_string[index] == ' ' || input_string[index] == '\n' 
                                                    || input_string[index] == 9)
    {
        // increment index to skip ' ' or '\n'
        index++;
    }

    while(input_string[index] != '\0')
    {
        if(word_size_level == word_size)
        {
            word_size += 5;
            // create a new string of this size
            words[amount_level] = (char *)xrealloc((void *)words[amount_level], 
                                                    word_size * sizeof(char));
        }

        // until space or \n or tab is not reached
        while(input_string[index] == ' ' || input_string[index] == '\n' 
                                                    || input_string[index] == 9)
        {
            // increment index to skip ' ' or '\n'
            index++;
            clean = 1;
        }

        if(clean == 1)
        {
            // place null terminator at the end of string
            words[amount_level][word_size_level] = '\0';
            // reset flag
            word_size_level = 0;

            //amount_levelincrement for the next string
            amount_level++;
            
            /* if the amount filled is the same as the max available then 
            increase */
            if(amount_level == amount)
            {
                // create a temp variable of char **
                char ** temp = (char **)xmalloc((amount + 5) * sizeof(char *));

                // create space for each word
                for(int i = 0; i < amount + 5; i++)
                {
                    // this for the old data to be copied over so strlen used
                    if(i < amount)
                    {
                        temp[i] = (char *)xmalloc((strlen(words[i]) + 1) 
                                                   * sizeof(char));
                    }
                    else    // this is for new data so default word_size
                    {
                        temp[i] = (char *)xmalloc(word_size * sizeof(char));
                    }
                }

                // copy old data over
                for(int i = 0; i < amount; i++)
                {
                    strcpy(temp[i], words[i]);
                }

                // clear old data
                for(int i = 0; i < amount; i++)
                {
                    free(words[i]);
                }

                // clear words
                free(words);

                // assign words to the newly created memory
                words = temp;
                // NULL the inital pointer pointing to the newly created memory
                temp = NULL;
                // increment the total number of words for comparison next time
                amount += 5;
            }

            // reset flag such next time a space, \n or tab is reached
            clean = 0;
        }

        // assign current character
        words[amount_level][word_size_level] = input_string[index];

        // increment track and index for next character
        word_size_level++;
        index++;
    }

    // place \0 for last one
    words[amount_level][word_size_level] = '\0';

    // assign the num_of_words and num_of_frees for use of printing and freeing
    *num_of_words = amount_level + 1;
    *num_of_frees = amount;

    // return words
    return words;
}

char *get_string(string_manipulation *data)
{
    // return the address held by the string field
    return data->string;
}

void set_string(string_manipulation *data, char *string)
{
    // set the address of string field to address of string
    data->string = string;
}

void free_words(string_manipulation *data)
{
    // use the num_of_frees field to exactly free the correct amount of memory
    for (int i = 0; i < data->num_of_frees; i++)
    {
        free(data->words[i]);
    }
    // free word
    free(data->words);
}

void free_string(string_manipulation *data)
{
    // free string allocated
    free(data->string);
}

string_manipulation * free_string_manipulation(string_manipulation *data)
{
    // free data
    free(data);
    return NULL;
}

string_manipulation *free_all_string_manipulation(string_manipulation *data)
{
    // call other functions and free all dynamically allocated fields
    free_string(data);
    free_words(data);
    data = free_string_manipulation(data);
    return data;
}

void seperate_words_from_string(string_manipulation *data)
{
    // call get_words_from_string to seperate out the words in the string
    data->words = get_words_from_string(data->string, &(data->num_of_words),
                                        &(data->num_of_frees));
}

// create_int_array
int_array * create_int_array(void)
{
    int_array * array = (int_array *)xmalloc(sizeof(int_array));
    array->data = NULL;
    array->total = 0;
    array->min = 0;
    array->max = 0;
    array->mean = 0;
    array->variance = 0;
    return array;
}

// read_int_array
void read_int_array(int_array * array, unsigned long long int length)
{
    // if previous array exists
    if(array->data != NULL)
    {
        free(array->data);
    }
    // set the total number of elements
    array->total = length;
    // create the memory required to hold the data
    array->data = (int *)xmalloc(length * sizeof(int));

    for(int i = 0; i < array->total; i++)
    {
        scanf("%d", &(array->data[i]));
    }
}

void increase_int_array(int_array * array, unsigned long long int length)
{
    array->data = (int *)xrealloc((void *)array->data, length);
    for(unsigned long long int i = array->total - 1; i < length; i++)
    {
        array->data[i] = 0;
    }
    array->total = length;
}

int_array * sub_set_int_array(int_array * array, unsigned long long int min,
                              unsigned long long int max)
{
    unsigned long long int range = max - min;
    range++;
    int_array * sub_array = (int_array *)xmalloc(sizeof(int_array));
    sub_array->data = (int *)xmalloc(sizeof(int));
    sub_array->total = range;
    int offset = min - 1;
    for(unsigned long long int i = min - 1; i <= max; i++)
    {
        sub_array->data[i - offset] = array->data[i];
    }
    return sub_array;
}

// print_int_array
void print_int_array(int_array * array)
{
    for(int i = 0; i < array->total; i++)
    {
        printf("%d\n", array->data[i]);
    }
}

// find_min
void find_min(int_array * array)
{
    // set the minimum to the 1st element in the array
    array->min = array->data[0];
    
    // go through the remaining and find the min
    for(unsigned long long int i = 1; i < array->total; i++)
    {
        // if the current data is less than the set minimum
        if(array->data[i] < array->min)
        {
            array->min = array->data[i];
        }
    }
}

// find_max
void find_max(int_array * array)
{
    // set the maximum to the 1st element in the array
    array->max = array->data[0];
    
    // go through the remaining and find the max
    for(unsigned long long int i = 1; i < array->total; i++)
    {
        // if the current data is greater than the set maximum
        if(array->data[i] > array->max)
        {
            array->max = array->data[i];
        }
    }
}

// sort_min_to_max
void sort_min_to_max(int_array * array)
{
    for(unsigned long long int i = 0; i < array->total - 1; i++)       
    {   
        for(unsigned long long int j = 0; j < array->total - i - 1; j++)  
        { 
            if(array->data[j] > array->data[j+1]) 
            {
                int tmp = array->data[j];
                array->data[j] = array->data[j+1];
                array->data[j+1] = tmp; 
            }
        }
    }
}

// sort_max_to_min
void sort_max_to_min(int_array * array)
{
    for(unsigned long long int i = 0; i < array->total - 1; i++)       
    {   
        for(unsigned long long int j = 0; j < array->total - i - 1; j++)  
        { 
            if(array->data[j] < array->data[j+1]) 
            {
                int tmp = array->data[j];
                array->data[j] = array->data[j+1];
                array->data[j+1] = tmp; 
            }
        }
    }
}

// find_mean
void find_mean(int_array * array)
{
    unsigned long long int total = 0;
    for(unsigned long long int i = 0; i < array->total; i++)
    {
        total += array->data[i];
    }
    array->mean = total/array->total;
}

// find_variance
void find_variance(int_array * array)
{
    find_mean(array);
    unsigned long long int total = 0;
    for(int i = 0; i < array->total; i++)
    {
        unsigned long long int square = (array->data[i] - array->mean) 
                                        * (array->data[i] - array->mean);
        total += square;
    }
    array->variance = total/array->total;
}

// free_int_array
int_array * free_int_array(int_array * array)
{
    // free the data field
    free(array->data);
    // free the array
    free(array);
    // set the array to NULL
    array = NULL;
    // return the array
    return array;
}

void read_column_csv(char const * filename, const char * column)
{
    FILE * csv_file = fopen(filename, "r");

    char * line_1 = (char *)xmalloc(5 * sizeof(char));

    char character = fgetc(csv_file);
    unsigned long long int index = 0;

    while(character != '\n')
    {
        line_1[index] = character;
        index++;
        character = fgetc(csv_file);
    }

    line_1[index] = '\0';

    char * token;

    const char s[2] = ",";

    token = strtok(line_1, s);

    unsigned long long int location = 1;

    while(token != NULL)
    {
        if(strcmp(token, column) == 0)
        {
            break;
        }
        location++;
        token = strtok(NULL, s);
    }

    printf("%d\n", location);

    fclose(csv_file);
}
