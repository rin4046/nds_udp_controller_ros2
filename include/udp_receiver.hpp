#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

class UDPReceiver {
  int sock_;
  sockaddr_in addr_ = {0};
  bool is_open_ = false;

public:
  UDPReceiver() = default;

  ~UDPReceiver() {
    close();
  }

  bool open(uint16_t port) {
    if (is_open_) {
      return false;
    }
    if ((sock_ = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
      return false;
    }
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = INADDR_ANY;
    addr_.sin_port = htons(port);
    if (bind(sock_, reinterpret_cast<sockaddr *>(&addr_), sizeof(addr_)) != 0) {
      return false;
    }
    is_open_ = true;
    return true;
  }

  bool close() {
    if (!is_open_) {
      return false;
    }
    if (::close(sock_) != 0) {
      return false;
    }
    is_open_ = false;
    return true;
  }

  bool receive(void *data, size_t size) {
    if (!is_open_) {
      return false;
    }
    if (recv(sock_, data, size, 0) == -1) {
      return false;
    }
    return true;
  }

  template <class T> bool receive(T &data) {
    return receive(&data, sizeof(data));
  }
};
