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
## 关于可能出现libserial.so问题解决方法
在新的电脑测试IMU中出现了如下错误：
```
error while loading shared libraries:libserial.so：cannot open shared object file:No such file or directory
```
是因为找不到共享库，即.so文件，可通过如下方式设置共享库的搜索路径,查询libserial.so文件路径,会有多条路径，我们只关注usr/local
```
locate libserial.so
```
编辑/etc/ld.so.conf文件
```
sudo gedit /etc/ld.so.conf
```
在出现的文件最后添加一行libserial.so文件路径,并保存
```
/usr/local/lib/libserial.so
```
运行ldconfig，更新/etc/ld.so.cache
```
sudo ldconfig
```