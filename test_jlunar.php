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
echo "$str\n";
	
$str = lunar_get_today();	
var_dump($str);

$str = lunar_get_date(100);	
var_dump($str);

$str = lunar_get_lunardate(2012, 6, 29);	
var_dump($str);

$str = lunar_get_solardate(2012, 5, 12);	
var_dump($str);

$str = lunar_get_solardate(2012, 4, 18, 1);	
var_dump($str);

$spring = lunar_get_spring(2012);
var_dump($spring);

echo lunar_get_weekday(2012,6,30);
?>
