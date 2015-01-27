#include <dcart_exekutor/dcart_exekutor.h>

namespace exekutor
{

DcartExekutor::DcartExekutor(std::string robot_name, std::string action_name):
		ActionExekutor(robot_name, action_name)
{
	command_pub_ = nh_.advertise <std_msgs::String> ("dcart/command", 1);
}

DcartExekutor::~DcartExekutor()
{
	command_pub_.shutdown();
}

void DcartExekutor::actionThread()
{
	ROS_INFO("DcartExekutor has started.");
	std_msgs::String _message; 
	std::string data = std::string(getParamTuple().data);
	_message.data = data;
	command_pub_.publish(_message);

	ROS_INFO("Successfully executed the action on the robot.");
	setState(COMPLETED);
	sleep(1);

}

}
