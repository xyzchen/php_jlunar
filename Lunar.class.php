<?php 
//===================================================
//    公历转换成农历(使用jlunar扩展)
//         陈逸少
//       2011-08-01
//===================================================
class Lunar
{
	//---------------------------------------------------------
	// 公历数据
	public  $year; 	//公历: 年, 十进制，例如 2000
	public  $month;	//公历: 月, 十进制(1~12)，例如 10
	public  $day;		//公历: 日, 十进制(1~31)，例如 1
	public  $weekday; //公历: 星期, 整数 , 0 - 星期日, 1~6 - 星期一 ~ 星期六
	// 农历数据
	public  $lunarYear;	 // 农历年，如 2000
	public  $lunarMonth;  // 农历月，如 12, 1 ~ 12
	public  $lunarDay;	 // 农历日，如 13, 1 ~ 30
	public  $lunarIsLeapMonth; // 是否是闰月， 1 为农历闰月, 0 为非闰月
	/**
	 +----------------------------------------------------------
     * 架构函数
     * 创建一个 Lunar 对象
     +----------------------------------------------------------
     */
    public function __construct($year='', $month='', $day='') 
	{
		//获取当前日期
		$datestring = date("Y-m-d");
        list($y, $m, $d) = preg_split("/-/", $datestring);
        //检测参数
		if(empty($year))
		{
			$year  = intval($y, 10);
		}
		if(empty($month))
		{
			$month  = intval($m, 10);
		}
		if(empty($day))
		{
			$day  = intval($d, 10);
		}
        //使用指定日期
        $this->getLunarDate($year, $month, $day);
    }
	///////////////////////////////////////////////////////////////////
	//--------------------------------------------------------
	//    从公历到农历计算, 
	//        当天的农历年数应该和y相等
	//---------------------------------------------------------
	public function getLunarDate($y, $m, $d)
	{
    	$y = ($y < 1900) ? 1900 : $y;
    	// 保存公历信息
        $this->year  = $y;
        $this->month = $m;
        $this->day   = $d;
		// 使用扩展库计算当年的春节日期
		$data = lunar_get_lunardate($y, $m, $d);
		// 填充星期信息
		$this->weekday = $data['weekday'];
		// 填充农历信息
		$this->lunarYear  = $data['lunar_year'];	//年
		$this->lunarMonth = $data['lunar_month'];	//月
		$this->lunarDay   = $data['lunar_day'];		//日
		$this->lunarIsLeapMonth = $data['lunar_isleap'];//是否闰月
		// 返回自身
		return $this;
	}
	//-----------------------------------------------------------
	//  完成从 农历 到 公历的转换
	//     参数:
	//		$ly, $lm, $ld: 农历年月日
	//-----------------------------------------------------------
	public function getSolarDate($ly, $lm, $ld, $isleapmonth = 0)
	{
		// 填充农历年月日
		$this->lunarYear  = $ly;		//年
		$this->lunarMonth = $lm;		//月
		$this->lunarDay   = $ld;		//日
		$this->lunarIsLeapMonth = $isleapmonth;//闰月
		//计算公历
		$data = lunar_get_solardate($ly, $lm, $ld, $isleapmonth);
		// 填充公历年月日 星期
		$this->year  = $data['year'];
		$this->month = $data['month'];
		$this->day   = $data['day'];
		$this->weekday = $data['weekday'];
		//返回
		return $this;
	}
	
	//-----------------------------------------------------------
	//     获取 距离 1900年1月1日 days 天的日期
	//         1900年1月1日为1
	//-----------------------------------------------------------
	public function getOffsetDate($days)
	{
		$data = lunar_get_date($days);
		// 填充公历年月日 星期
		$this->year  = $data['year'];
		$this->month = $data['month'];
		$this->day   = $data['day'];
		$this->weekday = $data['weekday'];
		// 填充农历信息
		$this->lunarYear  = $data['lunar_year'];	//年
		$this->lunarMonth = $data['lunar_month'];	//月
		$this->lunarDay   = $data['lunar_day'];		//日
		$this->lunarIsLeapMonth = $data['lunar_isleap'];//是否闰月
		//返回自身
		return $this;		
	}

