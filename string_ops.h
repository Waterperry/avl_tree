#ifndef STRING_OPS
#include <stdlib.h>

#define STRING_OPS 1

char *append(char*,char);
char *join(char*,char*);
int len(char*);

char *append(char *str, char c){
	int len_s = len(str);
	char *new = malloc((2+len_s) * sizeof(char));

	for(int i = 0; i < len_s; i++){
		new[i] = str[i];
	}

	new[len_s] = c;
	new[len_s+1] = '\0';
	return new;
}

char *join(char *a, char *b){
	int a_len = len(a);
	int b_len = len(b);
	char *str = malloc(a_len + b_len + 1);
	for(int i = 0; i < a_len; i++){
		str[i] = a[i];
	}
	for(int i = a_len; i < a_len + b_len; i++){
		str[i] = b[i - a_len];
	}
	str[a_len + b_len] = 0;
	return str;
}

int len(char *str){
	int len = 0;
	while(str[len]!='\0') len++;
	return len;
}

#endif
