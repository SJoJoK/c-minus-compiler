SECTION .data
                                                
OutputMsg: db "Output Value:%i",10,0
                                   
                                   
                                   
                                   
                                   
                                   
                                   
                                   
                                   
                                   

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

global factorial
factorial:
;boilerplate prologue
push ebp
mov ebp, esp
push ebx
push esi
push edi
sub esp, 16

mov eax, [ebp+8]
mov ebx, 1
cmp eax, ebx
je Equ0
mov eax, 0
jmp EndEqu0
Equ0:
mov eax, 1
EndEqu0:
cmp eax, 1
jne EndIf1
mov eax, 1
mov [ebp-12], eax
jmp EndIfElse1
EndIf1:
mov eax, [ebp+8]
mov ebx, [ebp+8]
mov ecx, 1
sub ebx, ecx

;precall
;save required resgisters, if any
push eax
;push parameters
push ebx
call factorial

;postcall
;store return value
mov ebx, eax

;clear stack of parameters
add esp, 4

;restore used resgisters, if any
pop eax

imul eax, ebx
mov [ebp-12], eax
EndIfElse1:
mov eax, [ebp-12]

;precall
;save required resgisters, if any
;push parameters
push eax
call output

;postcall
;store return value

;clear stack of parameters
add esp, 4

;restore used resgisters, if any

mov ebx, [ebp-12]
mov eax, ebx

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

mov eax, 4
mov [ebp-16], eax
mov eax, [ebp-16]

;precall
;save required resgisters, if any
;push parameters
push eax
call factorial

;postcall
;store return value

;clear stack of parameters
add esp, 4

;restore used resgisters, if any

mov [ebp-16], eax
mov eax, 0

;boilerplate, epilogue
pop edi
pop esi
pop ebx
mov esp,ebp
pop ebp
ret

