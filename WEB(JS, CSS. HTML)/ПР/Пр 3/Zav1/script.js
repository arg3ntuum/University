date=new Date();
function data()
{
let month=date.getMonth();
let day=date.getDate();
let year=date.getFullYear();
month++;
if(day<10)
day="0"+day;
if(month<10)
	month="0"+month;
let time="�������: "+day+"."+month+"."+year;
alert(time);
}
function time1()
{
let milsec=date.getTime();
alert("� ������� ��������� ���� ������ "+milsec+" ��������.");
}
function tim()
{
let hour=date.getHours();
let min=date.getMinutes();
let sec=date.getSeconds();
if(hour<10)
	hour="0"+hour;
if(min<10)
	min="0"+min;
if(sec<10)
	sec="0"+sec;
let time="�������� ���: "+hour+" : "+min+" : "+sec;
alert(time);
}
function day() 
{
let dat=date.getDay();
let days = ['�����', '��������', '³������', '�����', '�������', '�`������', '������'];//
alert(days[(dat)]);   
}
