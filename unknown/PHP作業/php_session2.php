<?php
session_start();
//執行登入動作
if(!isset($_SESSION["membername"]) || ($_SESSION["membername"]=="")){
	if(isset($_POST["username"]) && isset($_POST["passwd"])){
		//預設帳號密碼
		$username = "admin";
		$passwd = "1234";
		//比對帳號密碼，若登入成功則呈現登入狀態
		if(($_POST["username"]==$username) && ($_POST["passwd"]==$passwd)){
			$_SESSION["membername"]=$username;
		}
		header("Location: php_session2.php");
	}
}
//執行登出動作
if(isset($_GET["logout"]) && ($_GET["logout"]=="true")){
	unset($_SESSION["membername"]);
	header("Location: php_session2.php");
}
?>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=big5" />
	<title>網站會員系統</title>
</head>
<body>
<?php 
//檢查是否為登入狀態，若未登入則顯示登入表單
if(!isset($_SESSION["membername"]) || ($_SESSION["membername"]=="")){
?>		
<form id="form1" name="form1" method="post" action="php_session2.php">
  <table width="300" border="0" align="center" cellpadding="5" cellspacing="0" bgcolor="#F2F2F2">
    <tr>
      <td colspan="2" align="center" bgcolor="#CCCCCC"><font color="#FFFFFF">會員系統</font></td>
    </tr>
    <tr>
      <td width="80" align="center" valign="baseline">帳號</td>
      <td valign="baseline"><input type="text" name="username" id="username" /></td>
    </tr>
    <tr>
      <td width="80" align="center" valign="baseline">密碼</td>
      <td valign="baseline"><input type="password" name="passwd" id="passwd" /></td>
    </tr>
    <tr>
      <td colspan="2" align="center" bgcolor="#CCCCCC"><input type="submit" name="button" id="button" value="登入" />
      <input type="reset" name="button2" id="button2" value="重設" /></td>
    </tr>
  </table>
</form>
<?php 
//若登入即顯示登入成功訊息
}else{
?>
<table width="300" border="0" align="center" cellpadding="5" cellspacing="0" bgcolor="#F2F2F2">
  <tr>
    <td align="center" bgcolor="#CCCCCC"><font color="#FFFFFF">會員系統</font></td>
  </tr>
  <tr>
    <td align="center" valign="baseline"><?php echo $_SESSION["membername"];?> 您好，登入成功！</td>
  </tr>
  <tr>
    <td align="center" bgcolor="#CCCCCC"><a href="php_session2.php?logout=true">登出系統</a></td>
  </tr>
</table>
<?php }?>
</body>
</html>