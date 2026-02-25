#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>

#define PORT 2077;

typedef struct {
  SOCKET sock;
  SOCKADDR_IN peerAddr;
} ThreadParams; 

typedef struct {
  int Py;   // Is the Y position of the opposing player 
} Packet;

extern volatile int remotePy;
extern volatile int localPy;

DWORD WINAPI NetworkThread(LPVOID param);
