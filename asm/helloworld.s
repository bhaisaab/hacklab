.data

HelloWorldString:
	.ascii "Hello World\n"

.text

.globl _start

_start:
	# Load all the arguments for write(), the system call
	movl $4, %eax # sys call number
	movl $1, %ebx # fd, 1 for stdout
	movl $HelloWorldString, %ecx # buffer to pass to write()
	movl $12, %edx # string len
	int $0x80 # call the interrupt

	# exit the program
	movl $1, %eax
	movl $0, %ebx # status value
	int $0x80
