#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
        int row;
        char *name;
        int total;
        float c3;
        float c4;
        float c5;
        float c6;
        float c7;
        float c8;
}nData;

void readData(char *fileName, nData *nS, int size);

int main(int argc, char *argv[]){
	int size = atoi(argv[1]);
	char* input = argv[2];
	nData nS[size];
        readData("censusData", nS, size);
	for(int i = 0; i<size; i++) {
	int w = strcmp(input, nS[i].name);
		if(w == 0){
			printf("%d %s %d %f %f %f %f %f %f\n", nS[i].row, nS[i].name, nS[i].total, nS[i].c3, nS[i].c4, nS[i].c5, nS[i].c6, nS[i].c7, nS[i].c8);
        	} 
	}
		
}
	



void readData(char *fileName, nData *nS, int size){
        FILE *fp;
        fp = fopen("censusData", "r");

        for(int i = 0; i < size; i++){
                nS[i].name = new char [30];
                fscanf(fp, "%d %s %d %f %f %f %f %f %f ", &(nS[i].row), nS[i].name, &(nS[i].total), &(nS[i].c3), &(nS[i].c4), &(nS[i].c5), &(nS[i].c6), &(nS[i].c7), &(nS[i].c8));         
        }
        fclose(fp);

}
