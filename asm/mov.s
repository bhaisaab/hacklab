
.data

	HelloWorld:
		.ascii "Hello World!"

	ByteLocation:
		.byte 10

	Int32:
		.int 2

	Int16:
		.short 3

	Float:
		.float 10.23

	IntegerArray:
		.int 10,20,30,40,50

.bss
	.comm LargeBuffer, 10000

.text
	.globl _start

	_start:
		nop

		movl $10, %eax

		movw $50, Int16

		movl %eax, %ebx

		movl Int32, %eax

		movb $3, %al
		movb %al, ByteLocation

		movl $0, %ecx
		movl $2, %edi
		movl $22, IntegerArray(%ecx, %edi, 4)

		movl $Int32, %eax
		movl (%eax), %ebx
		movl $9, (%eax)

		# exit
		movl $1, %eax
		movl $0, %ebx
		int $0x80
