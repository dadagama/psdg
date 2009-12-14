<?php 
	session_start();	
	if(isset($_REQUEST['logout']) && $_REQUEST['logout'] != "")
	{
		session_destroy();
	}
?>