#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "phonebook.h"
#include <string.h>
#include "names.h"
#include <time.h>

#define BUFFER_SIZE 100000
struct my_user_data {
	int number_ph;
	human_t current_human;
	int current_number_ph;
	phonebook_t* book_ph;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void push_back_human(phonebook_t *book, human_t *human)
{
    if (book->size + 100 >= book->capacity)
	{
		human_t *t = book->humans;
        book->capacity *= 2;
        book->humans = realloc(t, sizeof(human_t) * book->capacity);
    }
	book->humans[book->size++] = *human;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void start_element(void *data, const char *element, const char **attribute) 
{
	struct my_user_data *d = data;

    if (strcmp(element, "human") == 0)
	{
        char* tmp = malloc(3*256);
        strcpy(tmp, attribute[1]);
		char *initials = tmp;
		d->number_ph = 0;
        initials = strtok(initials, " ");
        strcpy(d->current_human.name, initials);

	    initials = strtok(NULL, " ");
        strcpy(d->current_human.middle_name, initials);

        initials = strtok(NULL, " ");
        strcpy(d->current_human.family_name, initials);

    	free(tmp);
    }
	else if(strcmp(element, "phone") == 0)
	{
		d->current_number_ph = 1;
		for (size_t i = 0; i<= 20; i++)
		{
			d->current_human.phones[d->number_ph][i] = '\0';
		}
	}		
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void end_element(void *data, const char *element) 
{
	struct my_user_data *d = data;

   	if (strcmp(element, "phone") == 0)
	{
		d->number_ph++;
		d->current_number_ph = 0;
	}
	else if (strcmp(element, "human") == 0)
	{
		while (d->number_ph < 10)
		{
			d->current_human.phones[d->number_ph++][0] = '\0';
		}
		push_back_human(d->book_ph, &d->current_human);
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void handle_data(void *data, const char *content, int length) 
{
	struct my_user_data *d = data;

    if (d->current_number_ph)
	{
		char* tmp = malloc(length + 1);
		strncpy(tmp, content, length);
		tmp[length] = '\0';
		strcat(d->current_human.phones[d->number_ph], tmp);
		free(tmp);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int comparator (void *a, void *b)
{
	return strcmp(((human_t*)a)->family_name, ((human_t*)b)->family_name);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int load_phonebook_xml(const char *filename, phonebook_t *book)
{  
	FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) 
	{
        printf("Failed to open file\n");
        return 1;
    }
	struct my_user_data data;
	data.book_ph = book;
    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);
	XML_SetUserData(parser, &data);
	size_t buff_size = BUFFER_SIZE;
	char buff [BUFFER_SIZE];
    memset(buff, 0, buff_size);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), buff_size, fp);
        done = len < buff_size;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) 
		{
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
            XML_ParserFree(parser);
            fclose(fp);
            return 2;
        }
    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);
	
	qsort(book->humans, book->size, sizeof(human_t), (__compar_fn_t)comparator);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
int save_phonebook_xml(const char *filename, phonebook_t *book)
{

    FILE *fp;
    fp = fopen(filename, "w");
	int i;
    if (fp == NULL) 
	{
        printf("Failed to open file for writing\n");
        return 3;
    }
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fp, "<phonebook>\n");
    for (i = 0; i < book->size; i++)
	{
        fprintf(fp, "\t<human name=\"%s %s %s\">\n", book->humans[i].name, book->humans[i].middle_name, book->humans[i].family_name);
		int j = 0;
        while ( j < 10 && book->humans[i].phones[j][0] != '\0')
		{
            fprintf(fp, "\t\t<phone>%s</phone>\n", book->humans[i].phones[j]);
			j++;
		}
        fprintf(fp, "\t</human>\n");
    }
    fprintf(fp, "</phonebook>");
    fclose(fp);

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
void print_phonebook(phonebook_t *book)
{
    printf("%d\n", (int)book->size);
	int i;
    for (i = 0; i < book->size; i++)
	{
        printf("name: %s\n", book->humans[i].name);
        printf("middle name: %s\n", book->humans[i].middle_name);
        printf("family name: %s\n", book->humans[i].family_name);
		int j = 0;
		while (j < 10 && book->humans[i].phones[j][0] != '\0')
		{
            printf("phone: %s\n", book->humans[i].phones[j]);
			j++;
		}
    	if (i != book->size - 1)
		{
	    	printf("\n");
		}
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void gen_phonebook(phonebook_t *book, size_t size)
{
	clear_phonebook(book);
	book->capacity = size + 1;
	book->size = size;
	book->humans = malloc((size + 1) * sizeof(human_t));
	int i, j, k;
    for (i = 0; i < size; i++)
	{	       
        int n = 1 + rand() % 4;
        for (j = 0; j < n; j++)
		{
        	int l = 5 + rand() % 10;
            for (k = 0; k < l; k++)
			{
                book->humans[i].phones[j][k] = '0' + rand() % 10;
			}
            book->humans[i].phones[j][l] = '\0';
        }
	    book->humans[i].phones[n][0] = '\0';
        strcpy((book->humans[i]).name, kNames[rand() % NAMES_CNT]);
        strcpy(book->humans[i].family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
        strcpy(book->humans[i].middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
     }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void clear_phonebook(phonebook_t *book)
{
    free(book->humans);
    book->capacity = 0;
    book->size = 0;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void init_phonebook(phonebook_t *book)
{
	book->size = 0;
	book->capacity = 1;
	book->humans = malloc(sizeof(human_t));
}