	//----------------------------------------------
	//  增加或减少 $d 天
	//----------------------------------------------
	public function getDiffDate($d)
	{
		if(empty($d) ||($d == 0))
		{
			return $this;
		}
		// 计算当天是 1900-1-1 后的第几天(1900-1-1为1)
		$offdays1 = self::getOffsetSolarDays($this->year, $this->month, $this->day) + $d;
		return $this->getOffsetDate($offdays1);
	}
	
	//----------------------------------------------
	//  后一天
	//----------------------------------------------
	public function getNextDate()
	{
		return $this->getDiffDate(1);
	}
	/**
     +----------------------------------------------------------
     *  判断日期 所属 星期 星座 干支 生肖 月 日
     *  type 参数：WN 星期 XZ 星座 GZ 干支 SX 生肖  MN 月 DN 日 
     *
     +----------------------------------------------------------
     * @access public
     +----------------------------------------------------------
     * @param string $type  获取信息类型
     +----------------------------------------------------------
     * @return string
     +----------------------------------------------------------
     */
	public function magicInfo($type)
	{
		// 公历数据    
        $y  = $this->year;
        $m  = $this->month;        
        $d  = $this->day;         
        $w  = $this->weekday;
		// 农历数据
		$ly =  $this->lunarYear;	// 农历年，如 2000
		$lm =  $this->lunarMonth;	// 农历月，如 12, 1 ~ 12
		$ld =  $this->lunarDay;		// 农历日，如 13, 1 ~ 30
		$lpm = $this->lunarIsLeapMonth; // 是否是闰月， 1 为农历闰月, 0 为非闰月       
      	 
		$result = '';
        switch ($type)
        {
        case 'WN'://星期
        	$WNDict = array("日","一","二","三","四","五","六");
            $result = '星期' . $WNDict[$w];
            break;
            
        case 'XZ'://星座
            $XZDict = array('摩羯','宝瓶','双鱼','白羊','金牛','双子','巨蟹','狮子','处女','天秤','天蝎','射手');
            $Zone   = array(1222,122,222,321,421,522,622,722,822,922,1022,1122,1222);
            if((100*$m+$d)>=$Zone[0]||(100*$m+$d)<$Zone[1])
            {
            	 $i=0;
            }                
            else
            {
                for($i=1;$i<12;$i++)
                {
                	if((100*$m+$d)>=$Zone[$i]&&(100*$m+$d)<$Zone[$i+1])
                  		break;
                }
            }
            $result = $XZDict[$i].'座';
            break;

        case 'GZ'://干支, 用农历年计算
            $GZDict = array(
                        array('甲','乙','丙','丁','戊','己','庚','辛','壬','癸'),
                        array('子','丑','寅','卯','辰','巳','午','未','申','酉','戌','亥')
                        );
            $i= $ly -1900 + 36 ;
            $result = $GZDict[0][$i%10].$GZDict[1][$i%12];
            break;

        case 'SX'://生肖, 用农历年计算
            $SXDict = array('鼠','牛','虎','兔','龙','蛇','马','羊','猴','鸡','狗','猪');
            $result = $SXDict[($ly-4)%12];
            break;
                       
       case 'MN'://农历月份
        	$MNDict = array('', '正','二','三','四','五','六','七','八','九','十','冬','腊');
            if($lpm == 1)
            {
            	$result = '闰' . $MNDict[$lm]. '月';	
            }
            else
            {
            	$result = $MNDict[$lm]. '月';	
            }
            break;
        
        case 'DN'://农历日期
        	$DNDict =  array(   '',
								'初一','初二','初三','初四','初五','初六','初七','初八','初九','初十',
								'十一','十二','十三','十四','十五','十六','十七','十八','十九','二十',
								'廿一','廿二','廿三','廿四','廿五','廿六','廿七','廿八','廿九','三十'
							);
			$result = $DNDict[$ld];
			break;
        }
        return $result;
    }

