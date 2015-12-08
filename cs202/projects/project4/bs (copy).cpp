#include <stdio.h>
#include <stdlib.h>

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
void printData(nData *nS, int size);
int findMin(nData *nS, int size);

int main (int argc, char *argv[]){
        int size = atoi(argv[2]);
        int maxIndex;
        nData nS[size];
        readStudents(argv[1], nS, size);
        printData(nS, size);
        maxIndex = findMax(nS,size);
        printf("The most common name is: %s\n", nS[minIndex].name);

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

void printData(nData *nS, int size){
        for(int i=0; i<size; i++){
                printf("Name: %s - Total: %d\n", nS[i].name, nS[i].total);
        }
}

int findMax(nData *nS, int size){
        int maxIndex = 0;
        for(int i=0; i<size; i++){
                if(nS[i].height > nS[minIndex].height){
                        maxIndex = i;
                }       
        }
        return maxIndex;
}
