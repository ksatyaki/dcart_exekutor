#include "dcart_exekutor/dcart_exekutor.h"
#include <signal.h>

using exekutor::DcartExekutor;

void handler(int signal_number)
{
	if(signal_number == SIGINT)
		printf("Ctrl-C caught...\n");
	else
		printf("Ctrl-Z caught...\n");
	ros::shutdown();

	abort();
}


int main(int argn, char *args[])
{
	peiskmt_initialize(&argn, args);

	ros::init(argn, args, "exekutor");

	DcartExekutor DcartCommand("Dcart", "Functions");

	peiskmt_setStringTuple("dcart.functions.23.command", "OFF");
	peiskmt_setStringTuple("dcart.functions.23.parameters", "-");
	peiskmt_setStringTuple("dcart.functions.23.state", "IDLE");

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);

	exekutor::ActionExekutor::waitForLink();
	return 0;
}
