#pragma once

#include "td_client.h"
#include <cpprest/ws_client.h>

using namespace web;
using namespace web::websockets::client;

class Realtime {
  websocket_callback_client* client_;
  std::function <void(Kansei)> handler_;
public:
  Realtime(std::function <void(Kansei)>);
  ~Realtime();
};