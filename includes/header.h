#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void removeLast(char arr[]);

struct contact{
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
};

struct input{
    char *firstName;
    char *lastName;
    char *companyName;
    char *email;
};
typedef struct input value;
