	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"main.c"
	.def	sprintf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,sprintf
	.globl	sprintf                         # -- Begin function sprintf
	.p2align	4, 0x90
sprintf:                                # @sprintf
.seh_proc sprintf
# %bb.0:
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 104], r9
	mov	qword ptr [rsp + 96], r8
	mov	qword ptr [rsp + 64], rdx
	mov	qword ptr [rsp + 56], rcx
	lea	rax, [rsp + 96]
	mov	qword ptr [rsp + 40], rax
	mov	r9, qword ptr [rsp + 40]
	mov	rdx, qword ptr [rsp + 64]
	mov	rcx, qword ptr [rsp + 56]
	xor	eax, eax
	mov	r8d, eax
	call	_vsprintf_l
	mov	dword ptr [rsp + 52], eax
	mov	eax, dword ptr [rsp + 52]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	vsprintf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,vsprintf
	.globl	vsprintf                        # -- Begin function vsprintf
	.p2align	4, 0x90
vsprintf:                               # @vsprintf
.seh_proc vsprintf
# %bb.0:
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], r8
	mov	qword ptr [rsp + 56], rdx
	mov	qword ptr [rsp + 48], rcx
	mov	rax, qword ptr [rsp + 64]
	mov	r8, qword ptr [rsp + 56]
	mov	rcx, qword ptr [rsp + 48]
	mov	rdx, -1
	xor	r9d, r9d
                                        # kill: def $r9 killed $r9d
	mov	qword ptr [rsp + 32], rax
	call	_vsnprintf_l
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	_snprintf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_snprintf
	.globl	_snprintf                       # -- Begin function _snprintf
	.p2align	4, 0x90
_snprintf:                              # @_snprintf
.seh_proc _snprintf
# %bb.0:
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 104], r9
	mov	qword ptr [rsp + 64], r8
	mov	qword ptr [rsp + 56], rdx
	mov	qword ptr [rsp + 48], rcx
	lea	rax, [rsp + 104]
	mov	qword ptr [rsp + 32], rax
	mov	r9, qword ptr [rsp + 32]
	mov	r8, qword ptr [rsp + 64]
	mov	rdx, qword ptr [rsp + 56]
	mov	rcx, qword ptr [rsp + 48]
	call	_vsnprintf
	mov	dword ptr [rsp + 44], eax
	mov	eax, dword ptr [rsp + 44]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	_vsnprintf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_vsnprintf
	.globl	_vsnprintf                      # -- Begin function _vsnprintf
	.p2align	4, 0x90
_vsnprintf:                             # @_vsnprintf
.seh_proc _vsnprintf
# %bb.0:
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], r9
	mov	qword ptr [rsp + 56], r8
	mov	qword ptr [rsp + 48], rdx
	mov	qword ptr [rsp + 40], rcx
	mov	rax, qword ptr [rsp + 64]
	mov	r8, qword ptr [rsp + 56]
	mov	rdx, qword ptr [rsp + 48]
	mov	rcx, qword ptr [rsp + 40]
	xor	r9d, r9d
                                        # kill: def $r9 killed $r9d
	mov	qword ptr [rsp + 32], rax
	call	_vsnprintf_l
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:
	push	rbp
	.seh_pushreg rbp
	push	rsi
	.seh_pushreg rsi
	push	rdi
	.seh_pushreg rdi
	push	rbx
	.seh_pushreg rbx
	sub	rsp, 280
	.seh_stackalloc 280
	lea	rbp, [rsp + 128]
	.seh_setframe rbp, 128
	.seh_endprologue
	mov	dword ptr [rbp + 148], 0
	lea	rcx, [rip + "??_C@_0BH@DKGDGBBF@Write?5string?5below?6?$DO?$DO?5?$AA@"]
	call	printf
	xor	ecx, ecx
	call	__acrt_iob_func
	mov	r8, rax
	lea	rcx, [rbp + 48]
	mov	edx, 100
	call	fgets
	cmp	rax, 0
	jne	.LBB4_2
# %bb.1:
	mov	dword ptr [rbp + 148], -1
	jmp	.LBB4_9
.LBB4_2:
	lea	rdx, [rbp + 48]
	lea	rcx, [rip + "??_C@_03OFAPEBGM@?$CFs?6?$AA@"]
	call	printf
	lea	rcx, [rbp + 48]
	call	strlen
	sub	rax, 1
	mov	byte ptr [rbp + rax + 48], 0
	lea	rax, [rbp + 48]
	mov	qword ptr [rbp + 40], rax
	#APP

	jmp	.L__MSASMLABEL_.0__start
