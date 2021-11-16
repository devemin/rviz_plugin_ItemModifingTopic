# (rviz plugin) ItemModifingTopic

<br>

## What's this ? - これは何？

rviz 用のプラグインです。

これを入れておくと、文字列を Publish する事で、

rviz のアイテムの「チェックボックス」や「テキスト」を**簡単**に、**動的**に変更できます。

<br>

```bash
1-minute to start using:

　　Topic: /rviz_itemmod 宛に、

　　Type: std_msgs/String で、

　　String.data 内に 'アイテム名,サブアイテム名,true/false/文字列'

　　といった形で文字列を並べ、 Publish して使います。

```

<br>

If you publish the string, you can modify the rviz's item!

<br>
<br>

## System - 環境

rviz

Ubuntu 18.04 / Windows 10 (Melodic) にてチェック

私は生粋の ROS 初心者です…。

<br>
<br>

## Easy Installation - 簡単インストール

```bash
$ cd ~/catkin_ws/src
$ git clone https://github.com/devemin/rviz_plugin_ItemModifingTopic.git
$ cd ..
$ catkin_make
$ 
```

<br>
<br>

# How to use - 使い方

rviz 画面で「Add」->「ItemModifingTopic」がありますので、追加すると、

/rviz_itemmod ( type: std_msgs/String ) というトピックが出来上がります。（変更可）

そのトピックに対して 文字列を下記体裁で並べて pub して下さい。

### 例：

```bash
'RobotModel,Visual Enabled,false,'

'Grid,false,'

'rvizアイテム名,サブアイテム名,指定文字列'

指定文字列は、true/True/false/False または 任意の文字列

```

### 文字列の注意点：

```bash
・カンマを増やして、ツリー構造の下にもアクセスできます

・チェックボックスとテキストだけでなく、カラータイプ（255; 255; 255 等の文字列で）、
　選択式リストボックス（文字列指定で）も変更できます。（サンプルスクリプト参照）

・rviz 上で変更できない項目は、この plugin でも変更できません。

・余分な空白はチェックしていません。詰めて下さい。

・文字列の最後には「, (カンマ)」を入れてください。
　無くても動くものもありますが、たとえば最後の文字列を空白にする場合は、末尾が ,, とカンマを２個続けます。

・厳密なデータチェックはしてないので、挙動を見ながらお使いください。
　（変なデータが適応されると、rviz が落ちます）
 
```

<br>
<br>

```bash
$ //RobotModel の表示を消す
$ rostopic pub -1 /rviz_itemmod std_msgs/String "data: 'RobotModel,Visual Enabled,false'" 
$ 
$ //RobotModel の表示を消したのを戻す
$ rostopic pub -1 /rviz_itemmod std_msgs/String "data: 'RobotModel,Visual Enabled,true'" 
$ 
$ //Grid を消す
$ rostopic pub -1 /rviz_itemmod std_msgs/String "data: 'Grid,false'" 
$ 
```

<br>
<br>

## Sample script - サンプルスクリプト

また、Python (rospy) から Topic を送るサンプルスクリプトも置いておきます。

（ src/testStringPub.py ）


<br>
<br>

## Liscense - ライセンス

MIT Liscense

<br>
<br>

## Thanks !!!

●オリジナル Rviz Plugin をつくってみる 2. ROS1で .ui ファイルを使ってオリジナルパネルをつくる ( [by RyodoTanaka](https://twitter.com/RyodoTanaka) )

https://twitter.com/RyodoTanaka

https://qiita.com/RyodoTanaka/items/4924af4f7b1e91f3a5b9

<br>
<br>

●ROS講座74 twistを送るrviz panel pluginを作る ( [by project_srs](https://qiita.com/srs) )

https://qiita.com/srs/items/da3b65ca365644783068

●ROS講座118 overlayで表示するのrviz display plugindを作る

https://qiita.com/srs/items/343f859d7b741ccd5711
