#include "ros/ros.h"
#include "eval_funcs/objective.h"

bool objective(eval_funcs::objective::Request  &req,
          eval_funcs::objective::Response &res)
{
    res.eval = 0;
    for(int i=0; i<req.chrom.size(); i++)
        res.eval += req.chrom[i];
    ROS_INFO("sending back response: [%f]", (double)res.eval);
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "one_max_node");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("objective", objective);
    ROS_INFO("Ready to add two ints.");
    ros::spin();

    return 0;
}