.L__MSASMLABEL_.0__EmulateProc:
	push	rbp
	mov	rbp, rsp
	mov	rdi, qword ptr [rbp + 16]
	mov	rcx, qword ptr [rbp + 16]
	cld
	xor	rax, rax
	mov	al, 0
	scasb	al, byte ptr es:[rdi]
	dec	rdi
	sub	rdi, rcx
	mov	rax, rcx
	pop	rbp
	ret
.L__MSASMLABEL_.0__start:
	push	rax
	push	rdi
	push	rcx
	push	qword ptr [rbp + 40]
	call	.L__MSASMLABEL_.0__EmulateProc
	add	rsp, 8
	dec	rax
	mov	qword ptr [rbp + 32], rax
	pop	rcx
	pop	rdi
	pop	rax

	#NO_APP
	mov	rdx, qword ptr [rbp + 32]
	lea	rcx, [rip + "??_C@_0BA@HNOHBDKC@strlen?5?$DO?$DO?5?$CFlld?6?$AA@"]
	call	printf
	lea	rcx, [rip + "??_C@_0BM@DDGFFLPJ@Write?5first?5string?5below?6?$DO?$DO?$AA@"]
	call	printf
	xor	ecx, ecx
	call	__acrt_iob_func
	mov	r8, rax
	lea	rcx, [rbp + 48]
	mov	edx, 100
	call	fgets
	cmp	rax, 0
	jne	.LBB4_4
# %bb.3:
	mov	dword ptr [rbp + 148], -1
	jmp	.LBB4_9
.LBB4_4:
	lea	rcx, [rbp + 48]
	call	strlen
	sub	rax, 1
	mov	byte ptr [rbp + rax + 48], 0
	lea	rax, [rbp + 48]
	mov	qword ptr [rbp + 40], rax
	lea	rcx, [rbp + 48]
	call	strlen
	mov	qword ptr [rbp + 24], rax
	lea	rcx, [rbp - 80]
	xor	edx, edx
	mov	r8d, 100
	call	memset
	lea	rax, [rbp - 80]
	mov	qword ptr [rbp - 88], rax
	#APP

	push	rax
	push	rbx
	push	rdx
	push	rcx
	push	rsi
	push	qword ptr [rbp + 24]
	push	qword ptr [rbp + 40]
	push	qword ptr [rbp - 88]

	#NO_APP
	call	copyString
	#APP

	add	rsp, 24
	mov	qword ptr [rbp - 88], rax
	pop	rsi
	pop	rcx
	pop	rdx
	pop	rbx
	pop	rax

	#NO_APP
	mov	dword ptr [rbp - 92], 0
.LBB4_5:                                # =>This Inner Loop Header: Depth=1
	movsxd	rax, dword ptr [rbp - 92]
	cmp	rax, qword ptr [rbp + 24]
	jge	.LBB4_8
# %bb.6:                                #   in Loop: Header=BB4_5 Depth=1
	mov	rax, qword ptr [rbp - 88]
	movsxd	rcx, dword ptr [rbp - 92]
	movsx	edx, byte ptr [rax + rcx]
	lea	rcx, [rip + "??_C@_03PJCJOCBM@?$CFc?6?$AA@"]
	call	printf
# %bb.7:                                #   in Loop: Header=BB4_5 Depth=1
	mov	eax, dword ptr [rbp - 92]
	add	eax, 1
	mov	dword ptr [rbp - 92], eax
	jmp	.LBB4_5
.LBB4_8:
	mov	dword ptr [rbp + 148], 0
.LBB4_9:
	mov	eax, dword ptr [rbp + 148]
	add	rsp, 280
	pop	rbx
	pop	rdi
	pop	rsi
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	printf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,printf
	.globl	printf                          # -- Begin function printf
	.p2align	4, 0x90
printf:                                 # @printf
.seh_proc printf
# %bb.0:
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 104], r9
	mov	qword ptr [rsp + 96], r8
	mov	qword ptr [rsp + 88], rdx
	mov	qword ptr [rsp + 64], rcx
	lea	rax, [rsp + 88]
	mov	qword ptr [rsp + 48], rax
	mov	rax, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 40], rax       # 8-byte Spill
	mov	rax, qword ptr [rsp + 64]
	mov	qword ptr [rsp + 32], rax       # 8-byte Spill
	mov	ecx, 1
	call	__acrt_iob_func
	mov	rdx, qword ptr [rsp + 32]       # 8-byte Reload
	mov	r9, qword ptr [rsp + 40]        # 8-byte Reload
	mov	rcx, rax
	xor	eax, eax
	mov	r8d, eax
	call	_vfprintf_l
	mov	dword ptr [rsp + 60], eax
	mov	eax, dword ptr [rsp + 60]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	_vsprintf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_vsprintf_l
	.globl	_vsprintf_l                     # -- Begin function _vsprintf_l
	.p2align	4, 0x90
