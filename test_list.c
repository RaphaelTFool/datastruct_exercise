#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct data_list
{
	int  test_int_data;
	char test_char_data; 
	struct list_head list;
}data_list;


int main()
{	
	data_list data;
	data.test_int_data = 123;
	data.test_char_data = 'a';
	
	/* We test offsetof here*/
	printf("\n-------We test the offset marco-------\n");
	printf("offset of test_int_data = %lu\n", OFFSETOF(struct data_list, test_int_data));
	printf("offset of test_char_data = %lu\n", OFFSETOF(struct data_list, test_char_data));
	printf("offset of list_head = %lu\n", OFFSETOF(struct data_list, list));

	/*We test container_of here*/
	printf("\n-------We test the container_of marco-------\n");
	struct data_list *ptr;
	ptr = CONTAINER_OF(&(data.test_int_data), struct data_list, test_int_data);
	printf("We define a new pointer ptr to struct data_list\n");
	printf("After container_of, the values are as follow\n");
	printf("ptr->test_int_data = %d\n", ptr->test_int_data);
	printf("ptr->test_char_data = %c\n", ptr->test_char_data); 

	return 0;
}
