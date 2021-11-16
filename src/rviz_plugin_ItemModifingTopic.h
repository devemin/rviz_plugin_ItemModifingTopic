#ifndef OPE_RELAY_H
#define OPE_RELAY_H

#ifndef Q_MOC_RUN
#include <std_msgs/String.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <rviz/display.h>
#include <rviz/display_group.h>
#include <rviz/properties/string_property.h>
using namespace std;



#endif

namespace rviz
{

}  // namespace rviz

namespace rviz_plugin_ItemModifingTopic
{
    class ItemModifingTopic : public rviz::Display
    {
      Q_OBJECT
    public:
      ItemModifingTopic();
      virtual ~ItemModifingTopic();
    
      virtual void onInitialize();
      virtual void reset();
    
    private Q_SLOTS:
      void updateThisTopicName();
    
    private:
      void processMessage(const std_msgs::String& msg);
    
      string defaultTopicName =  "/rviz_itemmod";
      const string defaultTopicNameTitle =  "Topic";
      rviz::StringProperty *str_property_;
      ros::NodeHandle nh_;
      ros::Subscriber sub_;
    };

}  // namespace rviz_plugin_ItemModifingTopic

#endif  // OPE_RELAY_H
