#include<stdio.h>
#include<string.h>
#include "image_to_array.h"

//void readData(char *fileName, ImageData red);

int main(int argc, char *argv[]){
	ImageData red;
	ImageData blue;
	char* input = argv[1];
	printf("%s\n", input);
	red = image_to_array(input);
	
	blue.width = red.width;
	blue.height = red.height;
	blue.data = new unsigned char**[blue.height];
	for(int i = 0; i< red.height; i++){
		blue.data[i] = new unsigned char*[blue.width];
		
		for(int j = 0; j< red.width; j++){
			blue.data[i][j] = new unsigned char[3];
			
			if(red.data[i][j][2]>red.data[i][j][1] && red.data[i][j][2]>red.data[i][j][0] && red.data[i][j][2] > (1.7*red.data[i][j][0]) && red.data[i][j][2] > (1.7*red.data[i][j]   [1]) 
			 ){
				
				blue.data[i][j][2] = 0;
				blue.data[i][j][1] = 0;
				blue.data[i][j][0] = 255;
								
			}
			else{
				blue.data[i][j][2] = red.data[i][j][2];
				blue.data[i][j][1] = red.data[i][j][1];
				blue.data[i][j][0] = red.data[i][j][0];
			}
		}
	}
	array_to_image(blue, "blue");
	
	
cv::waitKey(0);
return 0;
}



