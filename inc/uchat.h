#ifndef UCHAT_H
#define UCHAT_H

#include "libmx.h"
#include <stdint.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sqlite3.h>

	/*==============SERVER CONFIG============*/
#define TCP_PORT 8080
#define DB_SOURCE "uchat_db"
    /*==============END SERVER CONFIG============*/


#define MESSAGE_LENGTH 2048
#define MAX_CLIENTS    8

#define WS_KEY_LEN     24
#define WS_MS_LEN      36
#define WS_KEYMS_LEN   (WS_KEY_LEN + WS_MS_LEN)
#define MAGIC_STRING   "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

#define WS_HS_REQ      "Sec-WebSocket-Key"

#define WS_HS_ACCLEN   130
#define WS_HS_ACCEPT                   \
	"HTTP/1.1 101 Switching Protocols\r\n" \
	"Upgrade: websocket\r\n"               \
	"Connection: Upgrade\r\n"              \
	"Sec-WebSocket-Accept: "               \

	/* Frame definitions. */
#define WS_FIN    128

	/* Frame types. */
#define WS_FR_OP_TXT  1
#define WS_FR_OP_CLSE 8

#define WS_FR_OP_UNSUPPORTED 0xF

#define SHA1HashSize 20
#define SHA1CircularShift(bits,word) \
                         (((word) << (bits)) | ((word) >> (32-(bits))))

/* Events. */
struct ws_events {
	/* void onopen(int fd); */
	void (*onopen)(int);
	/* void onclose(int fd); */
	void (*onclose)(int);
	/* void onmessage(int fd, unsigned char *message); */
	void (*onmessage)(int, const unsigned char *);
    /* void onlogin(int fd, unsigned char *message); */
    void (*onlogin)(int, const unsigned char *);
};

enum {
    shaSuccess = 0,
    shaNull,            /* Null pointer parameter */
    shaInputTooLong,    /* input data too long */
    shaStateError       /* called Input after Result */
};

typedef struct t_SHA1Context {
    uint32_t Intermediate_Hash[SHA1HashSize/4]; /* Message Digest  */
    uint32_t Length_Low;            /* Message length in bits      */
    uint32_t Length_High;           /* Message length in bits      */

    /* Index into message block array   */
    int_least16_t Message_Block_Index;
    uint8_t Message_Block[64];      /* 512-bit message blocks      */

    int Computed;               /* Is the digest computed?         */
    int Corrupted;             /* Is the message digest corrupted? */
} t_SHA1Context;


extern int getHSaccept(char *wsKey, unsigned char **dest);
extern int getHSresponse(char *hsrequest, char **hsresponse);

extern char* ws_getaddress(int fd);
extern int   ws_sendframe(int fd, const char *msg, bool broadcast);
extern int   ws_socket(struct ws_events *evs, uint16_t port);
unsigned char * base64_encode(const unsigned char *src, size_t len,
                              size_t *out_len);
unsigned char * base64_decode(const unsigned char *src, size_t len,
                              size_t *out_len);
int SHA1Reset(t_SHA1Context *);
int SHA1Input(t_SHA1Context *, const uint8_t *, unsigned int);
int SHA1Result( t_SHA1Context *, uint8_t Message_Digest[SHA1HashSize]);
void mx_init_sqli();

#endif
