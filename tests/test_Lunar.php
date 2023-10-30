<?php 
//------------------------------------------
// Lunar.class.php 测试用例:
//------------------------------------------
include( dirname(dirname(__FILE__)) . "/Lunar.class.php");
$lu = new Lunar;
//var_dump($lu);
echo $lu->getDateString(). "\n";
echo $lu->magicInfo('XZ') . "\n\n";
echo "\n------------- offsetDays(-1) ----------------\n";
for($i=0; $i<30; $i++)
{
	$lu->offsetDays(-1);
	echo $lu->getDateString() . "  ";
	echo $lu->getSolarHolidayName() . "  ";
	echo $lu->getLunarHolidayName() . "  ";
	echo Lunar::getTermName($lu->year, $lu->month, $lu->day) . "\n";
}
echo "\n------------- initFromLunar ----------------\n";
$lu->initFromLunar(2012, 4, 18, 1);
//var_dump($lu);
echo $lu->getDateString() . "\n";
echo $lu->magicInfo('XZ') . "\n";

echo "\n------------- initFromSolar ---------------\n";
$lu->initFromSolar(2012, 1, 8);
//var_dump($lu);
echo $lu->getDateString(). "\r\n";
echo $lu->magicInfo('XZ') . "\r\n";

echo "\n---------------- nextDate ----------------\n";
$lu = new Lunar;
echo $lu->getDateString() . "\r\n";
for($i=0; $i<10; $i++)
{
	$lu->nextDate();
	echo$lu->getDateString(). "\r\n";
}

echo "\n------------getMonthFirstday(2012, 6)-------------------\n";
$lu = Lunar::getMonthFirstday(2012, 6);
echo $lu->getDateString() . "\r\n";
var_dump($lu);
echo "\n toArray: \n\n";
//转换到 array
var_dump($lu->toArray());

?>