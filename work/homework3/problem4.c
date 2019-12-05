#include <stdio.h>

main(){
	unsigned fibonacci(unsigned n){
		if(n <=1){
			return n;
		}
		else{
			unsigned n1 = n - 1;
			unsigned n2 = n -2 ;
			return fibonacci(n1) + fibonacci(n2);
		}
	}
	printf("fib %d",fibonacci(56));
}
