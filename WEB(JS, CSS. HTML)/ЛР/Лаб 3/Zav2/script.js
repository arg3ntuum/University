let pass_koded = "", your_pass = "";
function vvod(){
	let pass=prompt("������ ����� ������ � �������� ������ 'OK'");
	if (pass === "") {
		alert("������ ������!!!");
	}
	for (let i = 0; pass.length > i; i++){
		pass_koded += pass.charCodeAt(i);
	}
}
function check(){
	let pass=prompt("������ ������ ������ � �������� ������ 'OK'");
	if (pass === "")
		alert("������ ������!!!");
	for (let i = 0; pass.length > i; i++){
		your_pass += pass.charCodeAt(i);
	}
	if (pass_koded === your_pass)
		alert("� ������ !!!");
	else alert("���� ������� !!!");
}