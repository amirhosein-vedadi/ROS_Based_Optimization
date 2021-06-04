#include "ros/ros.h"
#include "eval_funcs/objective.h"

bool objective(eval_funcs::objective::Request  &req,
          eval_funcs::objective::Response &res)
{
    res.eval = 0;
    for(int i=0; i<req.chrom.size(); i++)
        res.eval -= req.chrom[i];
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "one_max_node");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("objective", objective);
    ROS_INFO("Ready to evaluate optimization cost.");
    ros::spin();

    return 0;
}