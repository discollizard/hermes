#include "webfunctions.h"

int open_socket_or_die(){

	int sockfd;

	if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0){
		perror("Failed to create socket");
		exit(EXIT_FAILURE);
	}

	return sockfd;
}

void set_sock_opts_or_die(int socket_file_descriptor){

	int reuse_address_and_port = 1;

	if(setsockopt(socket_file_descriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &reuse_address_and_port, sizeof(reuse_address_and_port)) < 0){
		perror("Failed to set socket options");
		close(socket_file_descriptor);
		exit(EXIT_FAILURE);
	}
}

void bind_socket_or_die(int socket_file_descriptor, struct sockaddr_in* sock_struct){

	printf("%p", sock_struct);
	if(bind(socket_file_descriptor, (struct sockaddr*)sock_struct, sizeof(*sock_struct)) < 0){
		perror("Failed to bind socket");	
		close(socket_file_descriptor);
		exit(EXIT_FAILURE);
	}

}
