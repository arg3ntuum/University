let znachenie = "", cifri_znach = "", vikon_koduv = 0;
function vvod(){
	znachenie=prompt("������ ����� � �������� ������ 'OK'");
}
function koduvannya(){
	vikon_koduv = 1;
	for (let i = 0; znachenie.length > i; i++){
		cifri_znach += znachenie.charCodeAt(i);
                cifri_znach += ' ';
	}
}
function vvivod(){
	if (vikon_koduv === 1)
		alert("���: "+ cifri_znach);
	else if (znachenie === "")
		alert("������ ����� �������");
	else if (vikon_koduv === 0)
	alert("��������� �� ���� ��������");
}