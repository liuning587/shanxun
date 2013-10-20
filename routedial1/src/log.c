/**
 ******************************************************************************
 * @file      log.c
 * @brief     日志记录模块
 * @details   This file including all API functions's 
 *            implement of log.c.	
 *
 * @copyright
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "config.h"
#include "log.h"

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
#ifndef DEFAULT_LOG_FILE_NAME
# define DEFAULT_LOG_FILE_NAME   "./MStationServer.txt"  /**< 默认日志文件 */
#endif

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
static char the_log_flag = 1;   /**< 日志记录标志 */
static FILE *the_log_fp = NULL;

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief      日志模块初始化
 * @param[in]  *pname : 日志文件
 * @param[in]  logflag: 是否记录日志
 *
 * @retval     0 : 初始化成功
 * @retval    -1 : 初始化失败
 ******************************************************************************
 */
int
log_init(void)
{
    if (the_log_fp == NULL)
    {
        the_log_fp = fopen(DEFAULT_LOG_FILE_NAME, "a+");
        if (the_log_fp == NULL)
        {
            return -1;
        }
    }
    return 0;
}

/**
 ******************************************************************************
 * @brief      日志模块退出
 * @param[in]  None
 *
 * @retval  NONE
 ******************************************************************************
 */
void
log_exit(void)
{
    if (the_log_fp != NULL)
    {
        (void)fclose(the_log_fp);
        the_log_fp = NULL;
    }
}

/**
 ******************************************************************************
 * @brief      设置是否记录日志
 * @param[in]  logflag: 是否记录日志(0:不记录 1:记录)
 *
 * @retval  NONE
 ******************************************************************************
 */
void
log_on(char logflag)
{
    the_log_flag = logflag & 0x01;
}

/**
 ******************************************************************************
 * @brief      记录buf
 * @param[in]  *pformat : 名称
 * @param[in]  *pbuffer : 数据首地址
 * @param[in]  len      : 长度
 *
 * @retval     None
 ******************************************************************************
 */
void
log_buf(const char *pformat,
        const char *pbuffer,
        int len)
{
    int i;

    if ((the_log_fp != NULL) && (the_log_flag))
    {
        (void)fprintf(the_log_fp, pformat);
        for (i = 0; i < len; i++)
        {
            (void)fprintf(the_log_fp, "%02X ", *(pbuffer + i));
        }
        (void)fprintf(the_log_fp, "\n");

        (void)printf(pformat);
        for (i = 0; i < len; i++)
        {
            (void)printf("%02X ", *(pbuffer + i));
        }
        (void)printf("\n");
    }
}

/**
 ******************************************************************************
 * @brief      日志print
 * @param[in]  fmt  : 日志信息与printf相同
 *
 * @retval  None
 ******************************************************************************
 */
void
log_print(const char *fmt, ...)
{
    va_list args;

    if ((the_log_fp != NULL) && (the_log_flag))
    {
        struct tm daytime;
        time_t stime = time(NULL);
        daytime = *localtime(&stime);
        (void)fprintf(the_log_fp, "[%04d-%02d-%02d %02d:%02d:%02d]",
                daytime.tm_year + 1900,
                daytime.tm_mon + 1,
                daytime.tm_mday,
                daytime.tm_hour,
                daytime.tm_min,
                daytime.tm_sec);
        va_start( args, fmt );
        (void)vfprintf(the_log_fp, fmt, args);
        (void)vprintf(fmt, args);
    }
}
/*----------------------------------log.c------------------------------------*/
