<?php
//取得目前路徑
$fileDir = getcwd();
//執行刪除動作
if(isset($_GET["action"])&&$_GET["action"]=="delete"){
	unlink($_GET["file"]);	
	$fileDir =pathinfo($_GET["file"],PATHINFO_DIRNAME);
	//重新轉頁到目前目錄中
	header("Location: ?dir=".$fileDir);
}
//執行上傳動作
if(isset($_GET["action"])&&$_GET["action"]=="upload"){
	if($_FILES["upload"]["error"]==0){
		move_uploaded_file($_FILES["upload"]["tmp_name"], $_POST["dir"]."\\".$_FILES["upload"]["name"]);
	}
	//重新轉頁到目前目錄中
	header("Location: ?dir=".$_POST["dir"]);
}
?>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>檔案管理</title>
</head>
<body>
<?php
//若有URL參數dir，其值即為目前路徑
if(isset($_GET["dir"])&&$_GET["dir"]!=""){
	$fileDir = $_GET["dir"];
}
//目前路徑上一層路徑
$fileUplevel = dirname($fileDir);
//取得目前路徑中的內容
$fileResource = scandir($fileDir);
echo '<table width="500" border="0" align="center" cellpadding="2" cellspacing="1" bgcolor="#000000">';
//顯示目前路徑
echo '<tr><td bgcolor="#FAFAFA"colspan="3">目前路徑：'.$fileDir.'</td></tr>'; 
echo '<tr><td bgcolor="#FAFAFA"colspan="3" align="center">';
//設定URL參數action為upload
echo '<form action="?action=upload" method="post" enctype="multipart/form-data" name="form1" id="form1">';
//將上一層路徑帶進連結的URL參數dir中
echo '<a href="?dir='.$fileUplevel.'">上一層</a> | ';
echo '上傳檔案 <input type="file" name="upload" style="height:20px" />';
echo '<input type="submit" name="button" style="height:20px" value="送出" />';
echo '<input name="dir" type="hidden" id="dir" value="'.$fileDir.'" /></form>';
echo '<tr><td bgcolor="#FAFAFA">名稱</td><td bgcolor="#FAFAFA" width="120" align="center">檔案大小</td><td bgcolor="#FAFAFA" width="80" align="center">功能</td></tr>';
//顯示資料夾內容
foreach($fileResource as $fileName){
	if(is_dir($fileDir.'\\'.$fileName)){
		//不顯示相對路徑「.」及「..」
		if($fileName != "." && $fileName !=".."){			
			//顯示資料夾，並設定該資料夾的路徑帶進連結的URL參數dir中
			echo '<tr><td bgcolor="#FAFAFA" width="300"><a href="?dir='.$fileDir.'\\'.$fileName.'">&lt;'.$fileName.'&gt;</a></td>';
			echo '<td bgcolor="#FAFAFA" width="120">&nbsp;</td><td bgcolor="#FAFAFA" width="80">&nbsp;</td></tr>';
		}
	}
}
//顯示檔案的內容
foreach($fileResource as $fileName){
	if(is_file($fileDir.'\\'.$fileName)){
		//計算檔案大小
		$fsize = filesize($fileDir.'\\'.$fileName);
		//顯示檔案名稱
		echo '<tr><td bgcolor="#FAFAFA" width="300">'.$fileName.'</td>';
		//顯示檔案大小，並以千位符號格式化顯示
		echo '<td bgcolor="#FAFAFA" width="120" align="right">'.number_format($fsize).' bytes</td>';
		//在刪除文字上加上連結，並設定該資料夾的路徑帶進連結的URL參數dir、參數action為delete
		echo '<td bgcolor="#FAFAFA" width="80" align="center"><a href="?file='.$fileDir.'\\'.$fileName.'&action=delete">刪除</a></td></tr>';
	}
}
echo '</table>';
?>
</body>
</html>