let x;
function vvod()
{
x=prompt("������ �������� X �� �����");
if(x == ''){
alert("������ ���� ��� ����� ����� � ���� ����� ����.");}
else if(isNaN(x) != 0){
alert("������ ���� ��� ����� ����� � ���� ����� ����.");}
else if(Math.sign(x) == 0 || Math.sign(x) == -1 || Math.sign(x) == -0){
alert("������ �� ������� � �� ��'���� �����.")}
}
function log()
{
if(x == undefined){
alert("������ ����� X.");}
else if(isNaN(x) == 0){
alert("logX = "+Math.log(x).toFixed(3));}
else if(isNaN(x) != 0){
alert("������ ���� ��� ����� ����� � ���� ����� ����.");}
}