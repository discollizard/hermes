#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "params.h"
#include "webfunctions.c"

int main(int argc, char** argv){

	int socket_descriptor;
	int new_socket_descriptor_temp;
	struct sockaddr_in address;

	socket_descriptor = open_socket_or_die();

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	//ok, if this function fails, should the program just die?
	//it's not like it won't work, it just wont reuse addresses nor ports
	//
	//maybe log the occurence and move on? idk, TODO
	//

	set_sock_opts_or_die(socket_descriptor);

	bind_socket_or_die(socket_descriptor, &address);

	if (listen(socket_descriptor, 1024) < 0) {
		perror("Error while listening to incoming connections");
		exit(EXIT_FAILURE);
	}

	printf("Listening on port %d...", PORT);

	if ((new_socket_descriptor_temp = accept(socket_descriptor, (struct sockaddr*)&address, (socklen_t*)sizeof((struct sockaddr*)&address))) < 0){
		perror("Error while accepting incoming connection");
		exit(EXIT_FAILURE);
	}

	printf("Connection accepted: %d", new_socket_descriptor_temp);

	close(socket_descriptor);
	return 0;

	//wait for socket connection 
	//when socket connects, return the page content
	//when interrupted, exit gracefully
	//
	//
	
	
	return 0;
}
