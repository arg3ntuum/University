let windows;
function openwindow()
{
 windows = window.open("window.html", "windows", "width = 1000px,height = 500px");
}

function closewindow()
{
 windows.close();
}

function sinu()
{
let sinux, x = '', podtv;
 podtv = confirm("�������� ���������� ������ ?");
 if(podtv == true)
 {
 x = prompt("������ �������� ���� � �������� � ���� �����:");
  if(x == ''|| isNaN(x) !=0)
  alert("�������� ���� �� ������� ��� �� ����� ����� �� ������.");
  else
  {
  sinux = Math.sin(x);
  alert("����� ="+sinux.toFixed(4));
  } 
 }
}