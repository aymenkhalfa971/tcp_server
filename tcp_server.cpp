#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <stdint.h>
#include <chrono>
#include <thread>
#include <functional>
int 	gclientSocket; 
int glistening;
uint8_t sendBuffer[100];
uint16_t timer = 0;
uint8_t startMain = 0;
int timeoutFlag = 0;
int startCounter = 0;
typedef enum {
INIT,
RECEIVE,
CLOSE

}tcpState;
tcpState state = INIT;
//int main();
void timer_start(std::function<void(void)> func, unsigned int interval)
{
  std::thread([func, interval]()
  {
    while (true)
    {
      auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
      func();
      std::this_thread::sleep_until(x);
    }
  }).detach();
}
uint16_t returnnn = 0;
void sendData()
{
if(startCounter == 1)
{
timer++;
}
else
{
timer = 0;
}
// timer++;
 if(timer >= 50)
 {
	 timer = 0;
	timeoutFlag = 1;
	 printf("timer Triggered\n");
// startMain = 0;
// timer = 0;
// main();
//	goto CLOSE;
//	state : INIT;
 }
}
using namespace std;
int main()
{

timer_start(sendData, 1000);
#if 0
    // Create a socket
   printf("main Starting : \n");
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }
int reuse = 1;
    if (setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
        printf("setsockopt(SO_REUSEADDR) failed\n");
 
    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(3389);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
    bind(listening, (sockaddr*)&hint, sizeof(hint));
 	
    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);
 
    // Wait for a connection
    
    
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket =  close(clientSocket);
	clientSocket    = accept(listening, (sockaddr*)&client, &clientSize);
 	gclientSocket = clientSocket;
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
 
    // Close listening socket
    close(listening);
 
    // While loop: accept and echo message back to client
    uint8_t buf[4096];
    uint8_t buffer[100];
    uint32_t counter = 0;
    uint32_t ret = 0;
    uint8_t dataReceived = 0;
    while (true)
    {
        memset(buf, 0, 4096);
 	memset(buffer, 0, 100);
        // Wait for client to send data
	 
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        timer = 0;
	if (bytesReceived == -1)
        {
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }
 
        if (bytesReceived == 0)
	{
            cout << "Client disconnected " << endl;
            break;
        }
        else
	{
       // cout << string(buf, 0, bytesReceived) << endl;
 	for(int i = 0;i<bytesReceived;i++)
	{
		printf("%02X",buf[i]);
	}

	printf("\n\n\n\n\n");
	if((buf[0] == 0x00)&& (buf[1] == 0x0F))
	{
	buffer[0] = 0x01;
        // Echo message back to client
	printf("Data no sent to Tracker: %02X\n",buffer[0]);
        send(clientSocket, buffer,1, 0);
	}
	else
	{
	buffer[0] = 0x00;	
	buffer[1] = 0x00;  
	buffer[2] = 0x00;  
	buffer[3] = buf[9];
	sendBuffer[0] = 0x00;
	sendBuffer[1] = 0x00;
	sendBuffer[2] = 0x00;
	sendBuffer[3] = buf[9];
       // memset(buf, 0, sizeof(buf)); 	
  	counter++;      
       	ret = send(clientSocket, buffer,4, 0);
	startMain = 1;
	if(ret == 4)
	{
	printf("Data no %d  sent to Tracker: %02X\n",counter, buffer[3]);
	}
	else if (ret == -1)
	{
	printf("data was not sent successfully\n");
	}
	else
	{
	printf("unknown error: %d\n",ret);
	}
	timer_start(sendData, 1000);
	}
	}
    }
 
    // Close the socket
    close(clientSocket);
#endif
    while(true)
    {
    switch(state){
	case INIT:
		
		{	
			startCounter = 0;
    // Create a socket
   printf("main Starting : \n");
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    glistening = listening;
    if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }
int reuse = 1;
    if (setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
        printf("setsockopt(SO_REUSEADDR) failed\n");
struct timeval tv;

tv.tv_sec = 30;  /* 30 Secs Timeout */

if(setsockopt(listening, SOL_SOCKET, SO_RCVTIMEO,(const char*)&tv,sizeof(struct timeval))<0)
       printf("socketopt SO_RCVTIMEO failed \n");	
    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(3389);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
    bind(listening, (sockaddr*)&hint, sizeof(hint));
 	
    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);
 
    // Wait for a connection
    
    
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket =  close(clientSocket);
	clientSocket    = accept(listening, (sockaddr*)&client, &clientSize);
 	gclientSocket = clientSocket;
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
 
    // Close listening socket
    close(listening);
    state = RECEIVE;
    }
	break;
	case RECEIVE:
	{	
    uint8_t buf[4096];
    uint8_t buffer[100];
    uint32_t counter = 0;
    uint32_t ret = 0;
    uint8_t dataReceived = 0;

        memset(buf, 0, 4096);
 	memset(buffer, 0, 100);
        // Wait for client to send data
	int bytesReceived = -1;
	do{	 
         bytesReceived = recv(gclientSocket, buf, 4096, MSG_DONTWAIT);
	 if(timeoutFlag == 1)
	 {
		// timeoutFlag = 0;
		// printf("entered timeout condition\n");
		//state = CLOSE;
		bytesReceived = 1;
		break;
	 }
	}while(bytesReceived == -1);
	if(timeoutFlag == 1)
	{
	
		 timeoutFlag = 0;
		 printf("entered timeout condition\n");
		state = CLOSE;
		break;
	}
       // timer = 0;
#if 0
	if (bytesReceived == -1)
        {
            cerr << "Error in recv(). Quitting" << endl;
            state = CLOSE;
	    break;
        }
#endif
	
        if (bytesReceived == 0)
	{
            cout << "Client disconnected " << endl;
	    state = CLOSE;
            break;
        }
        else
	{
       // cout << string(buf, 0, bytesReceived) << endl;
 	for(int i = 0;i<bytesReceived;i++)
	{
		printf("%02X",buf[i]);
	}

	printf("\n\n\n\n\n");
	if((buf[0] == 0x00)&& (buf[1] == 0x0F))
	{
	buffer[0] = 0x01;
        // Echo message back to client
	printf("Data no sent to Tracker: %02X\n",buffer[0]);
        send(gclientSocket, buffer,1, 0);
	}
	else
	{
	buffer[0] = 0x00;	
	buffer[1] = 0x00;  
	buffer[2] = 0x00;  
	buffer[3] = buf[9];
	sendBuffer[0] = 0x00;
	sendBuffer[1] = 0x00;
	sendBuffer[2] = 0x00;
	sendBuffer[3] = buf[9];
       // memset(buf, 0, sizeof(buf)); 	
  	counter++;      
       	ret = send(gclientSocket, buffer,4, 0);
//	startCounter = 1;
//	startMain = 1;
	if(ret == 4)
	{
	printf("Data no %d  sent to Tracker: %02X\n",counter, buffer[3]);
	startCounter = 1;
	}
	else if (ret == -1)
	{
	printf("data was not sent successfully\n");
	
	}
	else
	{
	printf("unknown error: %d\n",ret);
	}
	}
	}
    	state = RECEIVE;
    }
        break;
	case CLOSE:
	{
	printf("entered close \n");
    	close(glistening);
	state = INIT;
	}
	break;	
    }   
    }
    return 0;
}
