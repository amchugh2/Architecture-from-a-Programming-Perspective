	.text
	.globl get_parity
#edi contains n	
get_parity:

	#@TODO: add code here to set eax to 1 iff edi has even parity
	test %edi, %edi
	mov $0,  %eax
	jpe .here
	ret

.here:
	movl $1,  %eax
	ret
	
	
	
