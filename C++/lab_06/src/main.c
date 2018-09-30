#include <stdio.h>
#include <stdlib.h>
#include "phonebook.h"
#include <string.h>
#include <time.h>


int main(int argc, char **argv) 
{
    srand(time(NULL));
    phonebook_t book;
    init_phonebook(&book);
    load_phonebook_xml(argv[1], &book);
    print_phonebook(&book);
    gen_phonebook(&book, 1 + rand() % 15);
    save_phonebook_xml(argv[2], &book);
    clear_phonebook(&book);
    return 0;
}
