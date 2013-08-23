/**
 ******************************************************************************
 * @file      socket.c
 * @brief     C Source file of socket.c.
 * @details   This file including all API functions's 
 *            implement of socket.c.	
 *
 * @copyright Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#ifdef __WIN32
#include <winsock.h>
#else
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include "log.h"

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
/* NONE */ 

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief      套接字初始化
 * @param[in]  *pHostName   : 主机名
 * @param[in]  port         : 端口号
 *
 * @retval     0: 初始化失败
 * @retval    >0: 初始化成功
 ******************************************************************************
 */
unsigned int socket_init(const char *pHostName, unsigned short port)
{
#ifdef __WIN32
    SOCKET sockfd;
    SOCKADDR_IN server_addr;
    WSADATA wsaData;
#else
    int sockfd = -1;
    struct sockaddr_in server_addr;
#endif
    struct hostent *host;
    int time_out = 1000 * 15; //超时15s

    do
    {
#ifdef __WIN32
        // Initialize Winsock
        if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
        {
            log_print("Error at WSAStartup()\n");
            break;
        }
#endif

        if((host = gethostbyname(pHostName)) == NULL)
        {
            log_print("%s gethostname error\n", __FUNCTION__);
            break;
        }

        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            log_print("socket error:%s\a\n", strerror(errno));
            break;
        }

        memset(&server_addr, 0x00, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr = *((struct in_addr*)host->h_addr);

        if (connect(sockfd, (struct sockaddr *)(&server_addr),
                sizeof(struct sockaddr)) == -1)
        {
            log_print("connect error:%s\n", strerror(errno));
            break;
        }
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&time_out, sizeof(int));
        return (unsigned int)sockfd;
    } while(0);

    return 0u;
}

/**
 ******************************************************************************
 * @brief      套接字发送数据
 * @param[in]  socket   : 套接字句柄
 * @param[in]  *pbuf    : 发送数据首地址
 * @param[in]  size     : 发送数据长度
 *
 * @retval     -1   : 发送失败
 * @retval     size : 发送成功
 ******************************************************************************
 */
int socket_send(unsigned int socket, const char *pbuf, int size)
{
    if (socket == 0)
    {
        return -1;
    }
    return send(socket, pbuf, size, 0);
}

/**
 ******************************************************************************
 * @brief      套接字接收数据
 * @param[in]  socket   : 套接字句柄
 * @param[in]  *pbuf    : 接收数据首地址
 * @param[in]  size     : 希望接收数据长度
 *
 * @retval     -1   : 接收失败
 * @retval     size : 接收成功
 ******************************************************************************
 */
int socket_recv(unsigned int socket, char *pbuf, int size)
{
    if (socket == 0)
    {
        return -1;
    }
    return recv(socket, pbuf, size, 0);
}

/**
 ******************************************************************************
 * @brief      套接字关闭
 * @param[in]  socket   : 套接字句柄
 *
 * @return  None
 ******************************************************************************
 */
void socket_close(unsigned int socket)
{
    if (socket != 0)
    {

#ifdef __WIN32
        closesocket(socket);
        WSACleanup(); //needed in winsock
#else
        close(socket);
#endif
    }
}

/*----------------------------socket.c--------------------------------*/
