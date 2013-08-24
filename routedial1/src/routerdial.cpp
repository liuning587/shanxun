/**
 ******************************************************************************
 * @file      routerdial.c
 * @brief     C Source file of routerdial.c.
 * @details   This file including all API functions's 
 *            implement of routerdial.c.	
 *
 * @copyright .
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "ini.h"
#include "socket.h"
#include "urldecode.h"

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
#define DLL1_API extern"C" __declspec(dllexport)

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
/**
 * 一下字符串有三个参数
 * 1：用户名
 * 2：密码
 * 3：路由器地址
 */
#if 0
/* 水星路由器 */
static const char *pTPlinkchar = "GET /userRpm/PPPoECfgRpm.htm?wantype=2&VnetPap=0&acc=%s&psw=%s&linktype=4&waittime2=0&Connect=%%C1%%AC+%%BD%%D3 HTTP/1.1\r\n"
"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/xaml+xml, application/vnd.ms-xpsdocument, application/x-ms-xbap, application/x-ms-application, application/QVOD, application/QVOD, */*\r\n"
"Referer: http://192.168.1.1/userRpm/PPPoECfgRpm.htm\r\n"
"Accept-Language: zh-cn\r\n"
"Accept-Encoding: gzip, deflate\r\n"
"User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1) ; .NET CLR 3.0.04506.30; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; .NET CLR 2.0.50727)\r\n"
"Host: 192.168.1.1\r\n"
"Connection: Keep-Alive\r\n"
"Authorization: Basic YWRtaW46YWRtaW4=\r\n\r\n";
#endif
#if 1
/* TP-LINK路由器 */
static const char *pTPlinkchar = "GET /userRpm/PPPoECfgRpm.htm?wantype=2&VnetPap=0&acc=%s&psw=%s&linktype=4&waittime2=0&Connect=%%C1%%AC+%%BD%%D3 HTTP/1.1\r\n"
        "Accept: */*\r\n"
        "Accept-Language: zh-cn\r\n"
        "UA-CPU: x86\r\n"
        "Accept-Encoding: gzip, deflate\r\n"
        "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1) ; .NET CLR 3.0.04506.30; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; .NET CLR 2.0.50727)\r\n"
        "Host: %s\r\n"
        "Connection: Keep-Alive\r\n"
        "Authorization: Basic YWRtaW46YWRtaW4=\r\n\r\n";

/**
 * 一下字符串有三个参数
 * 1：用户名
 * 2：密码
 * 3: 密码
 * 4：路由器地址
 * 5：路由器地址
 */
/* TP-LINK路由器new(800) */
static const char *pTPlinkchar800 = "GET /userRpm/PPPoECfgRpm.htm?wan=0&wantype=2&acc=%s&psw=%s&confirm=%s&specialDial=100&SecType=0&sta_ip=0.0.0.0&sta_mask=0.0.0.0&linktype=4&waittime2=15&Save=%%B1%%A3+%%B4%%E6 HTTP/1.1\r\n"
        "Accept: text/html, application/xhtml+xml, */*\r\n"
        "Referer: http://%s/userRpm/PPPoECfgRpm.htm\r\n"
        "Accept-Language: zh-cn\r\n"
        "Accept-Encoding: gzip, deflate\r\n"
        "User-Agent: Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0)\r\n"
        "Host: %s\r\n"
        "Connection: Keep-Alive\r\n"
        "Cookie: tLargeScreenP=1; Authorization=Basic%%20YWRtaW46YWRtaW4%%3D; subType=pcSub; TPLoginTimes=1\r\n\r\n";
#endif
/* 腾达路由器 */
#if 1
/**
 * 一下字符串有三个参数
 * 1. 路由器地址
 * 2. 用户名长度+密码长度+148
 * 3：time(NULL)
 * 4: 用户名
 * 5：密码
 */
