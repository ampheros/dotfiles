
void stringCopy(char *a, char*b){
	while(*b != '\0'){
		*a = *b;
		a++;
		b++;
	}
	*a = '\0';
}

bool stringCompare(char *a, char *b){
	int c = 0;
	while(*a == *b){
		if(*a == '\0' || *b == '\0')
			break;
		a++;
		b++;
	}
	if(*a == '\0' && *b == '\0')
		return true;
	else
		return false;	
}

void stringAdd(char *a, char *b, char *r){
	while(*a != '\0'){
		*r = *a;
		a++;
		r++;
	}
	while(*b !='\0'){
		*r = *b;
		r++;
		b++;
	}
	*r = '\0'; 
	
}

int stringLength(char *a){
	int l = 0;
	while(*a != '\0'){
		a++;
		l++;
	}	
	return l;
}
