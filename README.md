# php_jlunar
php 的农历扩展，独立出来方便更新

##编译
phpize
./configure CC=g++ [--with-php-config=/usr/local/php/bin/php-config]
make


##安装
sudo make install

然后在 /etc/php.d/ 下添加 jlunar.ini 文件，内容为以下两行：
; Enable jlunar extension module
extension=jlunar.so



