let n;
function inp()
{
n=prompt("������ �������� ������ ����������� ����� N �� ���� ����� � �������� ������ 'OK'");
}
function factorial(){
 let result = 1;
    while(n){
        result *= n--;
    }
alert("N!="+result)
}