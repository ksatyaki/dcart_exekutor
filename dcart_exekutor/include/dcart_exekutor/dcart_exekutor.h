/**
 * THE DCART EXEKUTOR PACKAGE.
 * THIS PACKAGE PROVIDES THE INTERFACE BETWEEN PEIS
 * AND ROS FOR PERFORMING TASKS ON THE DUST CART.
 * 
 * AUTHOR: Chittaranjan S Srinivas
 * 
 */

#ifndef DCART_EXEKUTOR_H
#define DCART_EXEKUTOR_H
 
#include <exekutor/action_exekutor.h>
#include <std_msgs/String.h>

namespace exekutor
{

class DcartExekutor: public ActionExekutor
{
protected:

	/**
	 * The publisher to the topic dacrt/command.
	 */
	ros::Publisher command_pub_;

	/**
	 * This function publishes to the dcart/command topic.
	 *
	 * The implementation of actionThread() function.
	 * This is called from ActionExekutor's startActionThread().
	 */
	virtual void actionThread();

	/**
	 * For convenience we split our tasks.
	 * For Bin actions.
	 */
	void binAction(const std::string& bin_parameters);

	/**
	 * For moveto.
	 */
	void movetoAction(const std::string& moveto_parameters);

	/**
	 * For startgui.
	 */
	void startguiAction (const std::string& startgui_parameters);

	/**
	 * For dock.
	 */
	void dockAction (const std::string& dock_parameters);


	/**
	 * A Subscriber to the status message.
	 */
	ros::Subscriber status_sub_;

	/**
	 * A Callback for the status.
	 */
	void statusCallback(const std_msgs::String::ConstPtr& status_message);

	/**
	 * A Status message.
	 */
	std_msgs::StringConstPtr status_;

	/**
	 * This functions listens on the status topic with the given prefix.
	 */
	void waitForCompletion(const std::string& status_prefix);

public:
	/**
	 * Constructor.
	 */
	DcartExekutor(std::string robot_name, std::string action_name);

	/**
	 * Destructor.
	 */
	virtual ~DcartExekutor();
};

}

#endif /* DCART_EXEKUTOR_H */

