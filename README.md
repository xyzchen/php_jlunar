# php_jlunar
php 的农历扩展，独立出来方便更新

## 编译
```bash
phpize
./configure
make
```

## 安装
```bash
sudo make install
```

然后在 /etc/php.d/ 下添加 jlunar.ini 文件，内容为以下1行：
```conf
extension=jlunar
```