static const char *pTendaChar = "POST /goform/AdvSetWan HTTP/1.1\r\n"
        "Accept: */*\r\n"
        "Accept-Language: zh-cn\r\n"
        "UA-CPU: x86\r\n"
        "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1) ; .NET CLR 3.0.04506.30; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; .NET CLR 2.0.50727)\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Accept-Encoding: gzip, deflate\r\n"
        "Host: %s\r\n"
        "Content-Length:%d\r\n"
        "Connection: Keep-Alive\r\n"
        "Cache-Control: no-cache\r\n"
        "Cookie: admin:languange=cn\r\n\r\n"
        "GO=wan_connectd.asp&rebootTag=&v12_time=%d.738&WANT2=3&WANT1=2&PUN=%s&PPW=%s&MTU=1492&SVC=&AC=&PIDL=60&PCM=2&hour1=0&minute1=0&hour2=0&minute2=0";
#endif
/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
static char serverip[16] = {0};
static unsigned short port = 0u;
static char logflag = 0;
/**
 * 路由器类型:
 * 0: 水星
 * 1: TP-link   WR710
 * 2: TP-link   WR800
 * 3: Tenda
 */
static int gateway_type = 1;   /* 路由器类型 */

/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
static unsigned int
connect_start(void)
{
    (void)ini_get_server_ip(serverip);
    (void)ini_get_server_port(&port);
    (void)ini_get_log_flag(&logflag);
    (void)ini_get_log_type(&gateway_type);

    (void)log_init();
    log_on(logflag);
    return socket_init(serverip, port);
}

static void
connect_close(unsigned int socketfd)
{
    socket_close(socketfd);
    log_exit();
}

//
extern"C" __declspec(dllexport) int _stdcall _RouterDial(char *pusr, char *passwd)
{
    unsigned int socket = 0;
    char sendbuf[2048] = {0};
    int sendlen = 0;

    if ((socket = connect_start()) == 0)
    {
        log_print("connect_start err arg: usr[0x%08x]:%s passwd[0x%08x]%s\n",
                __FUNCTION__, pusr, pusr, passwd, passwd);
        log_exit();
        return 0;
    }
#if 0
    log_print("in %s() arg: usr[0x%08x]:%s passwd[0x%08x]%s\n",
            __FUNCTION__, pusr, pusr, passwd, passwd);
#endif

    do
    {
        if (gateway_type == 0 || gateway_type == 1)
        {
            /* 水星和tplink */
            /* 将用户名转换为urlcode */
            char *pusrname = url_encode(pusr);
            sprintf(sendbuf, pTPlinkchar, pusrname, passwd, serverip);
            free(pusrname); /* 用完后释放 */
            sendlen = strlen(sendbuf) + 1;
        }
        else if (gateway_type == 2)
        {
            log_print("新TP-link 800\n");
            /* 将用户名转换为urlcode */
            char *pusrname = url_encode(pusr);
            sprintf(sendbuf, pTPlinkchar800, pusrname, passwd, passwd, serverip, serverip);
            free(pusrname); /* 用完后释放 */
            sendlen = strlen(sendbuf) + 1;
        }
        else if (gateway_type == 3)
        {
            int ContentLen = 149 + strlen(pusr) + strlen(passwd);
            sprintf(sendbuf, pTendaChar, serverip, ContentLen, time(NULL), pusr, passwd);
            sendlen = strlen(sendbuf) + 1;
        }
        else
        {
            log_print("暂时不支持gateway_type[%d]\n", gateway_type);
            break;
        }

        log_print("send:\n%s\n", sendbuf);
        if (sendlen != socket_send(socket, sendbuf, sendlen))
        {
            log_print("%s发送数据数据出错\n", __FUNCTION__);
            break;
        }
        else
        {
            log_print("%s发送数据数据成功\n", __FUNCTION__);
        }
#if 0
        log_print("recv:\n");
        while (0 < socket_recv(socket, sendbuf, sizeof(sendbuf)))
        {
            log_print("%s", sendbuf);
        }
#endif
    } while(0);
    connect_close(socket);

    return 0;
}

/*----------------------------routerdial.c--------------------------------*/
