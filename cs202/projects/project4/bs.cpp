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
void printData(nData *nS, int size);
int findMax(nData *nS, int size);
void findMed(nData *nS, int size);

void bubble(nData *nS, int n);


int main (int argc, char *argv[]){
        int size = atoi(argv[1]);
        int maxIndex;
        nData nS[size];
	char* input = argv[3];
        readData(input, nS, size);
        bubble(nS, size);
        printData(nS, size);
        maxIndex = findMax(nS,size);
	findMed(nS, size);
	printf("The most common name is:\n%d %s %d %f %f %f %f %f %f\n", nS[maxIndex].row, nS[maxIndex].name, nS[maxIndex].total, nS[maxIndex].c3, nS[maxIndex].c4, nS[maxIndex].c5, nS[maxIndex].c6, nS[maxIndex].c7, nS[maxIndex].c8);

	freopen(argv[5], "w", stdout);
	printData(nS, size);
	findMed(nS, size);
	printf("The most common name is:\n%d %s %d %f %f %f %f %f %f\n", nS[maxIndex].row, nS[maxIndex].name, nS[maxIndex].total, nS[maxIndex].c3, nS[maxIndex].c4, nS[maxIndex].c5, nS[maxIndex].c6, nS[maxIndex].c7, nS[maxIndex].c8);
	fclose (stdout);


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
                printf("%d %s %d %f %f %f %f %f %f\n", nS[i].row, nS[i].name, nS[i].total, nS[i].c3, nS[i].c4, nS[i].c5, nS[i].c6, nS[i].c7, nS[i].c8);
        }
}

int findMax(nData *nS, int size){
        int maxIndex = 0;
        for(int i=0; i<size; i++){
                if(nS[i].total > nS[maxIndex].total){
                        maxIndex = i;
                }       
        }
        return maxIndex;
}



void swap(nData *nS, int i, int j){
  nData tmp = nS[i];
  nS[i] = nS[j];
  nS[j] = tmp;
}


void bubble(nData *nS, int size){
  bool sorted = false;
  while(!sorted){
    sorted = true;
    for(int i = 0; i < size-1; i++){
      if (nS[i].total > nS[i+1].total){
        swap(nS, i, i+1);
        sorted = false;
      }
    }
  }
}

void findMed(nData *nS, int size){
	int mp;
	int u = size%2;
	if(u == 0){
		printf("No median\n");	
	}
	else{
	mp = (size/2)+.5;
	printf("The median name is:\n%d    %s %d %f %f %f %f %f %f\n", nS[mp].row, nS[mp].name, nS[mp].total, nS[mp].c3, nS[mp].c4, nS[mp].c5, nS[mp].c6, nS[mp].c7, nS[mp].c8);
	}
}


