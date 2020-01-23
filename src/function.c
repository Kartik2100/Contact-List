#include "header.h"

/*
removes the new line and replaces it with a null character
*/
void removeLast(char arr[]){
   if(arr[strlen(arr) - 1] == '\n'){
       arr[strlen(arr) - 1] = '\0';
   }
}

