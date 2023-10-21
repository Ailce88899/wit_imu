//#include "ros/ros.h"
#include "rclcpp/rclcpp.hpp"
//#include "std_msgs/String.h"
#include "std_msgs/msg/string.hpp"
#include <serial/serial.h>
#include <HWT9073.h>
//# include "sensor_msgs/Imu.h"
#include "sensor_msgs/msg/imu.hpp"
#include <sstream>
//#include "tf/transform_datatypes.h"
#include "tf2/transform_datatypes.h"
#include "tf2/LinearMath/Quaternion.h"
serial::Serial ser; //声明串口对象 
using ImuMsg = sensor_msgs::msg::Imu;
extern int angle_tip; 
//回调函数 
void write_callback(const std_msgs::msg::String::ConstPtr& msg) 
{ 
    //ROS_INFO_STREAM("Writing to serial port" <<msg->data); 
    ser.write(msg->data);   //发送串口数据 
} 
extern char sum;
int main(int argc, char **argv)
{
   	//初始化节点 
    //ros::init(argc, argv, "serial_imu_node"); 
    //声明节点句柄 
    //ros::NodeHandle nh;
    rclcpp::init(argc,argv);
    auto node = rclcpp::Node::make_shared("imu_com");
     
    //订阅主题，并配置回调函数 
    //ros::Subscriber IMU_write_pub = nh.subscribe("imu_command", 1000, write_callback); 
    //rclcpp::Subscription<ImuMsg>::SharedPtr IMU_write_pub = node->create_subscription<ImuMsg>("imu_command", 1000, write_callback);
    //发布主题, 消息格式使用sensor_msg::Imu标准格式（topic名称，队列长度）
    //ros::Publisher IMU_read_pub = nh.advertise<sensor_msgs::Imu>("imu/data_raw", 1000);
    rclcpp::Publisher<ImuMsg>::SharedPtr IMU_read_pub = node->create_publisher<ImuMsg>("imu/data_raw", 1000);
    //打开串口
    try 
    { 
    //设置串口属性，并打开串口 
        ser.setPort("/dev/ttyUSB0"); 
        ser.setBaudrate(230400); 
        serial::Timeout to = serial::Timeout::simpleTimeout(1000); 
        ser.setTimeout(to); 
        ser.open(); 
    } 
    catch (serial::IOException& e) 
    { 
        //ROS_ERROR_STREAM("Unable to open port "); 
        RCLCPP_ERROR(node->get_logger(),"Unable to open port ");
        exit(0); 
    } 

    //检测串口是否已经打开，并给出提示信息 
    if(ser.isOpen()) 
    { 
        //ROS_INFO_STREAM("Serial Port initialized"); 
        RCLCPP_INFO(node->get_logger(),"Serial Port initialized");
    } 
    else 
    { 
        RCLCPP_ERROR(node->get_logger(),"Unable to initial Serial port ");
        exit(0); 
    } 
    unsigned short  data_size;
    unsigned char   tmpdata[2000] ;
    float           roll,pitch,yaw;
    //消息发布频率
	//ros::Rate loop_rate(100);
    rclcpp::Rate loop_rate(100);
    while (rclcpp::ok()){
		//处理从串口来的Imu数据
		//串口缓存字符数
        if(data_size = ser.available()){ //ser.available(当串口没有缓存时，这个函数会一直等到有缓存才返回字符数
            ser.read(tmpdata, data_size);
            HWT9073.CopeSerialData( tmpdata,data_size);   //HWT9073 imu 库函数
           //打包IMU数据
            //sensor_msgs::Imu imu_data;
            sensor_msgs::msg::Imu imu_data;
            //imu_data.header.stamp = ros::Time::now();
            imu_data.header.stamp = node->now();
            imu_data.header.frame_id = "imu_link";
            roll  =  (float)HWT9073.stcAngle0.Angle0/1000;
            pitch =  (float)HWT9073.stcAngle1.Angle1/1000;
            yaw   =  (float)HWT9073.stcAngle2.Angle2/1000;
	    //    ROS_INFO("roll:%.3f  pitch:%.3f  yaw:%.3f  \r\n",roll ,pitch,yaw);//打印欧拉角
	    tf2::Quaternion q;
            q.setRPY(roll, pitch, yaw);
            imu_data.orientation.x = q.x();
            imu_data.orientation.y = q.y();
            imu_data.orientation.z = q.z();
            imu_data.orientation.w = q.w();
           
      //      ROS_INFO("QX:%.3f  QY:%.3f  QZ:%.3f QW:%.3f \r\n\r\n", imu_data.orientation.x,imu_data.orientation.y,imu_data.orientation.z,imu_data.orientation.w);

           imu_data.angular_velocity.x = (double)HWT9073.stcGyro.w[0]/32768*2000*3.1415/180;
           imu_data.angular_velocity.y = (double)HWT9073.stcGyro.w[1]/32768*2000*3.1415/180;
           imu_data.angular_velocity.z = (double)HWT9073.stcGyro.w[2]/32768*2000*3.1415/180;
 
           imu_data.linear_acceleration.x = (double)HWT9073.stcAcc.a[0]/32768*16*9.8;
           imu_data.linear_acceleration.y = (double)HWT9073.stcAcc.a[1]/32768*16*9.8;
           imu_data.linear_acceleration.z = (double)HWT9073.stcAcc.a[2]/32768*16*9.8;
           //发布topic
           //IMU_read_pub.publish(imu_data);
           IMU_read_pub->publish(imu_data);
        }
        //处理ROS的信息，比如订阅消息,并调用回调函数 
        //ros::spinOnce(); 
        rclcpp::spin_some(node);
        loop_rate.sleep(); 
  }
  	return 0;
 }

