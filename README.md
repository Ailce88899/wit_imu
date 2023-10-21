# wit_imu HWT9073-CAN

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
