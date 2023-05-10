#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "params.h"
#include "webfunctions.c"

int main(int argc, char** argv){

	int server_fd, client_fd, line;
	struct sockaddr_in address;
	char line_buffer[LINE_BUFFER_SIZE];
	char return_buffer[LINE_BUFFER_SIZE];

	server_fd = open_socket_or_die();

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);

	//ok, if this function fails, should the program just die?
	//it's not like it won't work, it just wont reuse addresses nor ports
	//
	//maybe log the occurence and move on? idk, TODO
	//

	set_sock_opts_or_die(server_fd);

	bind_socket_or_die(server_fd, &address);

	if (listen(server_fd, 1024) < 0) {
		perror("Error while listening to incoming connections");
		exit(EXIT_FAILURE);
	}

	printf("Listening on port %d...", PORT);

	for(;;){

		struct sockaddr_in client_addr;
		socklen_t client_address_len;

		client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_address_len);

		if (client_fd < 0){
			perror("Error while accepting incoming connection");
			close(server_fd);
			exit(EXIT_FAILURE);
		}

		memset(line_buffer, 0, LINE_BUFFER_SIZE - 1);

		printf("Connection accepted: %d", server_fd);

		while((line = read(client_fd, line_buffer, LINE_BUFFER_SIZE - 1)) > 0){
			//could log this in a file later
			fprintf(stdout, "\n%s\n", line_buffer);
			fflush(stdout);

			if (line_buffer[line-1] == '\n'){
				break;
			}

			memset(line_buffer, 0, LINE_BUFFER_SIZE - 1);
		}
		if(line < 0){
			perror("Error while reading from socket");
			close(server_fd);
			exit(EXIT_FAILURE);
		}

		snprintf((char*)return_buffer, sizeof(return_buffer), "HTTP/1.0 200 OK \r\n\r\nAmo mickelly");

		if((write(client_fd, (char*)return_buffer, strlen((char*)return_buffer))) < 0){
			perror("Error while writing to socket");
			close(server_fd);
			exit(EXIT_FAILURE);
		}

		close(server_fd);
	}


	return 0;

	//wait for socket connection 
	//when socket connects, return the page content
	//when interrupted, exit gracefully
	//
	//
	
	
	return 0;
}
