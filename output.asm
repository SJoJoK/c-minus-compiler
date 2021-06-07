SECTION .data
a times 5 dd 0
                                 
ReturnMsg: db "Return Value:%i",10,0

SECTION .text
extern printf
global main
main:
;boilerplate prologue
push ebp
mov ebp, esp
push ebx
push esi
push edi
sub esp, 16

mov eax, 0
mov [ebp-12], eax
While0:
mov eax, [ebp-12]
mov ebx, 5
cmp eax, ebx
jl Lt1
mov eax, 0
jmp EndLt1
Lt1:
mov eax, 1
EndLt1:
cmp eax, 1
jne EndWhile0
mov eax, [ebp-12]
mov ebx, [ebp-12]
mov ecx, a
mov [ecx+4*eax], ebx
mov ebx, [ebp-12]
mov ecx, 1
add ebx, ecx
mov [ebp-12], ebx
jmp While0
EndWhile0:
mov ebx, 0
mov [ebp-12], ebx
mov ebx, 0
mov [ebp-16], ebx
While2:
mov ebx, [ebp-12]
mov ecx, 5
cmp ebx, ecx
jl Lt3
mov ebx, 0
jmp EndLt3
Lt3:
mov ebx, 1
EndLt3:
cmp ebx, 1
jne EndWhile2
mov ebx, [ebp-16]
mov ecx, [ebp-12]
mov esi, a
mov edx, [esi+4*ecx]
add ebx, edx
mov [ebp-16], ebx
mov ecx, [ebp-12]
mov edx, 1
add ecx, edx
mov [ebp-12], ecx
jmp While2
EndWhile2:
mov ecx, [ebp-16]
mov eax, ecx

;print return value
push eax
push ReturnMsg
call printf
add esp,4
pop eax

;boilerplate, epilogue
pop edi
pop esi
pop ebx
mov esp,ebp
pop ebp
ret

