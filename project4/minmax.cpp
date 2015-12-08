#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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
int findMax(nData *nS, int size, int cat);
int findMin(nData *nS, int size, int cat);

int main (int argc, char *argv[]){
	int size = atoi(argv[1]);
	int cat = atoi(argv[2]);
	nData nS[size];
        readData("censusData", nS, size);
	
	int maxIndex = findMax(nS,size, cat);
	printf("Max\n%d %s %d %f %f %f %f %f %f\n", nS[maxIndex].row, nS[maxIndex].name, nS[maxIndex].total, nS[maxIndex].c3, nS[maxIndex].c4, nS[maxIndex].c5, nS[maxIndex].c6, nS[maxIndex].c7, nS[maxIndex].c8);
	
	int minIndex = findMin(nS, size, cat);
	printf("Min\n%d %s %d %f %f %f %f %f %f\n", nS[minIndex].row, nS[minIndex].name, nS[minIndex].total, nS[minIndex].c3, nS[minIndex].c4, nS[minIndex].c5, nS[minIndex].c6, nS[minIndex].c7, nS[minIndex].c8);

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

int findMax(nData *nS, int size, int cat){
        int maxIndex = 0;
	if(cat == 0){
        	for(int i=0; i<size; i++){
                	if(nS[i].c3 > nS[maxIndex].c3){
                        maxIndex = i;
                	}       
        	}
	}
	
	if(cat == 1){
        	for(int i=0; i<size; i++){
                	if(nS[i].c4 > nS[maxIndex].c4){
                        maxIndex = i;
                	}       
        	}
	}
	
	if(cat == 2){
        	for(int i=0; i<size; i++){
                	if(nS[i].c5 > nS[maxIndex].c5){
                        maxIndex = i;
                	}       
        	}
	}
	if(cat == 3){
        	for(int i=0; i<size; i++){
                	if(nS[i].c6 > nS[maxIndex].c6){
                        maxIndex = i;
                	}       
        	}
	}
	if(cat == 4){
        	for(int i=0; i<size; i++){
                	if(nS[i].c7 > nS[maxIndex].c7){
                        maxIndex = i;
                	}       
        	}
	}
	if(cat == 5){
        	for(int i=0; i<size; i++){
                	if(nS[i].c8 > nS[maxIndex].c8){
                        maxIndex = i;
                	}       
        	}
	}
	
	
        return maxIndex;
}

int findMin(nData *nS, int size, int cat){
        int minIndex = 0;
	if(cat == 0){
        	for(int i=0; i<size; i++){
                	if(nS[i].c3 < nS[minIndex].c3){
                        minIndex = i;
                	}       
        	}
	}
	
	if(cat == 1){
        	for(int i=0; i<size; i++){
                	if(nS[i].c4 < nS[minIndex].c4){
                        minIndex = i;
                	}       
        	}
	}
	
	if(cat == 2){
        	for(int i=0; i<size; i++){
                	if(nS[i].c5 < nS[minIndex].c5){
                        minIndex = i;
                	}       
        	}
	}
	if(cat == 3){
        	for(int i=0; i<size; i++){
                	if(nS[i].c6 < nS[minIndex].c6){
                        minIndex = i;
                	}       
        	}
	}
	if(cat == 4){
        	for(int i=0; i<size; i++){
                	if(nS[i].c7 < nS[minIndex].c7){
                        minIndex = i;
                	}       
        	}
	}
	if(cat == 5){
        	for(int i=0; i<size; i++){
                	if(nS[i].c8 < nS[minIndex].c8){
                        minIndex = i;
                	}       
        	}
	}
	
	
        return minIndex;
}


