#include "realtime.h"

Realtime::Realtime(std::function <void(Kansei)> handler) {
  handler_ = handler;
  client_ = new websocket_callback_client();
  client_->connect(U("ws://ec2-54-153-123-10.us-west-1.compute.amazonaws.com:80/ws")).then([](){});
  client_->set_message_handler([this](websocket_incoming_message msg) {
    auto str = msg.extract_string().get();
    std::cout << str << std::endl;
    Kansei kansei;
    auto json_line = json::value::parse(utility::conversions::to_string_t(str));
    kansei.interest =
      json_line[U("interest")].is_null() ? std::numeric_limits<double>::quiet_NaN() : json_line[U("interest")].as_integer();
    kansei.drowsiness =
      json_line[U("drowsiness")].is_null() ? std::numeric_limits<double>::quiet_NaN() : json_line[U("interest")].as_integer();
    kansei.concentration =
      json_line[U("concentration")].is_null() ? std::numeric_limits<double>::quiet_NaN() : json_line[U("interest")].as_integer();
    kansei.stress =
      json_line[U("stress")].is_null() ? std::numeric_limits<double>::quiet_NaN() : json_line[U("interest")].as_integer();
    kansei.like =
      json_line[U("like")].is_null() ? std::numeric_limits<double>::quiet_NaN() : json_line[U("interest")].as_integer();
    handler_(kansei);
  });
}