	//----------------------------------
	//获取当天的农历传统节日字符串
	//----------------------------------
	public function getLunarHolidayName()
	{
		/* 农历传统节日数据　*/
		$stLunarHoliday = array(
			array(0,  0, ""),//0, 无节日
			array(1,  1,  "春节"),//1
			array(1,  15, "元霄节"),//2
			array(5,  5,  "端午节"),//3
			array(7,  7,  "七夕节"),//4
			array(8,  15, "中秋节"),//5
			array(9,  9,  "重阳节"),//6
			array(12, 8,  "腊八节"),//7
		);
		for($id = 0; $id < count($stLunarHoliday); $id++)
		{
			if(($this->lunarMonth == $stLunarHoliday[$id][0])&&($this->lunarDay == $stLunarHoliday[$id][1]))
			{
				return $stLunarHoliday[$id][2];
			}
		}
		return false;
	}
	
	//----------------------------------
	//获取当天的公历节日字符串
	//----------------------------------
	public function getSolarHolidayName()
	{
		/* 农历传统节日数据　*/
		$stSolarHoliday = array(
			array(0,  0, ""),//0, 无节日
			array(1,  1,  "元旦"),//1
			array(2,  14, "情人节"),
			array(3,  8,  "妇女节"),//3
			//array(4,  1,  "愚人节"),
			array(5,  4,  "青年节"),//5
			array(6,  1,  "儿童节"),//
			array(7,  1,  "建党节"),//
			array(8,  1,  "建军节"),//
			array(9,  10, "教师节"),//
			array(10, 1,  "国庆节"),//10
			array(12, 25, "圣诞节"),
		);
		for($id = 0; $id < count($stSolarHoliday); $id++)
		{
			if(($this->month == $stSolarHoliday[$id][0])&&($this->day == $stSolarHoliday[$id][1]))
			{
				return $stSolarHoliday[$id][2];
			}
		}
		return false;
	}
	
	//----------------------------------------------------
    //获取当前日期字符串
    //-----------------------------------------------------
	public function getDateString()
	{
		//公历日期
		$strday  = $this->year . '年' . $this->month . '月' . $this->day . '日';
		//农历日期
		$strweek = $this->magicInfo('WN');
		$strgz   = $this->magicInfo('GZ');
		$strsx   = $this->magicInfo('SX');
		$strmn   = $this->magicInfo('MN');
		$strdn   = $this->magicInfo('DN');
		//农历日期
		$strlday =  $strgz . '(' . $strsx .')年' .  $strmn . $strdn;
		//返回字符串
	    return $strday . ' ' . $strlday . ' ' . $strweek;
	}
	////////////////////////////////////////////////////////////////////////
	///下面的是静态函数
	////////////////////////////////////////////////////////////////////////
    //--------------------------------------------
	// 计算 公历 y年m月的天数   
	//     参数:  y  - 年, 1900 ~ 2100
	//            m  - 月, 1    ~ 12
	//--------------------------------------------
	public static function getSolarMonthDays($y, $m) 
	{
		return @lunar_get_solar_daysofmonth($y, $m);
	}
	
	//-------------------------------------------
	// 计算公历某年的天数
	//-------------------------------------------
	public static function getSolarYearDays($y)
	{
		if((($y % 4 == 0) && ($y % 100 != 0)) || ($y % 400 == 0))
		{
			return 366;	// 公历闰年
		}
		return 365;	//公历平年
	}
		
	//------------------------------------------------------
	//  计算 公历 y-m-d 到 1900-1-0的天数
	//   
	//     参数: 公历的年月日 1900-1-1 ~ 2100-12-31 之间
	//
	//     返回:
	//          天数, 一个正数值 1900-1-1为 1
	//          
	//-----------------------------------------------------
	public static function getOffsetSolarDays($y, $m, $d)
	{
		return @lunar_get_offset_solardays($y, $m, $d);
	}
	
