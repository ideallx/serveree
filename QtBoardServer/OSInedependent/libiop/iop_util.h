/*
 * Copyright (c) 2011-2014 zhangjianlin �ż���
 * eamil:jonas88@sina.com
 * addr: china
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _IOP_UTIL_H_
#define _IOP_UTIL_H_
#include "iop_config.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
typedef WSABUF iov_type;
typedef int iop_socklen_t;
//#define EINPROGRESS WSAEINPROGRESS
//#define EWOULDBLOCK WSAEWOULDBLOCK

#define IGNORE_SIGNAL(signo)    do{}while(0)
#define IGNORE_SIGPIPE()        do{}while(0)
#define SET_RLIMIT_NOFILE(num)  do{}while(0)

#define SOCK_STARTUP()  do{ \
                WSADATA     wsadata;    \
                WSAStartup(MAKEWORD( 2, 2 ),&wsadata);   \
            }while(0)        

#define SOCK_CLEANUP()  do{ \
                WSACleanup();   \
            }while(0)        

#else
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netdb.h>
#include <sys/socket.h>   
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

typedef struct iovec iov_type;
typedef socklen_t iop_socklen_t;
#define IGNORE_SIGNAL(signo)    signal(signo, SIG_IGN)
#define IGNORE_SIGPIPE()        signal(SIGPIPE, SIG_IGN)

#define SET_RLIMIT_NOFILE(num)  do{ \
                                            struct rlimit r;    \
                                            r.rlim_cur=num; \
                                            r.rlim_max=num; \
                                            setrlimit(RLIMIT_NOFILE,&r);    \
                                        }while(0)
#define SOCK_STARTUP()  do{}while(0)        
#define SOCK_CLEANUP()  do{}while(0)        

#endif



typedef struct sockaddr iop_sockaddr;
typedef struct sockaddr_in iop_sockaddr_in;

#define IOP_MAX(a,b) ((a)>(b)?(a):(b))
#define IOP_MIN(a,b) ((a)<(b)?(a):(b))

#define UC(b)   (((int)b)&0xff)  

#define INET_NTOA_R(in_addr, buf)   do{ \
                                        register char *p = (char *)&in_addr;    \
                                        sprintf(buf, "%d.%d.%d.%d", UC(p[0]), UC(p[1]), UC(p[2]), UC(p[3])); \
                                        }while(0)



#define IP_NTOA(ip, buf)    do{ \
                                        register char *p = (char *)&ip;    \
                                        sprintf(buf, "%d.%d.%d.%d", UC(p[0]), UC(p[1]), UC(p[2]), UC(p[3])); \
                                        }while(0)

#define SOCKADDR_IN(addr, ip, port) do{ \
                                memset(&(addr), 0, sizeof(addr)); \
                                (addr).sin_family      = AF_INET;     \
                                (addr).sin_addr.s_addr = inet_addr(ip);   \
                                (addr).sin_port        = htons(port);     \
                                if ((addr).sin_addr.s_addr == INADDR_NONE){    \
                                    struct hostent* pHost = gethostbyname(ip);  \
                                    if (pHost == NULL){return -1;}  \
                                    memcpy(&(addr).sin_addr, pHost->h_addr_list[0], pHost->h_length);} \
                                }while(0)
    
#define MAKE_TIMEVAL(tv, millisec)  do{ \
                                                if(millisec > 0){   \
                                                    tv.tv_sec = millisec / 1000;    \
                                                    tv.tv_usec = (millisec % 1000)*1000;    \
                                                } else{ \
                                                    tv.tv_sec = 0;  \
                                                    tv.tv_usec = 0; \
                                                }}while(0)
                                    
#define IOP_SOCK_STREAM()   socket(AF_INET, SOCK_STREAM, 0)
#define IOP_SOCK_DGRAM()   socket(AF_INET, SOCK_DGRAM, 0)

#define SOCK_TYPE_STREAM 0
#define SOCK_TYPE_DGRAM 1

io_handle_t iop_socket_stream();
io_handle_t iop_socket_datagram();                                                
int iop_close_handle(io_handle_t h);
int iop_read(io_handle_t h, void *buf, unsigned int count);
int iop_write(io_handle_t h, const void *buf, unsigned int count);

int iop_readv(io_handle_t h, iov_type *vec, int count);
int iop_writev(io_handle_t h, const iov_type *iov, int count);    

int iop_set_nonblock(io_handle_t h);
int iop_set_block(io_handle_t h);
int iop_sock_reuseaddr(io_handle_t h);
int iop_set_sock_recv_timeo(io_handle_t sock, int ms);
int iop_set_sock_snd_timeo(io_handle_t sock, int ms);

io_handle_t iop_tcp_server(const char *host, unsigned short port);
io_handle_t iop_udp_server(const char *host, unsigned short port);
int iop_connect(io_handle_t sock, const char *ip, unsigned short port);
int iop_do_connect(io_handle_t sock, const iop_sockaddr_in *addr);
int iop_connect_timeo(io_handle_t sock, const iop_sockaddr_in *addr, int msec);

io_handle_t iop_accept(io_handle_t sock, iop_sockaddr *addr, iop_socklen_t *len);
int iop_sendto(io_handle_t s, const void *buf, unsigned int len, int flags, const iop_sockaddr *to, iop_socklen_t tolen);
int iop_recvfrom(io_handle_t s, void *buf, unsigned int len, int flags, iop_sockaddr *from, iop_socklen_t *fromlen);


int open_dev_null(int fd);


iop_uint16_t iop_htons(iop_uint16_t x);
iop_uint32_t iop_htonl(iop_uint32_t x);
iop_uint16_t iop_ntohs(iop_uint16_t x);
iop_uint32_t iop_ntohl(iop_uint32_t x);

int iop_send_n(io_handle_t s, const char *buf, int len);
int iop_recv_n(io_handle_t s, char *buf, int len);

int iop_sock_bind(io_handle_t sock, const char *ip, const unsigned short port);
void iop_usleep(int usec);


#ifdef __cplusplus
}
#endif


#endif
