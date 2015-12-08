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
	int l;

        char* crypted[700];
        char* eQcrypted = new char[700] ;
        char jwords[700][25];
        char eqwords[10][50];
	


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
			
		decrypted[i] = strcmp(crypted[i], hashes[0]);

                        if (decrypted[i] == 0){
                        printf("Password for %s is %s\n", usernames[0], words[i]);
                        }
        }

     
                
        for(i=0, j=0; i<num_words; i++, j++){
                                
                strcpy(jwords[j],words[i]);
                       
        }
        
   

                
       for(i=0; i<num_words; i++){
        	
                for(j=0; j<num_words; j++){
                sprintf(eqwords[0], "%s%s", words[i], jwords[j]);
          	eQcrypted = crypt(eqwords[0],salt);

			//for(k=0;k<num_records; k++){
                		eQdecrypted[0] = strcmp(eQcrypted, hashes[3]);
                        	if (eQdecrypted[0] == 0){
                        	printf("Password for %s is %s\n", usernames[3], eqwords[0]);
                        	}
				
				eQdecrypted[1] = strcmp(eQcrypted, hashes[4]);
                        	if (eQdecrypted[1] == 0){
                        	printf("Password for %s is %s\n", usernames[4], eqwords[0]);
                        	}

				eQdecrypted[2] = strcmp(eQcrypted, hashes[5]);
                        	if (eQdecrypted[2] == 0){
                        	printf("Password for %s is %s\n", usernames[5], eqwords[0]);
                        	}

			//}

		
		}
	
			
     }
	        
}



                


void parse_passwd( const char* filename, int &num_records, char** &usernames, char** &hashes, char** &fullnames );

void get_words( int &num_words, char** &words );
