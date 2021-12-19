#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>

using namespace std;

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	struct sockaddr_in server;
	char message[256], server_reply[2000];
	if (char *env_p = std::getenv("PATH"))
		std::cout << "Your PATH is: " << env_p << '\n';
	struct protoent *proto;
	proto = getprotobyname("tcp");
	sockfd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	cout <<"socket created\n";

	cout << argv[1] << "\n";
	cout << argv[2] << "\n";
	portno = atoi(argv[2]);
	cout << portno << "\n";
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = htons(portno);
	memset(server.sin_zero, '\0', sizeof server.sin_zero);

	cout <<"connecting to server\n";
	int x = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
	cout <<"Connect Return Code :"<< x << "\n";
	if (x < 0)
	{
		cout <<"Connect Failed\n";
		cout << errno << "\n";
		cout << hstrerror(errno) << "\n";
		exit(1);
	}
	cout <<"Connected\n";
	while (1)
	{
		cout <<"Enter Message :";
		cin >> message;

		if (send(sockfd, message, strlen(message), 0) < 0)
		{
			cout << "Send Failed\n";
			exit(1);
		}
		sleep(2);

		if (recv(sockfd, server_reply, 2000, 0) < 0)
		{
			cout << "Recv Failed\n";
			break;
		}

		cout << "Server Reply:" << server_reply << "\n";
	}
	close(sockfd);
	return 0;
}