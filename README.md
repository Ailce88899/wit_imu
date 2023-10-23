# wit_imu HWT9073-CAN
## 安装serial依赖
[link](http://wjwwood.io/serial/doc/1.1.0/index.html)
Once you have gathered the dependencies, you need to checkout the software from github.com:
```
    git clone git://github.com/wjwwood/serial.git
```
Once you have checked out the source code from github.com you can enter the directory and build the software.
```
    cd serial
    make
    make test # (optional) builds the example and tests, and runs the tests.
    make doc  # (optional) builds _this_ documentation.
```
To install simply:
```
    sudo make install
```
To uninstall simply:
```
    sudo make uninstall
```

## 编译
进入wit_imu
```
colcon build
```
## 运行
连接设备HWT9073-CAN
1.查看挂载点
```
ls -l /dev/ttyUSB*
```
2.打开串口权限
```
sudo chmod +777 /dev/ttyUSB0
```
3.运行
```
cd ~/wit_imu
. install/setup.sh
ros2 run ros2_imu imu_com
```
