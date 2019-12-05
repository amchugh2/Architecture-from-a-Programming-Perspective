#include <stdio.h>
#include <stdlib.h>

int index_array(int a[-5 ... 4][2 ... 5], int i, int j){
	return a[i][j];
}

int main(){
	printf("hello\n");
}

