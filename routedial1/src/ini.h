/**
 ******************************************************************************
 * @file       ini.h
 * @brief      API include file of ini.h.
 * @details    This file including all API functions's declare of ini.h.
 * @copyright  Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 *
 ******************************************************************************
 */
#ifndef INI_H_
#define INI_H_ 

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
extern int ini_get_server_ip(char * pserverip);
extern int ini_get_server_port(unsigned short *pport);
extern int ini_get_log_flag(char *pflag);
extern int ini_get_log_type(int *ptype);

#ifdef __cplusplus      /* Maintain C++ compatibility */
}
#endif /* __cplusplus */
#endif /* INI_H_ */
/*--------------------------End of ini.h-----------------------------*/
