#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include "aria.h"

#pragma comment(lib,"ws2_32.lib")

void swcmd(char * c,ArRobot* robot);
int reccmd(ArRobot* robot);
void up(ArRobot* robot);
void down(ArRobot* robot);
void right(ArRobot* robot);
void left(ArRobot* robot);

int main(int argc, char* argv[])
{
	//robot的初始操作
	Aria::init();
	ArRobot robot;
	ArArgumentParser parser(&argc,argv);
	ArSimpleConnector connector(&parser);
	parser.loadDefaultArguments();
	if(!connector.parseArgs())//解析连接器参数
	{

		printf("未知设置\n");

		Aria::exit(0);

		exit(1);

	}

	if(!connector.connectRobot(&robot))
	{
		printf("连接失败\n");

		Aria::exit(0);

		exit(1);

	}

	robot.runAsync(true);//以异步模式运行

	//robot.lock();
	robot.enableMotors();//启动发动机
	
	reccmd(&robot);//接受命令
    
	robot.disableMotors();
	Aria::exit(0);

    return 0;
}


void up(ArRobot* robot)
{
	//printf("UP\n");
	robot->move(150);
}

void down(ArRobot* robot)
{
	//printf("DOWN\n");
	robot->move(-100);
}

void left(ArRobot* robot)
{
	//printf("LEFT\n");
	robot->setDeltaHeading(10);
}

void right(ArRobot* robot)
{
	//printf("RIGHT\n");
	robot->setDeltaHeading(-10);
}

//对接收命令的识别
void swcmd(char * c,ArRobot* robot)
{
	char cmd=c[0];
	switch(cmd)
	{
		case 'U':	up(robot);break;
		case 'D':	down(robot); break;
		case 'L':	left(robot); break;
		case 'R':	right(robot);break;
		default:
			printf("%s命令无效!\n",c);
			break;
	}
}

int reccmd(ArRobot* robot)
{
	//初始化WSA
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(sockVersion, &wsaData)!=0)
    {
        return 0;
    }

    //创建套接字
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(slisten == INVALID_SOCKET)
    {
        printf("socket error !");
		getchar();
        return 0;
    }

    //绑定IP和端口
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);
    sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY); 
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        printf("bind error !\n");
    }

    //开始监听
    if(listen(slisten, 5) == SOCKET_ERROR)
    {
        printf("listen error !");
		getchar();
        return 0;
    }

    //循环接收数据
    SOCKET sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[255]; 
    while (true)
    {
        printf("等待接收命令!\n");
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
        if(sClient == INVALID_SOCKET)
        {
            printf("accept error !");
            continue;
        }
        printf("接受到一个连接：%s", inet_ntoa(remoteAddr.sin_addr));
        

        //接收数据
        int ret = recv(sClient, revData, 255, 0);        
        if(ret > 0)
        {
            revData[ret] = 0x00;
			printf("的%s命令！\n",revData);
			swcmd(revData,robot);
        }
		else
		{
			printf("\n");
		}

        //发送数据
        char * sendData = strcat(revData,"命令发送成功！\n");
        send(sClient, sendData, strlen(sendData), 0);
		if (revData[0]=='E')
				break;
        closesocket(sClient);
    }
    WSACleanup();
	return 1;
}