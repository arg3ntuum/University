format PE64 console
entry start

section '.data' data writable
 a dd 5
 b dd 2
 x dd 0
section '.text' code executable
start:
mov eax,[a] ;�������� � ������ �������� �
cmp eax,[b] ;��������� �������� � � b
 jl a2 ;������� �� ���� �2, ���� �<b
 jg a1 ;������� �� ���� �1, ���� a>b
 je a3 ;������� �� ���� �3, ���� a=b
;==================== a<b ============================
a1:
 cmp [a], 0 ;�������� ������ �� ����
 je exit ;���� b=0, �� ���������� �� �����


 mov eax, [b]
 cdq ;���������� ������ EAX
 idiv [a] ;����� �� a: b/a
 add eax, 10 ;������ 10  b/a+10
 mov [x], eax ;�������� �������� ����������
 jmp exit ;������� �� �����
;==================== a>b ============================
a2:
 cmp [b], 0 ;�������� ������ �� ����
 je exit ;���� �=0, �� ���������� �� �����
 mov eax, [a] ; �������� � �� ��������
 imul eax, 2 ; 2*a
 sub eax, 5 ;2 * a - 5
 cdq ;���������� ������ EAX
 idiv [b] ; ����� �� �
 mov [x], eax ;�������� �������� ����������
 jmp exit
;==================== a=b ============================
a3:
 mov [x], 3425 ;�������� �������� ���������� -2
 mov eax, 3425
exit:
       ; call [getch]
    xor eax, eax

  mov     eax, 0x1
  mov     ebx, 0
  int     0x80