_vsprintf_l:                            # @_vsprintf_l
.seh_proc _vsprintf_l
# %bb.0:
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], r9
	mov	qword ptr [rsp + 56], r8
	mov	qword ptr [rsp + 48], rdx
	mov	qword ptr [rsp + 40], rcx
	mov	rax, qword ptr [rsp + 64]
	mov	r9, qword ptr [rsp + 56]
	mov	r8, qword ptr [rsp + 48]
	mov	rcx, qword ptr [rsp + 40]
	mov	rdx, -1
	mov	qword ptr [rsp + 32], rax
	call	_vsnprintf_l
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	_vsnprintf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_vsnprintf_l
	.globl	_vsnprintf_l                    # -- Begin function _vsnprintf_l
	.p2align	4, 0x90
_vsnprintf_l:                           # @_vsnprintf_l
.seh_proc _vsnprintf_l
# %bb.0:
	sub	rsp, 136
	.seh_stackalloc 136
	.seh_endprologue
	mov	rax, qword ptr [rsp + 176]
	mov	qword ptr [rsp + 128], r9
	mov	qword ptr [rsp + 120], r8
	mov	qword ptr [rsp + 112], rdx
	mov	qword ptr [rsp + 104], rcx
	mov	rax, qword ptr [rsp + 176]
	mov	qword ptr [rsp + 88], rax       # 8-byte Spill
	mov	rax, qword ptr [rsp + 128]
	mov	qword ptr [rsp + 80], rax       # 8-byte Spill
	mov	rax, qword ptr [rsp + 120]
	mov	qword ptr [rsp + 72], rax       # 8-byte Spill
	mov	rax, qword ptr [rsp + 112]
	mov	qword ptr [rsp + 64], rax       # 8-byte Spill
	mov	rax, qword ptr [rsp + 104]
	mov	qword ptr [rsp + 56], rax       # 8-byte Spill
	call	__local_stdio_printf_options
	mov	rdx, qword ptr [rsp + 56]       # 8-byte Reload
	mov	r8, qword ptr [rsp + 64]        # 8-byte Reload
	mov	r9, qword ptr [rsp + 72]        # 8-byte Reload
	mov	r10, qword ptr [rsp + 80]       # 8-byte Reload
	mov	rcx, rax
	mov	rax, qword ptr [rsp + 88]       # 8-byte Reload
	mov	rcx, qword ptr [rcx]
	or	rcx, 1
	mov	qword ptr [rsp + 32], r10
	mov	qword ptr [rsp + 40], rax
	call	__stdio_common_vsprintf
	mov	dword ptr [rsp + 100], eax
	cmp	dword ptr [rsp + 100], 0
	jge	.LBB7_2
# %bb.1:
	mov	eax, 4294967295
	mov	dword ptr [rsp + 52], eax       # 4-byte Spill
	jmp	.LBB7_3
.LBB7_2:
	mov	eax, dword ptr [rsp + 100]
	mov	dword ptr [rsp + 52], eax       # 4-byte Spill
.LBB7_3:
	mov	eax, dword ptr [rsp + 52]       # 4-byte Reload
	add	rsp, 136
	ret
	.seh_endproc
                                        # -- End function
	.def	__local_stdio_printf_options;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,__local_stdio_printf_options
	.globl	__local_stdio_printf_options    # -- Begin function __local_stdio_printf_options
	.p2align	4, 0x90
__local_stdio_printf_options:           # @__local_stdio_printf_options
# %bb.0:
	lea	rax, [rip + __local_stdio_printf_options._OptionsStorage]
	ret
                                        # -- End function
	.def	_vfprintf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_vfprintf_l
	.globl	_vfprintf_l                     # -- Begin function _vfprintf_l
	.p2align	4, 0x90
