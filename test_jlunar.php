<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('jlunar'))
{
	dl('php_jlunar.' . PHP_SHLIB_SUFFIX);
}
$module    = 'jlunar';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func)
{
    echo $func."$br\n";
}
echo "$br\n";

$str = lunar_get_todaystring();
echo "lunar_get_todaystring(): {$str}\n";
	
$str = lunar_get_today();
echo "\nlunar_get_today():\n";
var_dump($str);

$str = lunar_get_date(100);	
echo "\nlunar_get_date(100):\n";
var_dump($str);

$str = lunar_get_lunardate(2012, 6, 29);
echo "\nlunar_get_lunardate(2012, 6, 29):\n";	
var_dump($str);

$str = lunar_get_solardate(2012, 5, 12);
echo "\nlunar_get_solardate(2012, 5, 12):\n";	
var_dump($str);

$str = lunar_get_solardate(2012, 4, 18, 1);
echo "\nlunar_get_solardate(2012, 4, 18, 1):\n";
var_dump($str);

$spring = lunar_get_spring(2012);
echo "\nlunar_get_spring(2012):\n";
var_dump($spring);

$str = lunar_get_weekday(2012,6,30);
echo "\nlunar_get_weekday(2012,6,30): {$str}\n";

?>
