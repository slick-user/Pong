#include "net.h"

/* Imagine I can do some sort of multi threading where I can have both these processes ocurring concurrently but if that is what we wanted to do, I could have just done it in Go 
 * So we are using multithreading, we are using a peer to peer architecture so no longer for client server operations but so that the game process may run separate from the netcode (so they 
 * don't affect eachothers performance */

volatile int remotePy = 0;
volatile int localPy = 0;

// NETCODE THREAD
DWORD WINAPI NetworkThread(LPVOID param) {
  ThreadParams *p = (ThreadParams*)param;
  SOCKET sock = p->sock;
  SOCKADDR_IN peerAddr = p->peerAddr;
  int peerLen = sizeof(peerAddr);

  SOCKADDR_IN recvAddr;
  int recvLen = sizeof(recvAddr);

  Packet recvPacket;
  Packet sendPacket;

  while (1) {

    // SEND
    sendPacket.Py = localPy;
    int s = sendto(sock, (char*)&sendPacket, sizeof(Packet), 0,
           (struct sockaddr*)&peerAddr, peerLen);
    if (s == SOCKET_ERROR) {
      printf("sendto failed: %d\n", WSAGetLastError());
    }

    // RECEIVE
    int bytes = recvfrom(sock, (char*)&recvPacket, sizeof(Packet), 0,
                         (struct sockaddr*)&recvAddr, &recvLen); 
    if (bytes == SOCKET_ERROR) {
      int err = WSAGetLastError();
      if (err != WSAEWOULDBLOCK && err != WSAEINTR) {
        printf("recvfrom failed: %d\n", err);
      }
    } else if (bytes > 0) {
      remotePy = recvPacket.Py;
    }

    Sleep(33);
  }

  free(param);
  return 0;
}
