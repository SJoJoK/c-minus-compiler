SECTION .data
                                                
OutputMsg: db "Output Value:%i",10,0
a times 10 dd 0
                   
                                   
                                   
                                   
                                   
                                   
                                   
                                   
                                   
                                   

SECTION .text
extern printf
global output
output:
;boilerplate prologue
push ebp
mov ebp, esp
push ebx
push esi
push edi
sub esp, 16

mov eax, [ebp+8]

;precall
;save required resgisters, if any
;push parameters
push eax
push OutputMsg
call printf

;postcall
;store return value

;clear stack of parameters
add esp, 4

;restore used resgisters, if any


;boilerplate, epilogue
pop edi
pop esi
pop ebx
mov esp,ebp
pop ebp
ret

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
mov eax, 1
mov [ebp-12], eax
While0:
mov eax, [ebp-12]
mov ebx, 9
cmp eax, ebx
jle Lte1
mov eax, 0
jmp EndLte1
Lte1:
mov eax, 1
EndLte1:
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
mov ebx, [ebp-12]
mov ecx, 3
add ebx, ecx
mov [ebp-12], ebx
jmp While0
EndWhile0:
mov ebx, 0
mov [ebp-12], ebx
While2:
mov ebx, [ebp-12]
mov ecx, 9
cmp ebx, ecx
jle Lte3
mov ebx, 0
jmp EndLte3
Lte3:
mov ebx, 1
EndLte3:
cmp ebx, 1
jne EndWhile2
mov ebx, [ebp-12]
mov edx, a
mov ecx, [edx+4*ebx]

;precall
;save required resgisters, if any
push eax
push ebx
;push parameters
push ecx
call output

;postcall
;store return value
mov ecx, eax

;clear stack of parameters
add esp, 4

;restore used resgisters, if any
pop ebx
pop eax

mov edx, [ebp-12]
mov esi, 1
add edx, esi
mov [ebp-12], edx
jmp While2
EndWhile2:
mov edx, 0
mov eax, edx

;boilerplate, epilogue
pop edi
pop esi
pop ebx
mov esp,ebp
pop ebp
ret

