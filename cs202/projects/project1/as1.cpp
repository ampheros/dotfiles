//gllobal variables
extern double batPositionX;
extern double batPositionY;
extern double ballPositionX;
extern double ballPositionY;

int isBatBelowBottom(int maxy){

  if (batPositionY > maxy) 
  	{return true;}
  else {return false;}
}

int isBatAboveTop(){

  if (batPositionY < 0) 
  	{return true;}
  else 
  	{return false;}
}


int isOutOfBounds(int position, int low, int high){
  
  	if (position < low || position > high) 
  		{return true;}
  	else 
  		{return false;}
}

int computeScore(int hits, int whiffs){
  
  if (ballPositionX > 79) 
  	{return whiffs;
  	 return hits - whiffs;}
  	else 
  	{return hits;
	 return hits - whiffs;}
}


