#include "rviz_plugin_ItemModifingTopic.h"
#include <pluginlib/class_list_macros.h>
#include <std_msgs/String.h>



namespace rviz_plugin_ItemModifingTopic
{
    ItemModifingTopic::ItemModifingTopic()
    {
    }

    void ItemModifingTopic::onInitialize()
    {
        str_property_ = new rviz::StringProperty(defaultTopicNameTitle.c_str(), defaultTopicName.c_str(), "Topic name for sub.", this, SLOT(updateThisTopicName()));
        sub_ = nh_.subscribe(defaultTopicName, 10, &ItemModifingTopic::processMessage, this);

        this->expand();
    }

    ItemModifingTopic::~ItemModifingTopic()
    {
    }


    void ItemModifingTopic::reset()
    {
    }

    void ItemModifingTopic::updateThisTopicName()
    {
        string changename = str_property_->getString().toStdString() ;
        if (changename == "") {
            changename = defaultTopicName.c_str();
        }
        if (changename[0] != '/') {
            changename = "/" + changename;
        }

        //https://makemove.hatenablog.com/entry/2016/09/04/193533
        //Thanks!
        ros::master::V_TopicInfo master_topics;
        ros::master::getTopics(master_topics);
        for (ros::master::V_TopicInfo::iterator it = master_topics.begin() ; it != master_topics.end(); it++) {
          const ros::master::TopicInfo& info = *it;
          //std::cout << "topic_" << it - master_topics.begin() << ": " << info.name << std::endl;
          //ROS_WARN("%s", info.name.c_str());
          if (info.name == changename) {
            changename = defaultTopicName.c_str();
            break;
          }
        }


        //ROS_WARN("%s", changename.c_str());
        sub_.shutdown();        
        sub_ = nh_.subscribe(changename, 10, &ItemModifingTopic::processMessage, this);


        rviz::Display * rviz_di = (rviz::Display *)this;
        rviz::Property * rviz_dp = (rviz::Property *) rviz_di->subProp(defaultTopicNameTitle.c_str());
        rviz_dp->setValue(changename.c_str());


    }

    void ItemModifingTopic::processMessage(const std_msgs::String& msg)
    {
        rviz::DisplayGroup *rviz_dg = (rviz::DisplayGroup *)this->getParent();  //本プラグインの親がroot のはず
        rviz::Display * rviz_di;         //temporary Display item
        rviz::Property * rviz_dp;        //temporary Property item

        vector<string> v;
        string s = msg.data.c_str();
        stringstream ss{s};

        const char* pluginname = "ItemModifingTopic Plugin";
        int itemflag_from = 0;
        int itemflag_to = 0;
        bool itemboolvalue_from = false;
        bool itemboolvalue_to = false;
        string itemstringvalue_from = "";

        ////////////////////////////////////////////////////////////////////////////
        //sub 文字列をカンマで分け、 vector<string> へ入れる
        while ( getline(ss, s, ',') ){
            v.push_back(s);
        }


        ////////////////////////////////////////////////////////////////////////////
        //sub データ全項目チェック

        if ( (v.size() < 2) || (v.size() >= 100) ) {
            ROS_WARN("[%s]: %s, Topic string number ERROR. [change string num]", pluginname, msg.data.c_str());
            return;
        }

        /*
        //for debug
        for (int i=0; i<v.size();i++){
            ROS_WARN("%s", v.at(i).c_str());
        }
        */


        ////////////////////////////////////////////////////////////////////////////
        //sub データ末尾の項目 type チェック
        if ( (v.at(v.size()-1)  == "true") || (v.at(v.size()-1)  == "True") ) {
            itemflag_from = Qt::ItemIsUserCheckable;
            itemboolvalue_from = true;
            //ROS_WARN("data check [true] OK");
        }
        else if ( (v.at(v.size()-1)  == "false") || (v.at(v.size()-1)  == "False") ) {
            itemflag_from = Qt::ItemIsUserCheckable;
            itemboolvalue_from = false;
            //ROS_WARN("data check [false] OK");
        }
        else {
            itemflag_from = Qt::ItemIsEditable;
            itemstringvalue_from = v.at(v.size()-1);
            //ROS_WARN("data check [string] OK");
        }



        ////////////////////////////////////////////////////////////////////////////
        //適応先のアイテム tree 構造チェック、実行

        //アイテム数の分、処理
        for (int a=0; a<rviz_dg->numDisplays(); a++) {
            //ROS_WARN("displays, %d, ", a);
            rviz_di = (rviz::Display *) rviz_dg->getDisplayAt(a);

            //アイテム名が一致した場合の処理
            if (rviz_di->getNameStd() == v.at(0) ) {
                //ROS_WARN("displays found!, %s, ", v.at(0).c_str());

                if (v.size() == 2) {
                    //root にあるDisplayアイテムを処理したいので、その Display を Property をキャストすることｄ
                    //あとで階層が2以上の深さにある Property を処理する部分で同等に扱える
                    rviz_dp = (rviz::Property *) rviz_di;
                }
                else {
                    rviz_dp = (rviz::Property *) rviz_di->subProp(v.at(1).c_str());
                }

                for (int b=2; b<v.size()-1; b++) {
                    rviz_dp = (rviz::Property *) rviz_dp->subProp(v.at(b).c_str());
                    //ROS_WARN("property, %s, ", v.at(b).c_str() );
                }
    
                if (rviz_dp ) {
                    if (itemflag_from == Qt::ItemIsUserCheckable) {
                        if (rviz_dp->getViewFlags(1) & Qt::ItemIsUserCheckable) {
                            rviz_dp->setValue(itemboolvalue_from);
                            //ROS_WARN("ItemIsUserCheckable OK");
                            //return ;
                        }
                        else {
                            ROS_WARN("%s, %d, ItemIsUserCheckable is different. ERROR.", msg.data.c_str(), rviz_dp->getViewFlags(1));
                            return ;
                        }
                    }
                    else if (itemflag_from == Qt::ItemIsEditable) {
                        if ( (rviz_dp->getViewFlags(1) & Qt::ItemIsEditable) || (rviz_dp->getViewFlags(1) & Qt::ItemIsSelectable) ) {
                            rviz_dp->setValue(v.at(v.size()-1).c_str());
                            //ROS_WARN("ItemIsEditable OK");
                            //return ;
                        }
                        else {
                            ROS_WARN("%s, %d, ItemIsEditable is different. ERROR.", msg.data.c_str(), rviz_dp->getViewFlags(1));
                            return ;
                        }
                    }
                    else {
                        ROS_WARN("data change NG");
                        return ;
                    }
                }
            }
        }
    }
}  // namespace rviz_plugin_ItemModifingTopic

PLUGINLIB_EXPORT_CLASS(rviz_plugin_ItemModifingTopic::ItemModifingTopic, rviz::Display)