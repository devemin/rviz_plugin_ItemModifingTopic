# rviz_plugin_ItemModifingTopic
This is a rviz plugin. Topic for modifing rviz's item. (by std_msgs/String )

rviz 用のプラグインです。

文字列を送ることで、rviz のアイテムのチェックボックスやテキストを動的に変更できます。

rviz 画面で「Add」->「ItemModifingTopic」を追加すると、

/rviz_itemmod ( type: std_msgs/String ) というトピックが出来上がるので、

>>例：
>>
>>●RobotModel の表示を消す
>>
>>rostopic pub -1 /rviz_itemmod std_msgs/String "data: 'RobotModel,Visual Enabled,false'" 
>>
>>●RobotModel の表示を消したのを戻す
>>
>>rostopic pub -1 /rviz_itemmod std_msgs/String "data: 'RobotModel,Visual Enabled,true'" 
>>
>>●Grid を消す
>>
>>rostopic pub -1 /rviz_itemmod std_msgs/String "data: 'Grid,false'" 

また、Python (rospy) から Topic を送るサンプルスクリプトも置いておきます。（ src/testStringPub.py ）
