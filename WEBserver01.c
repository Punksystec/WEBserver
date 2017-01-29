
/*
 * WEBserver.c v01
 *
 * GPLv3 WEBserver for GCC Compiler and Linux x86-64 systems.
 *
 * Based on:
 *   http://blog.manula.org/2011/05/writing-simple-web-server-in-c.html
 */


#include "WEBserver01.h"

int main(){
	VERBOSE(MSG_PRG_START);

	int main_socket, new_socket;
	socklen_t addrlen;
	int bufsize = 1024;
	int bufread = 1024;
	char* buffer = malloc(bufsize); //TODO check
	char* buffer_read = malloc(bufread);
	char* http_get = malloc(bufsize);
	struct sockaddr_in address;

	if ((main_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0){
		VERBOSE(MSG_SOCKET_CREATED);
	}//TODO check

	address.sin_family = 		AF_INET;
	address.sin_addr.s_addr = 	INADDR_ANY;
	address.sin_port = 		htons(CONFIG_HTTP_PORT
);

	int server_status = FLAG_STOP;

	if (bind(main_socket, (struct sockaddr *) &address, sizeof(address)) ==0) {
		VERBOSE(MSG_BINDING_SOCKET);
		server_status = FLAG_RUN;
	}//TODO check

	int home_size=4;
	memcpy(http_get,"home",home_size);
	char* home_name="/home.html";
	int shome_name=strlen(home_name);

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

		if (strncmp(buffer,"GET ",4)==0){ //HTTP GET
		
			printf("\nGET request.\n");
			char* pos1=strchr(buffer,' ')+1;
			char* pos2=strchr(pos1,' ');
			int size_request= pos2-pos1;
			
			if (size_request==1){//Root request
				memcpy(http_get+home_size, home_name, shome_name);
				http_get[home_size+shome_name] = '\0';
				
			}else{
				printf("SIZE %d\n",size_request);
				memcpy(http_get+home_size,pos1, size_request);
				http_get[home_size+size_request] = '\0';
			}
			printf("REQUEST [%s]\n",http_get);

			FILE* file=NULL;
			file=fopen(http_get,"r");

			if (file!=NULL){
				printf("Sending %s...\n",http_get);
				int eof=0;
				while (!eof){
					int readed=fread(buffer_read, 1, bufsize, file);
					if (readed>0){
						write(new_socket,buffer_read,readed);
					}
					if (readed<bufsize){
						eof=1;
					}
				}
				fclose(file);
					
			}else{
				printf(ERR_REQUEST);
			}

		}else{
			printf("\nRequest not processed.\n");
		}

		//write(new_socket, "hello world\n", 12);
		//TODO check

		close(new_socket);//TODO check
	}

	close(main_socket);
	VERBOSE(MSG_SOCKET_CLOSED);

	VERBOSE(MSG_PRG_END);
	return 0;
}
