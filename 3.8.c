#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct symbol *SMB;
struct symbol {
	int left;
	int right;
};

int main(int argc, const char argv[])
{
	char line[100];
	char *p = line;
	char sym[100];
	SMB slashstar, braket,  squarebraket, brace;
	slashstar = (SMB)malloc(sizeof(struct symbol));
	slashstar->left = 0;
	slashstar->right = 0;
	braket = (SMB)malloc(sizeof(struct symbol));
	braket->left = 0;
	braket->right = 0;
	squarebraket = (SMB)malloc(sizeof(struct symbol));
	squarebraket->left = 0;
	squarebraket->right = 0;
	brace = (SMB)malloc(sizeof(struct symbol));
	brace->left = 0;
	brace->right = 0;
	int i=0;

	do{
		fgets(line, 100, stdin);
//		printf("%s", line);
		p = line;
		while(*p) {
			switch(*p) {
				case '(': (braket->left)++;sym[i++] = '('; break;
				case ')': (braket->right)++; sym[i++] = ')';break;
				case '[': (squarebraket->left)++; sym[i++] = '[';break;
				case ']': (squarebraket->right)++; sym[i++] = ']';break;
				case '{': (brace->left)++; sym[i++] = '{';break;
				case '}': (brace->right)++; sym[i++] = '}';break;
				case '/': {
							  p++;
							  if( *p=='*') {
								  (slashstar->left)++;sym[i++] = '/';
							  }
							  break;
						  }
				case '*': {
							  p++;
							  if( *p=='/') {
								  (slashstar->right)++;sym[i++] = '*';
							  }
						  }
			}	
			if(*p) { 
				p++;
			}
		}

	}while(strcmp(".\n", line)!=0);
	char *pp = sym;
	int tag  = 1;
	while(*pp) {
		switch(*pp) {
				case '(': 
				case ')': {
							if(braket->left > braket->right) {
								printf("NO\n");
								printf("(-?\n");
								tag = 0;
							} else if(braket->left < braket->right) {
								printf("NO\n");
								printf("?-)\n");
								tag = 0;
							}
							break;
						}
				
				
				case '[': 
				case ']': {
							if(squarebraket->left > squarebraket->right ) {
								printf("NO\n");
								printf("[-?\n");
								tag = 0;
							} else if(squarebraket->left < squarebraket->right ) {
								printf("NO\n");
								printf("?-]\n");
								tag = 0;
							}
							break;
				}
				case '{': 
				case '}':  {
							if(brace->left > brace->right ) {
									printf("NO\n");
									printf("{-?\n");
									tag = 0;
								} else if(brace->left < brace->right ) {
									printf("NO\n");
									printf("?-}\n");
									tag = 0;
								}
								break;				
				}
				case '/': 
				case '*': {
							 if(slashstar->left > slashstar->right) {
									printf("NO\n");
									printf("/*-?\n");
									tag = 0;
								} else if(slashstar->left < slashstar->right) {
									printf("NO\n");
									printf("?-*/n\n");
									tag = 0;
								}
								break;
						  }
				default : tag = 1;
			}
			if(tag == 0) {
				break;
			} 
			pp++;
	}			













//
//	if(slashstar->left > slashstar->right) {
//		printf("NO\n");
//		printf("/*-?\n");
//		tag = 0;
//	} else if(slashstar->left < slashstar->right) {
//		printf("NO\n");
//		printf("?-*/n\n");
//		tag = 0;
//	}
//	if(braket->left > braket->right) {
//		printf("NO\n");
//		printf("(-?\n");
//		tag = 0;
//	} else if(braket->left < braket->right) {
//		printf("NO\n");
//		printf("?-)\n");
//		tag = 0;
//	} 
//	if(squarebraket->left > squarebraket->right ) {
//		printf("NO\n");
//		printf("[-?\n");
//		tag = 0;
//	} else if(squarebraket->left < squarebraket->right ) {
//		printf("NO\n");
//		printf("?-]\n");
//		tag = 0;
//	}
//	if(brace->left > brace->right ) {
//		printf("NO\n");
//		printf("{-?\n");
//		tag = 0;
//	} else if(brace->left < brace->right ) {
//		printf("NO\n");
//		printf("?-}\n");
//		tag = 0;
//	}
	if(tag == 1) {
		printf("YES\n");
	}
//	printf("( %d %d )\n", braket->left, braket->right);
//	printf("[ %d %d ]\n", squarebraket->left, squarebraket->right);
//	printf("/* %d %d */\n", slashstar->left, slashstar->right);
//	printf("{ %d %d }\n", brace->left, brace->right);
	return 0;
}
