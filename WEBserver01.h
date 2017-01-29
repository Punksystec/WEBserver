//BEGIN_INCLUDE
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
//END_INCLUDE

//BEGIN_CONFIG
//#define CONFIG_HTTP_PORT 15000
#define CONFIG_HTTP_PORT 80
//END_CONFIG

//BEGIN_DEFINES
// TEST_ERROR_* to 1 for checking error conditions are ok 
// but program will not run. SET TO 0  FOR NORMAL RUNNING
#define TEST_ERROR_1 0
#define TEST_ERROR_2 0

// TEST_NORMA_* to 1 for test normal running. (0 normal value)
#define TEST_NORMAL_1 0

// Wrapper definitions
#define VERBOSE printf
#define ERROR 	printf
#define EXIT_1	server_status=FLAG_ERROR;printf("EXIT_1\n");exit(1)
#define EXIT_2	server_status=FLAG_ERROR;printf("EXIT_2\n");exit(1)

// Flags for server_status (may be equal to FLAG_RUN to stand up)
#define FLAG_STOP 	0
#define FLAG_RUN	 1
#define FLAG_ERROR	2

// Messages for the user
#define MSG_PRG_START		"WEBserver v0.1. Started\nHTTP for x86-64 systems.\n"
#define MSG_SOCKET_CREATED	"Socket created.\n" 
#define MSG_SOCKET_CLOSED	"Socket closed.\n"
#define MSG_PRG_END		"Webserver END!\n"
#define MSG_BINDING_SOCKET	"Binding socket...\n"
#define MSG_CLIENT_CONNECTED	"The client is connected...\n"

// Error messages
#define ERR_LISTENING		"Error listening.\n"
#define ERR_SERVER_REFUSE	"Server refuse connections.\n"
#define ERR_REQUEST		"REQUEST ERROR 404\n"
//END_DEFINES
