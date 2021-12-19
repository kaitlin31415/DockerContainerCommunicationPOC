#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <cstring>

using namespace std;
int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	char *env_p1;
	if (char *env_p = std::getenv("PATH"))
		std::cout << "Your PATH is: " << env_p << '\n';

	if (env_p1 = std::getenv("HOSTNAME"))
		std::cout << "Your HOSTNAME is : "<< env_p1 << '\n';
	if (argc < 2)
	{
		cout <<"Number of arguments not correct\n";
		exit(1);
	}
	cout << argv[1] <<"\n";
	cout <<"Creating socket\n";
	struct protoent *proto;
	proto = getprotobyname("tcp");
	sockfd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	cout <<"Socket created successfully\n";
	// memset(&serv_addr, 0 , sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	// serv_addr.sin_addr.s_addr=inet_addr(env_p1);
	serv_addr.sin_addr.s_addr = inet_addr("172.19.0.2");
	// serv_addr.sin_addr.s_addr=INADDR_ANY;
	cout <<"Port No :"<< portno << "\n";
	serv_addr.sin_port = htons(portno);
	cout <<"Starting binding socket to a port\n";
	if (bind(sockfd, (struct sockaddr *)&serv_addr,
			 sizeof(serv_addr)) < 0)
	{
		cout <<"Error while binding\n";
		exit(1);
	}
	cout <<"Bind is successful\n";
	cout <<"Listening to port\n";
	int x = listen(sockfd, 5);
	if (x < 0)
	{
		cout <<"Error on listening to port 1001\n";
		cout << errno << "\n";
		cout << hstrerror(errno) << "\n";
		close(sockfd);
		exit(1);
	}
	clilen = sizeof(cli_addr);
	cout <<"Accepting connection\n";
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	if (newsockfd < 0)
	{
		cout <<"Error while accepting a new connection\n";
		close(sockfd);
		exit(1);
	}
	cout <<"Accepted the connection\n";
	while (true)
	{
		memset(&buffer, 0, sizeof(buffer));
		cout <<"Reading from socket to buffer\n";
		n = read(newsockfd, buffer, 255);
		if (n < 0)
		{
			cout <<"Erro reading from socket\n";
			close(sockfd);
			close(newsockfd);
			exit(1);
		}
		cout <<"Message received to the server :"<< buffer << "\n";
		n = write(newsockfd,"I got your message", 18);
		if (n < 0)
		{
			cout <<"Error writing into socket\n";
			close(sockfd);
			close(newsockfd);
			exit(1);
		}
	}
	close(sockfd);
	close(newsockfd);
	return 0;
}