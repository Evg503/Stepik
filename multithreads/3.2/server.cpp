
#include <sys/epoll.h>
#include "common.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

#include <set>


constexpr int MAX_EVENTS = 32;

int main(int argc, char const *argv[])
{
  std::set<int> clients;
  int main_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  struct sockaddr_in sock_addr;
  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(12345);
  sock_addr.sin_addr.s_addr = htons(INADDR_ANY);
  bind(main_socket, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
  set_nonblock(main_socket);
  listen(main_socket, SOMAXCONN);

  int e_poll = epoll_create1(0);
  struct epoll_event event;

  event.data.fd = main_socket;
  event.events = EPOLLIN;
  epoll_ctl(e_poll, EPOLL_CTL_ADD, main_socket, &event);

  while(true)
  {
    struct epoll_event events[MAX_EVENTS];
    int n = epoll_wait(e_poll, events, MAX_EVENTS, -1);

    for(int i = 0; i < n; ++i)
    {
      if(events[i].data.fd == main_socket)
      {
        int new_socket = accept(main_socket, 0, 0);
        set_nonblock(new_socket);
        event.data.fd = new_socket;
        event.events = EPOLLIN;
        clients.insert(new_socket);
        epoll_ctl(e_poll, EPOLL_CTL_ADD, new_socket, &event);
      } else {
        static char buff[1024];
        int r = recv(events[i].data.fd, buff, sizeof(buff), MSG_NOSIGNAL);
        if ((r == 0) && (errno != EAGAIN))
        {
          epoll_ctl(e_poll, EPOLL_CTL_DEL, events[i].data.fd, nullptr);
          clients.erase(events[i].data.fd);
          close(events[i].data.fd);
        }
        if (r>0)
        {
          for(int fd: clients)
          {
            send(fd, buff, r, MSG_NOSIGNAL);
          }
        }
      }
    }
  }

  /* code */
}
