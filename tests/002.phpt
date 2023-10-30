--TEST--
lunar_get_today() Basic test
--EXTENSIONS--
jlunar
--FILE--
<?php
$ret = lunar_get_today();

var_dump($ret);
?>
--EXPECT--
The extension jlunar is loaded and working!
NULL
