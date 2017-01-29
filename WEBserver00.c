
/*
 * WEBserver.c
 *
 * GPLv3 WEBserver for GCC Compiler and Linux x86-64 systems.
 *
 * Based on:
 *   http://blog.manula.org/2011/05/writing-simple-web-server-in-c.html
 */


#include "WEBserver00.h"

int main(){
	VERBOSE(MSG_PRG_START);

	int main_socket, new_socket;
	socklen_t addrlen;
	int bufsize = 1024;
	char* buffer = malloc(bufsize); //TODO check
	struct sockaddr_in address;

	if ((main_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0){
		VERBOSE(MSG_SOCKET_CREATED);
	}//TODO check

	address.sin_family = 		AF_INET;
	address.sin_addr.s_addr = 	INADDR_ANY;
	address.sin_port = 		htons(CONFIG_HTTP_PORT);

	int server_status = FLAG_STOP;

	if (bind(main_socket, (struct sockaddr *) &address, sizeof(address)) ==0) {
		VERBOSE(MSG_BINDING_SOCKET);
		server_status = FLAG_RUN;
	}//TODO check

	while (server_status == FLAG_RUN){
		if ((listen(main_socket, 10) < 0) || TEST_ERROR_1){
			ERROR(ERR_LISTENING);
			EXIT_1;
		}

		new_socket=0;
		//DEBUG IF COMMENTED:
		new_socket = accept(main_socket,
			(struct sockaddr*) &address, &addrlen);

		if ((new_socket < 0) || TEST_ERROR_2) {
			ERROR(ERR_SERVER_REFUSE);
			EXIT_2;
		}

		if ((new_socket>0) || TEST_NORMAL_1){
			VERBOSE(MSG_CLIENT_CONNECTED);
		}
		recv(new_socket,  buffer, bufsize, 0);
		//TODO check

		printf("%s\n", buffer);

		write(new_socket, "hello world\n", 12);
		//TODO check

		close(new_socket);//TODO check
	}

	close(main_socket);
	VERBOSE(MSG_SOCKET_CLOSED);

	VERBOSE(MSG_PRG_END);
	return 0;
}
