#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {

    pub_ = n_.advertise<geometry_msgs::PoseWithCovarianceStamped>("/orb_slam2_mono/pose_cov", 2);


    sub_ = n_.subscribe("/orb_slam2_mono/pose", 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const geometry_msgs::PoseStamped& pose_msg)
  {
    geometry_msgs::PoseWithCovarianceStamped pwc;
    pwc.pose.pose = pose_msg.pose;
    pwc.header = pose_msg.header;
    //pwc.pose = pose_msg;
    pub_.publish(pwc);
  }

private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;

};//End of class

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "stamp_and_covariance");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}