#!/bin/bash

echo 'Building...'
phpize
./configure --enable-php-helloworld
make
sudo make install
echo "




"
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""

 php -d extension=php_helloworld.so -r 'php_helloworld("/home/assada/phpext");' 