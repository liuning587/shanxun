/**
 ******************************************************************************
 * @file       log.h
 * @brief      日志记录模块
 * @details    This file including all API functions's declare of log.h.
 * @copyright
 *
 ******************************************************************************
 */
#ifndef LOG_H_
#define LOG_H_ 

#ifdef __cplusplus             /* Maintain C++ compatibility */
extern "C" {
#endif /* __cplusplus */
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Globals
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Prototypes
 ----------------------------------------------------------------------------*/
extern int log_init(void);
extern void log_exit(void);
extern void log_on(char logflag);
extern void log_buf(const char *pformat, const char *pbuffer, int len);
extern void log_print(const char *fmt, ...);

#ifdef __cplusplus      /* Maintain C++ compatibility */
}
#endif /* __cplusplus */
#endif /* LOG_H_ */
/*--------------------------End of log.h-----------------------------*/
