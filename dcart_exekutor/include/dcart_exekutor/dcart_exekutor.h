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

