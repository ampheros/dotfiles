#include <stdio.h>
#include "parse_dict.h"
#include "parse_passwd.h"
#include <string.h>
#include <unistd.h>
#include <crypt.h>
#include <stdlib.h>
#include <string>





int main(){

        int num_words;
        char **words; 
        char salt[] = "$1$........";

        char* filename = "passwd";
        int num_records;
        char **usernames;
        char **hashes;
        char **fullnames;

        int decrypted[10];
        int eQdecrypted[10];
        int i;
        int j;
        int k;

        char *crypted[700];
        char *eQcrypted[700];
        char jwords[700][25];
        char eqwords[425000][50];

        get_words(num_words, words);
        parse_passwd(filename, num_records, usernames, hashes, fullnames);


        for(i=0; i<num_words; i++){
                crypted[i] = crypt(words[i],salt);


                decrypted[i] = strcmp(crypted[i], hashes[6]);

                        if (decrypted[i] == 0){
                        printf("Password for %s is %s\n", usernames[6], words[i]);
                        }
                decrypted[i] = strcmp(crypted[i], hashes[5]);

                        if (decrypted[i] == 0){
                        printf("Password for %s is %s\n", usernames[5], words[i]);
                        }
                decrypted[i] = strcmp(crypted[i], hashes[4]);

                        if (decrypted[i] == 0){
                        printf("Password for %s is %s\n", usernames[4], words[i]);
                        }
                decrypted[i] = strcmp(crypted[i], hashes[3]);

                        if (decrypted[i] == 0){
                        printf("Password for %s is %s\n", usernames[3], words[i]);
                        }
                decrypted[i] = strcmp(crypted[i], hashes[2]);

                        if (decrypted[i] == 0){
                        printf("Password for %s is %s\n", usernames[2], words[i]);
                        }
                decrypted[i] = strcmp(crypted[i], hashes[1]);

                        if (decrypted[i] == 0){
                        printf("Password for %s is %s\n", usernames[1], words[i]);
                        }
        }

        
                
        for(i=0, j=0; i<num_words; i++, j++){
                                
                strcpy(jwords[j],words[i]);
                       
        }
        
              
  /*      sprintf(eqwords[5], "%s %s\n", words[77], jwords[300]);
                printf("%s\n", eqwords[5]);
*/

                
        for(i=0, k=0; i<num_words; i++{
            k = sizeof(eqwords)

                for(j=0; j<num_words; j++, k++){
                sprintf(eqwords[k], "%s %s\n", words[i], jwords[j]);
                }
        }

        for(i=0; i<num_words; i++){
                eQcrypted[i] = crypt(eqwords[i],salt);


                eQdecrypted[i] = strcmp(crypted[i], hashes[6]);

                        if (eQdecrypted[i] == 0){
                        printf("Password for %s is %s\n", usernames[6], words[i]);
                        }
        }
        


                
}

void parse_passwd( const char* filename, int &num_records, char** &usernames, char** &hashes, char** &fullnames );


void get_words( int &num_words, char** &words );

