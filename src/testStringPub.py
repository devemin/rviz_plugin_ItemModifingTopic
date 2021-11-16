#!/usr/bin/env python
# coding: UTF-8
import rospy
from std_msgs.msg import String


strlist = [  \
    "RobotModel,false,", \
    "RobotModel,true,", \
    "RobotModel,Visual Enabled,false,", \
    "RobotModel,Visual Enabled,true,", \
    "RobotModel,Collision Enabled,true,", \
    "RobotModel,Collision Enabled,false,", \
    "RobotModel,Update Interval,5,", \
    "RobotModel,Update Interval,4,", \
    "RobotModel,Update Interval,3,", \
    "RobotModel,Update Interval,2,", \
    "RobotModel,Alpha,0.2,", \
    "RobotModel,Alpha,0.4,", \
    "RobotModel,Alpha,0.6,", \
    "RobotModel,Alpha,0.7,", \
    "RobotModel,Alpha,0.9,", \
    "RobotModel,Robot Description,hogehoge robot-chan :-),", \
    "RobotModel,Robot Description,robot_description,", \
    "Pose,Shape,Arrorw,", \
    "Pose,Shape,Axes,", \
    "Pose,Axes Length,1,", \
    "Pose,Axes Length,0.1,", \
    "Pose,Axes Length,0.3,", \
    "Pose,Axes Radius,0.5,", \
    "Pose,Axes Radius,0.25,", \
    "Pose,Axes Radius,0.1,", \
    "Pose,Axes Radius,0.01,", \
    "Pose,Shape,Arrorw,", \
    "Pose,Color,0; 128; 128,", \
    "Pose,Color,; 0; 255,", \
    "Pose,Color,255;255;255,", \
    "Pose,Color,255; 128; 255,", \
    "Pose,Color,255; 0; 0,", \
    "Pose,Color,128; 128; 255,", \
    "Pose,Color,0; 128; 255,", \
    "Pose,Color,0;255; 0,", \
    "Pose,Alpha,1,", \
    "Pose,Alpha,0.8,", \
    "Pose,Alpha,0.6,", \
    "Pose,Alpha,0.4,", \
    "Pose,Alpha,0.2,", \
    "Pose,Alpha,0.4,", \
    "Pose,Alpha,0.6,", \
    "Pose,Alpha,0.8,", \
    "Pose,Alpha,1,", \
    "Pose,Shaft Length, 1,", \
    "Pose,Shaft Length, 0.5,", \
    "Pose,Shaft Length, 0.1,", \
    "Pose,Shaft Length, 0.5,", \
    "Pose,Shaft Length, 1.0,", \
    "Pose,Shaft Radius, 0.05,", \
    "Pose,Shaft Radius, 0.01,", \
    "Pose,Shaft Radius, 0.10,", \
    "Pose,Shaft Radius, 0.05,", \
    "Pose,Shaft Radius, 0.10,", \
    "Pose,Head Length, 0.3,", \
    "Pose,Head Length, 0.6,", \
    "Pose,Head Length, 0.9,", \
    "Pose,Head Length, 1.2,", \
    "Pose,Head Length, 0.9,", \
    "Pose,Head Length, 0.6,", \
    "Pose,Head Length, 0.3,", \
    "Pose,Head Length, 0.1,", \
    "Pose,Head Length, 0.3,", \
    "Pose,Head Radius, 0.3,", \
    "Pose,Head Radius, 0.6,", \
    "Pose,Head Radius, 0.9,", \
    "Pose,Head Radius, 1.2,", \
    "Pose,Head Radius, 0.9,", \
    "Pose,Head Radius, 0.6,", \
    "Pose,Head Radius, 0.3,", \
    "Pose,Head Radius, 0.1,", \
    "Pose,Head Radius, 0.3" \
    ]


def talker():
    count = 0

    pub = rospy.Publisher('/rviz_itemmod', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    r = rospy.Rate(7) 
    while not rospy.is_shutdown():
        str = strlist[count]
        rospy.loginfo("pub to plugin: " + str)
        pub.publish(str)
        r.sleep()
        count += 1
        if (count >= len(strlist) ):
            count = 0

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass