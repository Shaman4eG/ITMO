<?php

	function placeholders($filename, $placeholders){
		return strtr(file_get_contents($filename), $placeholders);
	}

	$start = microtime();//$time;

	$r =  $_POST['realR'];
	$x =  $_POST['realX'];
	$y =  $_POST['realY'];

	$rh     = $r / 2;

	$result = ((($x >= -$r) && ($y >= -$r) && ($x <= 0) && ($y <= 0)) ||
			  (($x <= rh) && ($x >= 0) && ($y <= sqrt($rh * $rh - $x * $x)) && ($y >= ($x - $rh))));

	$finish     = microtime();
	$total_time = round(($finish - $start), 4);

	echo placeholders("result.html", array(
		"{{CURRENT_TIME}}" => date('Y-m-d H:i:s'),
		"{{LOAD_TIME}}" => $total_time,
		"{{R}}" => $r,
		"{{X}}" => $x,
		"{{Y}}" => $y,
		"{{RESULT}}" => ($result ? "попало" : "не попал")
	));
?>