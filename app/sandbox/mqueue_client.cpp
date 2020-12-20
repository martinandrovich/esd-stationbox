#include <mqueue.h>
#include <iostream>

#define QUEUE_NAME "/sp-example-client"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

// g++ mqueue_client.cpp -lrt -o client

int
main(int argc, char **argv)
{
	// queue descriptor
	mqd_t qd_client;

	std::cout << "client started!\n\n";

	struct mq_attr attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MESSAGES;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;

	if ((qd_client = mq_open (QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
	{
		perror ("Client: mq_open (client)");
		exit (1);
	}

	char msg_buffer[MSG_BUFFER_SIZE];

	while (true)
	{
		if (mq_receive(qd_client, msg_buffer, MSG_BUFFER_SIZE, NULL) == -1)
		{
			perror ("Client: mq_receive");
			exit(1);
		}

		std::cout << "server says: " << msg_buffer << std::endl;
	}
	
	return 0;
}
