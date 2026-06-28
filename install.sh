#!/bin/bash
echo "Update the package list"
sudo apt-get update
echo "installing required programs"
sudo apt-get install \
  build-essential \
  cmake \
  extra-cmake-modules \
  gettext \
  g++ \
  libkf5config-dev \
  libkf5configwidgets-dev \
  libkf5i18n-dev \
  libkf5kio-dev \
  libkf5widgetsaddons-dev \
  libkf5xmlgui-dev \
  libqt5sql5-mysql \
  qtbase5-dev \
  qttools5-dev \
  -y
echo "installing mysql"
sudo apt-get install mariadb-client mariadb-server -y
echo "begin build"
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make
echo "installing IOTPOS"
sudo make install
echo "install complete now to setup database"
cd ..
cd database_resources
cat iotpos_mysql.sql | sudo mysql -u root -p
echo "all done :)"
