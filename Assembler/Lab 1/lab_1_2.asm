format PE console
entry main
include 'win32a.inc'

section '.data' data readable writeable
;resStr db 'Result: %d', 0
    a    dd 4    ; ����� �����
    b    dd 2    ; ����� �����
    k    dd 1    ; ���� �����
    result dd ?

section '.code' code readable executable
main:
     ;y = (b/2-2/k)/(b-a*k+1) ;�������� 53 �� 2
               ;9/15    2 - 3
        ;b/2
    mov eax, [b]
    cdq
    mov ecx, 2
    idiv ecx
    mov [result], eax  ;result �������� �� b/2

        ;53/k
    mov eax, 2
    cdq
    mov ecx, [k]
    idiv ecx        ;eax �� 53/k

    neg eax ;eax �� -(53/k)


    add [result], eax  ; result = (b/2-53/k)

    mov eax, [a]
    imul eax, [k]
    inc eax
    sub [b], eax

    xor eax, eax
    mov eax, [result];9
    cdq
    mov ecx, [b]         ;15
    idiv ecx
    mov [result], eax


    ; ���� ����� � ������� �� �����������, ������� ���������
   ; push resStr
    ;push eax
    ;call [printf]


    jmp     exit


exit:

    invoke ExitProcess, 0

section '.idata' import data readable
         library kernel, 'kernel32.dll',\
                 msvcrt, 'msvcrt.dll'

         import kernel,\
                ExitProcess, 'ExitProcess'

         import msvcrt,\
                printf, 'printf',\
                scanf, 'scanf',\
                getch, '_getch'