	//-------------------------------------------------------
	//  计算公历 y 年 m 月 d 日 是星期几 (0=星期天)
	//-------------------------------------------------------
	public static function getWeekday($y, $m, $d)
	{
		// 计算到初始时间 1900年1月1日的天数：1900-1-1(星期一)---*/
		return @lunar_get_weekday($y, $m, $d);
	}
	
	//-------------------------------------------------------
	//   返回农历 y 年 闰几月(1 ~ 12), 没有返回0
	//-------------------------------------------------------
	public static function getLeapMonth($y)
	{
		return @lunar_get_leapmonth($y);
	}
	
	//-------------------------------------------------------
	//  计算农历某年某月的天数
	//      月分 1~ 13, 必须有13个月时13才有意义
	//-------------------------------------------------------
	public static function getLunarMonthDays($lunarY, $lunarM)
	{
		return @lunar_get_lunar_daysofmonth($lunarY, $lunarM);
	}
	
	//-------------------------------------------------------
	// 计算农历某年的天数
	//-------------------------------------------------------
	public static function getLunaYearDays($lunarY)
	{
		return @lunar_get_lunar_daysofyear($lunarY);
	}
	
	//-------------------------------------------------------
	//  计算农历 y年 春节的 公历日期
	//      返回: list(month, day)
	//-------------------------------------------------------
	public static function getSpringDate($y)
	{
		// 返回
		return @lunar_get_spring($y);
	}
	
	//---------------------------------------------------------------
	//  计算农历 y年m月d日到农历 1900年正月初一(公历1900-1-31)的天数
	//    当天到当天为 1
	//    这里不区分闰月, 农历月份为 1 ~ 13
	//---------------------------------------------------------------
	public static function getOffsetLunarDays($year, $month, $day)
	{
		$days = 0;
		// 计算 year 之前的整年数
		for($y = 1900; $y < $year; $y++)
		{
			$days += self::getLunaYearDays($y);
		}
		// 计算之前的月的
		for($m = 1; $m < $month; $m++)
		{
			$days += self::getLunarMonthDays($year, $m);
		}
		// 加当月天数
		$days += $day;
		return $days;
	}
	
	////////////////////////////////////////////////////////////
	//  其他的辅助函数
	////////////////////////////////////////////////////////////
	//-------------------------------------------------------
	//获取指定年,月的月历第一天(从星期天开始)
	//-------------------------------------------------------
	public static function getMonthFirstday($year, $month)
	{
		$lu = new Lunar($year, $month, 1);
		if($lu->weekday != 0)
		{
			$lu->getDiffDate(0 - $lu->weekday);
		}
		return $lu;
	}
	////////////////////////////////////////////////////////////
	//  24节气计算
	////////////////////////////////////////////////////////////
	//-----------------------------------------------------
	//   功能: 获取 y 年 m 月 d 日 的 节气字符串
	//        如果不是节气日, 返回 NULL
	//
	//   参数: $y:  年号, 如 2004
	//         $m: 月份, 1 ~ 12
	//         $d:   日期, 1 ~ 31
	//----------------------------------------------------
	public static function getTermName($y, $m, $d)
	{
		$szLunarJieqi = array( // 0 ~ 23 ,以 0 小寒 起算
					"小寒",
					"大寒", // 一月的节气
					"立春",
					"雨水", // 二月的节气
					"惊蛰",
					"春分",
					"清明",
					"谷雨",
					"立夏",
					"小满",
					"芒种",
					"夏至",
					"小暑",
					"大暑",
					"立秋",
					"处暑",
					"白露",
					"秋分",
					"寒露",
					"霜降",
					"立冬",
					"小雪",
					"大雪",
					"冬至",
				);
		$n = 0;
		if($d < 15)
		{
			$n = ($m - 1) * 2;
		}
		else
		{
			$n = $m * 2 - 1;
		}
		if(@lunar_get_term_yn($y, $n) == $d)
		{// 是一个节气
			return $szLunarJieqi[$n];
		}
		return false;
	}
}

?>
