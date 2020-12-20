#include <mqueue.h>
#include <iostream>
#include <unistd.h>
#include <unistd.h>

#define QUEUE_NAME "/sp-example-client"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

// g++ mqueue_server.cpp -lrt -o server

int
main(int argc, char **argv)
{
	// queue descriptors
	mqd_t qd_client;

	std::cout << "server started!\n\n";

	struct mq_attr attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MESSAGES;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;

	char msg_buffer[MSG_BUFFER_SIZE];

	if((qd_client = mq_open(QUEUE_NAME, O_WRONLY)) == 1)
	{
		perror("Server: Not able to open client queue");
		exit(-1);
	}

	std::cout << "message: ";
	for (std::string line; std::getline(std::cin, line);)
	{
		if(mq_send(qd_client, line.c_str(), line.size() + 1, 0) == -1)
		{
			perror("Server: Not able to send message to client");
			continue;
		}

		std::cout << "message: ";
	}

	return 0;
}