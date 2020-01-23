#include "header.h"

int main(){
    /*
    allocate memory for the structures
    */
    struct contact *info= malloc(sizeof(struct contact) *1000);
    struct contact *out = malloc(sizeof(struct contact) *1000);
    value *ptr= malloc(sizeof(value)*1000);
    char cName[100];
    char lName[100];
    char fName[100];
    char eName[100];

    /*
    Open file in append mode, in binary
    */
    FILE *fp;
    fp = fopen("myContactList.db","ab+");
    if(fp == NULL){
        printf("file not found");
        return(1);
    }

    /*
    Declare variables
    */
    char enter[2];
    char enterTwo[2];
    char enterThree[2];
    int arr[100];
    int i = 0;
    int j = 0;
    int fileLen;
    int val = 0;
    fseek(fp,0,SEEK_END);
    int place = ftell(fp);
    int len = 0;
    int k =0;
    char string[500];
    int x = 0;
    int t = 0;
    int m = 0;
    int realVal;
    (void)arr;
    while(x==0){
        fseek(fp,0,SEEK_END);
        fileLen = ftell(fp);
        fseek(fp,0,SEEK_SET);
        if(fileLen>0){
            while(val != 1){
                fread(&out[j],sizeof(struct contact),1,fp);
                fseek(fp,out[j].next,SEEK_SET);
                if(out[j].next == fileLen){
                    val = 1;
                }
                j = j+1;
            }
            printf("Number of Contacts %d\n",j);
            for(m=0;m<j;m++){
                k=k+1;
                if((out[m].last_name_posn == 0) && (out[m].company_name_posn == 0)){
                    k=k-1;
                }
                else if(out[m].last_name_posn == 0){
                    fseek(fp,out[m].company_name_posn,SEEK_SET);
                    fread(string,sizeof(char),100,fp);
                    printf("%d. %s\n",k,string);
                    arr[t] = m;
                    t=t+1;
                }
                else{
                    fseek(fp,out[m].first_name_posn,SEEK_SET);
                    fread(string,sizeof(char),100,fp);
                    printf("%d. %s",k,string);

                    fseek(fp,out[m].last_name_posn,SEEK_SET);
                    fread(string,sizeof(char),100,fp);
                    printf(" %s\n",string);
                    arr[t] = m;
                    t=t+1;
                }
            }
            k=0;
        }
        else{
            printf("Number of Contacts = 0\n");
        }
        printf("Action: ");
        scanf("%s", enter);

        if(strcmp(enter,"A") == 0){
            ptr[i].firstName = malloc(sizeof(char) *100);
            printf("First Name: ");
            fgets(fName,100,stdin);
            fgets(fName,100,stdin);
            removeLast(fName);
            strcpy(ptr[i].firstName, fName);

            ptr[i].lastName = malloc(sizeof(char) *100);
            printf("Last Name: ");
            fgets(lName,100,stdin);
            removeLast(lName);
            strcpy(ptr[i].lastName, lName);

            ptr[i].companyName = malloc(sizeof(char) *100);
            printf("Company Name: ");
            fgets(cName,100,stdin);
            removeLast(cName);
            strcpy(ptr[i].companyName, cName);

            printf("Phone Number (enter only numbers): ");
            scanf("%lu",&info[i].phone_number);

            ptr[i].email = malloc(sizeof(char) *50);
            printf("Email: ");
            fgets(eName,100,stdin);
            fgets(eName,100,stdin);
            removeLast(eName);
            strcpy(ptr[i].email, eName);

            /*
            calculating the position of the records
            */
            printf("Action: ");
            scanf("%s",enter);
         if(strcmp(enter,"S") == 0){
            if(strlen(ptr[i].firstName)>0){
                info[i].first_name_posn = place + 48;
                place = info[i].first_name_posn;
                len = strlen(ptr[i].firstName);
            }
            else{
                info[i].first_name_posn = 0;
                place = place + 48;
            }

            if((len==0)&&(strlen(ptr[i].lastName)>0)){
                info[i].last_name_posn = place + len;
                place = info[i].last_name_posn;
                len=strlen(ptr[i].lastName);
            }
            else if(strlen(ptr[i].lastName)>0){
                info[i].last_name_posn = place + len + 1;
                place = info[i].last_name_posn;
                len=strlen(ptr[i].lastName);
            }
            else{
                info[i].last_name_posn = 0;
            }

            if((len==0)&&(strlen(ptr[i].companyName)>0)){
                info[i].company_name_posn = place + len;
                place = info[i].company_name_posn ;
                len=strlen(ptr[i].companyName);
            }
            else if(strlen(ptr[i].companyName)>0){
                info[i].company_name_posn = place + len+1;
                place = info[i].company_name_posn ;
                len=strlen(ptr[i].companyName);
            }
            else{
                info[i].company_name_posn = 0;
            }

            if((len==0)&&(strlen(ptr[i].email)>0)){
                 info[i].email_posn = place + len;
                 place = info[i].email_posn ;
                 len=strlen(ptr[i].email);
            }
            else if(strlen(ptr[i].email)>0){
                info[i].email_posn = place + len + 1;
                place = info[i].email_posn ;
                len=strlen(ptr[i].email);
            }
            else{
                info[i].email_posn = 0;
            }

            if(len>0){
                info[i].next = place + len + 1;
                place = info[i].next;
            }
            else if(len==0){
                info[i].next = place + len;
                place = info[i].next;
            }

            len =0;


            /*
            writing the contact structure as well as the strings that the
            user entered
            */
            fwrite(&info[i],sizeof(struct contact),1,fp);

            if(strlen(ptr[i].firstName) > 0){
                info[i].first_name_posn = ftell(fp);
                fwrite(ptr[i].firstName,sizeof(char),strlen(ptr[i].firstName)+1,fp);
            }
            else{
                info[i].first_name_posn = 0;
            }

            if(strlen(ptr[i].lastName) > 0){
                info[i].last_name_posn = ftell(fp);
                fwrite(ptr[i].lastName,sizeof(char),strlen(ptr[i].lastName)+1,fp);
            }
            else{
                info[i].last_name_posn = 0;
            }

            if(strlen(ptr[i].companyName) > 0){
                info[i].company_name_posn = ftell(fp);
                fwrite(ptr[i].companyName,sizeof(char),strlen(ptr[i].companyName)+1,fp);
            }
            else{
                info[i].company_name_posn = 0;
            }

            if(strlen(ptr[i].email) > 0){
                info[i].email_posn = ftell(fp);
                fwrite(ptr[i].email,sizeof(char),strlen(ptr[i].email)+1,fp);
            }
            else{
                info[i].email_posn = ftell(fp);
            }

            info[i].next = ftell(fp);
            i=i+1;
         }
       }

       else if(strcmp(enter,"X") == 0){
           x = 1;
       }

       else{
           realVal = atoi(enter);
           realVal = realVal - 1;
           if(out[realVal].first_name_posn == 0){
                printf("First Name: \n");
            }
            else{
                printf("First Name: ");
                fseek(fp,out[realVal].first_name_posn,SEEK_SET);
                fread(string,sizeof(char),100,fp);
                printf("%s\n",string);
            }

            if(out[realVal].last_name_posn == 0){
                printf("Last Name: \n");
            }
            else{
                printf("Last Name: ");
                fseek(fp,out[realVal].last_name_posn,SEEK_SET);
                fread(string,sizeof(char),100,fp);
                printf("%s\n",string);
            }

            if(out[realVal].company_name_posn == 0){
                printf("Company Name: \n");
            }
            else{
                printf("Company Name: ");
                fseek(fp,out[realVal].company_name_posn,SEEK_SET);
                fread(string,sizeof(char),100,fp);
                printf("%s\n",string);
            }

            printf("Phone Number: %lu\n",out[realVal].phone_number);

            if(out[realVal].email_posn == 0){
                printf("Email: \n");
            }
            else{
                printf("Email: ");
                fseek(fp,out[realVal].email_posn,SEEK_SET);
                fread(string,sizeof(char),100,fp);
                printf("%s\n",string);
            }
            printf("Action: ");
            scanf("%s",enterTwo);

            if(strcmp(enterThree,"E") == 0){
                if(out[realVal].first_name_posn == 0){
                    printf("First Name: \n");
                }
                else{
                    printf("First Name: ");
                    fseek(fp,out[realVal].first_name_posn,SEEK_SET);
                    fread(string,sizeof(char),100,fp);
                    printf("%s\n",string);
                    strcpy(ptr[i].firstName,string);
                }

                if(out[realVal].last_name_posn == 0){
                    printf("Last Name: \n");
                }
                else{
                    printf("Last Name: ");
                    fseek(fp,out[realVal].last_name_posn,SEEK_SET);
                    fread(string,sizeof(char),100,fp);
                    printf("%s\n",string);
                    strcpy(ptr[i].lastName,string);
                }

                if(out[realVal].company_name_posn == 0){
                    printf("Company Name: \n");
                }
                else{
                    printf("Company Name: ");
                    fseek(fp,out[realVal].company_name_posn,SEEK_SET);
                    fread(string,sizeof(char),100,fp);
                    printf("%s\n",string);
                    strcpy(ptr[i].companyName,string);
                }

                info[realVal].last_name_posn = 0;
                info[realVal].company_name_posn = 0;
                fwrite(&info[realVal],sizeof(struct contact),1,fp);

                printf("Phone Number (enter only numbers): ");
                scanf("%lu",&info[i].phone_number);

                ptr[i].email = malloc(sizeof(char) *50);
                printf("Email: ");
                fgets(eName,100,stdin);
                fgets(eName,100,stdin);
                removeLast(eName);
                strcpy(ptr[i].email, eName);

                /*
                calculating the position of the records
                */
                printf("Action: ");
                scanf("%s",enterTwo);
             if(strcmp(enterTwo,"S")==0){
                if(strlen(ptr[i].firstName)>0){
                    info[i].first_name_posn = place + 48;
                    place = info[i].first_name_posn;
                    len = strlen(ptr[i].firstName);
                }
                else{
                    info[i].first_name_posn = 0;
                    place = place + 48;
                }

                if((len==0)&&(strlen(ptr[i].lastName)>0)){
                    info[i].last_name_posn = place + len;
                    place = info[i].last_name_posn;
                    len=strlen(ptr[i].lastName);
                }
                else if(strlen(ptr[i].lastName)>0){
                    info[i].last_name_posn = place + len + 1;
                    place = info[i].last_name_posn;
                    len=strlen(ptr[i].lastName);
                }
                else{
                    info[i].last_name_posn = 0;
                }

                if((len==0)&&(strlen(ptr[i].companyName)>0)){
                    info[i].company_name_posn = place + len;
                    place = info[i].company_name_posn ;
                    len=strlen(ptr[i].companyName);
                }
                else if(strlen(ptr[i].companyName)>0){
                    info[i].company_name_posn = place + len+1;
                    place = info[i].company_name_posn ;
                    len=strlen(ptr[i].companyName);
                }
                else{
                    info[i].company_name_posn = 0;
                }

                if((len==0)&&(strlen(ptr[i].email)>0)){
                    info[i].email_posn = place + len;
                    place = info[i].email_posn ;
                    len=strlen(ptr[i].email);
                }
                else if(strlen(ptr[i].email)>0){
                    info[i].email_posn = place + len + 1;
                    place = info[i].email_posn ;
                    len=strlen(ptr[i].email);
                }
                else{
                    info[i].email_posn = 0;
                }

                if(len>0){
                    info[i].next = place + len + 1;
                    place = info[i].next;
                }
                else if(len==0){
                    info[i].next = place + len;
                    place = info[i].next;
                }

                len =0;


                /*
                writing the contact structure as well as the strings that the
                user entered
                */
                fwrite(&info[i],sizeof(struct contact),1,fp);

                if(strlen(ptr[i].firstName) > 0){
                    info[i].first_name_posn = ftell(fp);
                    fwrite(ptr[i].firstName,sizeof(char),strlen(ptr[i].firstName)+1,fp);
                }
                else{
                    info[i].first_name_posn = 0;
                }

                if(strlen(ptr[i].lastName) > 0){
                    info[i].last_name_posn = ftell(fp);
                    fwrite(ptr[i].lastName,sizeof(char),strlen(ptr[i].lastName)+1,fp);
                }
                else{
                    info[i].last_name_posn = 0;
                }

                if(strlen(ptr[i].companyName) > 0){
                    info[i].company_name_posn = ftell(fp);
                    fwrite(ptr[i].companyName,sizeof(char),strlen(ptr[i].companyName)+1,fp);
                }
                else{
                    info[i].company_name_posn = 0;
                }

                if(strlen(ptr[i].email) > 0){
                    info[i].email_posn = ftell(fp);
                    fwrite(ptr[i].email,sizeof(char),strlen(ptr[i].email)+1,fp);
                }
                else{
                    info[i].email_posn = ftell(fp);
                }

                info[i].next = ftell(fp);
                i=i+1;
             }

             else if(strcmp(enterTwo,"D")==0){
                info[realVal].last_name_posn = 0;
                info[realVal].company_name_posn = 0;
                fwrite(&info[realVal],sizeof(struct contact),1,fp);
             }
          }
          else if(strcmp(enterThree,"D")==0){
              info[realVal].last_name_posn = 0;
              info[realVal].company_name_posn = 0;
              fwrite(&info[realVal],sizeof(struct contact),1,fp);
          }
       }
    }
    /*
    freeing memory from structures and closing the flie
    */
    free(info);
    free(out);
    free(ptr);
    fclose(fp);
return 0;
}



