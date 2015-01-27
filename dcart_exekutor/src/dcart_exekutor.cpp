#include <dcart_exekutor/dcart_exekutor.h>

namespace exekutor
{

DcartExekutor::DcartExekutor(std::string robot_name, std::string action_name):
		ActionExekutor(robot_name, action_name, false)
{
	command_pub_ = nh_.advertise <std_msgs::String> ("dcart/command", 1);
	status_sub_ = nh_.subscribe("dcart/status", 5, &DcartExekutor::statusCallback, this);
}

void DcartExekutor::statusCallback(const std_msgs::String::ConstPtr& status_message)
{
	status_ = status_message;
}

DcartExekutor::~DcartExekutor()
{
	command_pub_.shutdown();
}

void DcartExekutor::actionThread()
{
	ROS_INFO("DcartExekutor has started for action %s.", action_name_.c_str());
	std::string data = std::string(getParamTuple().data);

	for(int i = 0; i<data.size(); i++)
		data[i] = tolower(data[i]);

	if(action_name_ == "bin")
		binAction(data);
	else if(action_name_ == "startgui")
		startguiAction(data);
	else if(action_name_ == "dock")
		dockAction(data);
	else if(action_name_ == "moveto")
		movetoAction(data);

}

void DcartExekutor::dockAction(const std::string& dock_parameters)
{
	std_msgs::String _message;
	_message.data = dock_parameters;
	command_pub_.publish(_message);

	waitForCompletion(action_name_ + " " + dock_parameters);
}

void DcartExekutor::movetoAction(const std::string& moveto_parameters)
{
	std_msgs::String _message;
	_message.data = "moveto " + moveto_parameters;
	command_pub_.publish(_message);

	// The status string looks like "moveto STATUS".
	waitForCompletion(action_name_);
}

void DcartExekutor::startguiAction(const std::string& startgui_parameters)
{
	std_msgs::String _message;
	if(startgui_parameters.compare("walksupport") == 0)
		_message.data = "walk support";
	else if(startgui_parameters.compare("takegoods") == 0)
		_message.data = "take goods";
	command_pub_.publish(_message);

	// The status string looks like "walk support STATUS" or "take goods STATUS".
	waitForCompletion(_message.data);
}

void DcartExekutor::binAction(const std::string& bin_parameters)
{
	std_msgs::String _message;
	_message.data = "bin " + bin_parameters;
	command_pub_.publish(_message);

	// The status looks like "bin open STATUS".
	waitForCompletion(_message.data);
}

void DcartExekutor::waitForCompletion(const std::string& status_prefix)
{
	StateValue actionStatus = RUNNING;
	status_.reset();
	while(true)
	{
		ros::spinOnce();
		if(!status_)
			continue;
		else
		{
			size_t statusPosition = status_->data.find(status_prefix + " ") + std::string(status_prefix + " ").size();
			std::string extractedStatus = status_->data.substr(statusPosition);

			if(extractedStatus.compare("completed") == 0)
			{
				actionStatus = COMPLETED;
				ROS_INFO("The action completed successfully.");
				break;
			}
			else if(extractedStatus.compare("running") == 0)
			{
				continue;
			}
			else if(extractedStatus.compare("failed") == 0)
			{
				actionStatus = FAILED;
				ROS_INFO("The action failed. Contact RoboTech! :P.");
				break;
			}
		}
	}

	setState(actionStatus);


}

}
