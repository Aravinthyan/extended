#ifndef _EXTENDED_IO_H_
#define _EXTENDED_IO_H_

typedef struct STRING_MANIPULATION
{
    char * string;  /* Pointer to string */
    char ** words;  /* Pointer to pointer to the words of the string */
    unsigned int num_of_words;  /* Holds the number of words */
    unsigned int num_of_frees;  /* Holds the number of frees to be done */
}string_manipulation;

typedef struct INT_ARRAY
{
    int * data; /* Pointer to the array of int's created in heap*/
    int min;    /* Holds the minimum value in array */
    int max;    /* Holds the maximum value in array */
    float mean; /* Holds the mean of the data in the array */
    float variance; /* Holds the variance of the data in the array */
    unsigned long long int total;   /* Holds the total number of elements */
}int_array;

// xmalloc function
/*
    Description
    - creates a block of memory in heap. If this fails the prorgam will 
    graefully exit

    Function parameter
    - size_t size: number of bytes

    return
    - pointer to assigned block or NULL if failed

    NOTE:
    - if the requested amount of memory is not given the program will terminate
*/
void * xmalloc(size_t size);

// xrealloc function
/*
    Description
    - re-allocates old memory in heap with a different size which is specified.
    If this fails the prorgam will graefully exit

    Function parameter
    - void * ptr: pointer to current block of memory
    - size_t size: number of bytes

    return
    - pointer to assigned block or NULL if failed

    NOTE:
    - if the requested amount of memory is not given the program will terminate
*/
void * xrealloc(void * ptr, size_t size);

// read_variable_string_from_stdin function
/*
    Description
    - this function will simply read any length string input and store the 
    result in the heap

    Function parameters
    - nothing(void)
    
    return
    - the string read from stdin is returned as a character array created on the
    heap

    NOTE:
    - the returned character array has to be freed upon exit of program
*/
char * read_variable_string_from_stdin(void);

// get_all_data_file function
/*
    Description
    - retrives the contents inside a file and returns a pointer to the data in
    the heap

    Function parameters
    - const char * filename: pointer to the name of the file
    
    return
    - the string read from file, is returned as a character array created on the
    heap

    NOTE:
    - the returned character array has to be freed upon exit of program
*/
char * get_all_data_file(const char * filename);

// get_words_from_string function
/*
    Description
    - this function will seperate out the words in a string (provided it is a
    sentence)    

    Function parameters
    - const char * input_string: pointer to the string that is used to get the
    seperate words
    - int * num_of_words: this is pointer that will hold the number of words 
    from the string
    - int * num_of_frees: this is a pointer that will hold the number of frees
    that needs to be done upon exiting the program
    
    return
    - this is a pointer to pointer holding all the words in the string

    NOTE:
    - since the character array is multi-dimmensional and this is created in the
    heap it needs to be carefully free'd upon exit of the program
    
*/
char ** get_words_from_string(const char * input_string, int * num_of_words, 
                              int * num_of_frees);

// get_string function
/*
    Description
    - this function simply returns the pointer to the string from the 
    string_manipulation

    Function parameters
    - string_manipulation * data: this is a pointer to the string_manipulation
    variable from which the string will be obtained
    
    return
    - pointer to the retrived string

    NOTE:
    - N/A
*/
char * get_string(string_manipulation * data);

// set_string function
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void set_string(string_manipulation * data, char * string);

// free_words function
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void free_words(string_manipulation * data);

//
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void free_string(string_manipulation * data);

//
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
string_manipulation * free_string_manipulation(string_manipulation * data);

//
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
string_manipulation * free_all_string_manipulation(string_manipulation * data);

//
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void seperate_words_from_string(string_manipulation * data);

// create_int_array
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
int_array * create_int_array(void);

// read_int_array
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void read_int_array(int_array * array, unsigned long long int length);

// print_int_array
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void print_int_array(int_array * array);

// increase_int_array
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void increase_int_array(int_array * array, unsigned long long int length);

// 
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
int_array * sub_set_int_array(int_array * array, unsigned long long int min,
                              unsigned long long int max);

// find_min
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void find_min(int_array * array);

// find_max
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void find_max(int_array * array);

// sort_min_to_max
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void sort_min_to_max(int_array * array);

// sort_max_to_min
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void sort_max_to_min(int_array * array);

// find_mean
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void find_mean(int_array * array);

// find_variance
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
void find_variance(int_array * array);

// free_int_array
/*
    Description
    

    Function parameters
    
    
    return
    

    NOTE:
    
*/
int_array * free_int_array(int_array * array);

// functions to do
// above 4 functions should be done for all types of data type

void read_column_csv(char const * filename, const char * column);

#endif