_vfprintf_l:                            # @_vfprintf_l
.seh_proc _vfprintf_l
# %bb.0:
	sub	rsp, 104
	.seh_stackalloc 104
	.seh_endprologue
	mov	qword ptr [rsp + 96], r9
	mov	qword ptr [rsp + 88], r8
	mov	qword ptr [rsp + 80], rdx
	mov	qword ptr [rsp + 72], rcx
	mov	rax, qword ptr [rsp + 96]
	mov	qword ptr [rsp + 64], rax       # 8-byte Spill
	mov	rax, qword ptr [rsp + 88]
	mov	qword ptr [rsp + 56], rax       # 8-byte Spill
	mov	rax, qword ptr [rsp + 80]
	mov	qword ptr [rsp + 48], rax       # 8-byte Spill
	mov	rax, qword ptr [rsp + 72]
	mov	qword ptr [rsp + 40], rax       # 8-byte Spill
	call	__local_stdio_printf_options
	mov	rdx, qword ptr [rsp + 40]       # 8-byte Reload
	mov	r8, qword ptr [rsp + 48]        # 8-byte Reload
	mov	r9, qword ptr [rsp + 56]        # 8-byte Reload
	mov	rcx, rax
	mov	rax, qword ptr [rsp + 64]       # 8-byte Reload
	mov	rcx, qword ptr [rcx]
	mov	qword ptr [rsp + 32], rax
	call	__stdio_common_vfprintf
	nop
	add	rsp, 104
	ret
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr",discard,"??_C@_0BH@DKGDGBBF@Write?5string?5below?6?$DO?$DO?5?$AA@"
	.globl	"??_C@_0BH@DKGDGBBF@Write?5string?5below?6?$DO?$DO?5?$AA@" # @"??_C@_0BH@DKGDGBBF@Write?5string?5below?6?$DO?$DO?5?$AA@"
"??_C@_0BH@DKGDGBBF@Write?5string?5below?6?$DO?$DO?5?$AA@":
	.asciz	"Write string below\n>> "

	.section	.rdata,"dr",discard,"??_C@_03OFAPEBGM@?$CFs?6?$AA@"
	.globl	"??_C@_03OFAPEBGM@?$CFs?6?$AA@" # @"??_C@_03OFAPEBGM@?$CFs?6?$AA@"
"??_C@_03OFAPEBGM@?$CFs?6?$AA@":
	.asciz	"%s\n"

	.section	.rdata,"dr",discard,"??_C@_0BA@HNOHBDKC@strlen?5?$DO?$DO?5?$CFlld?6?$AA@"
	.globl	"??_C@_0BA@HNOHBDKC@strlen?5?$DO?$DO?5?$CFlld?6?$AA@" # @"??_C@_0BA@HNOHBDKC@strlen?5?$DO?$DO?5?$CFlld?6?$AA@"
"??_C@_0BA@HNOHBDKC@strlen?5?$DO?$DO?5?$CFlld?6?$AA@":
	.asciz	"strlen >> %lld\n"

	.section	.rdata,"dr",discard,"??_C@_0BM@DDGFFLPJ@Write?5first?5string?5below?6?$DO?$DO?$AA@"
	.globl	"??_C@_0BM@DDGFFLPJ@Write?5first?5string?5below?6?$DO?$DO?$AA@" # @"??_C@_0BM@DDGFFLPJ@Write?5first?5string?5below?6?$DO?$DO?$AA@"
"??_C@_0BM@DDGFFLPJ@Write?5first?5string?5below?6?$DO?$DO?$AA@":
	.asciz	"Write first string below\n>>"

	.section	.rdata,"dr",discard,"??_C@_03PJCJOCBM@?$CFc?6?$AA@"
	.globl	"??_C@_03PJCJOCBM@?$CFc?6?$AA@" # @"??_C@_03PJCJOCBM@?$CFc?6?$AA@"
"??_C@_03PJCJOCBM@?$CFc?6?$AA@":
	.asciz	"%c\n"

	.lcomm	__local_stdio_printf_options._OptionsStorage,8,8 # @__local_stdio_printf_options._OptionsStorage
	.addrsig
	.addrsig_sym _vsnprintf
	.addrsig_sym printf
	.addrsig_sym fgets
	.addrsig_sym __acrt_iob_func
	.addrsig_sym strlen
	.addrsig_sym copyString
	.addrsig_sym _vsprintf_l
	.addrsig_sym _vsnprintf_l
	.addrsig_sym __stdio_common_vsprintf
	.addrsig_sym __local_stdio_printf_options
	.addrsig_sym _vfprintf_l
	.addrsig_sym __stdio_common_vfprintf
	.addrsig_sym __local_stdio_printf_options._OptionsStorage
