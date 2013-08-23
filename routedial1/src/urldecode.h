#ifndef __URLDECODE_H__
#define __URLDECODE_H__

#ifdef __cplusplus             /* Maintain C++ compatibility */
extern "C" {
#endif /* __cplusplus */

char from_hex(char ch);
char to_hex(char code);
char *url_encode(char *str);
char *url_decode(char *str);


#ifdef __cplusplus      /* Maintain C++ compatibility */
}
#endif /* __cplusplus */
#endif
