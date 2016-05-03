apt-get -qqy update && apt-get --qqy upgrade
sudo apt-get install -y build-essential manpages-dev 
sudo apt-get install -y libcppunit-doc libcppunit-dev gdb
sudo apt-get install -y build-essential manpages-dev 
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get -qqy update
sudo apt-get install -y gcc-4.9 g++-4.9 libcurl-dev
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9
