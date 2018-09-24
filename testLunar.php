<?php 
//------------------------------------------
// Lunar.class.php 测试用例:
//------------------------------------------
include( dirname(__FILE__) . "/Lunar.class.php");
$lu = new Lunar;
//var_dump($lu);
echo $lu->getDateString(). "\r\n";
echo $lu->magicInfo('XZ') . "\r\n\n";
for($i=0; $i<30; $i++)
{
	$lu->getDiffDate(-1);
	echo $lu->getDateString() . "  ";
	echo $lu->getSolarHolidayName() . "  ";
	echo $lu->getLunarHolidayName() . "  ";
	echo Lunar::getTermName($lu->year, $lu->month, $lu->day) . "\r\n";
}
echo "---------------------------------------\n";
$lu->getSolarDate(2012, 4, 18, 1);
//var_dump($lu);
echo $lu->getDateString() . "\r\n";
echo $lu->magicInfo('XZ') . "\r\n";

echo "---------------------------------------\n";
$lu->getLunarDate(2012, 1, 8);
//var_dump($lu);
echo $lu->getDateString(). "\r\n";
echo $lu->magicInfo('XZ') . "\r\n";

echo "---------------------------------------\n";
echo "---------------------------------------\n";
$lu = new Lunar;
echo $lu->getDateString() . "\r\n";
for($i=0; $i<10; $i++)
{
	$lu->getNextDate();
	echo$lu->getDateString(). "\r\n";
}

echo "---------------------------------------\n";
$lu = Lunar::getMonthFirstday(2012, 6);
echo $lu->getDateString() . "\r\n";
var_dump($lu);


?>
