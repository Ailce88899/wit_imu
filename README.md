# wit_imu HWT9073-CAN
## 安装serial依赖
[link](https://blog.csdn.net/weixin_64184244/article/details/127623370)
下载ros2_serial包
```
    git clone https://github.com/ZhaoXiangBox/serial.git
```
进入serial包，进行make，依次输入以下指令
```
    cd serial
    mkdir build
    cd build
    cmake ..
    make
```
进行安装，完成后可直接调用
```
    sudo make install
```
卸载
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
