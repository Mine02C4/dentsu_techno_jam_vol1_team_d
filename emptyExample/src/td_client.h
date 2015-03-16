#pragma once

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <vector>
#include <limits>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

struct Kansei{
  double interest;
  double drowsiness;
  double concentration;
  double stress;
  double like;
};

class TdClient{
  std::string str_;
  //std::vector<TdDatabase> databases_;
  std::vector<Kansei> kanseis_;
  http_client* client_;
  long long job_id_;
public:
  TdClient();
  ~TdClient();
  std::string getStr();
  void getDatabases();
  void postJob();
  long long getJobId();
  void setJobId(long long);
  bool checkJobFinished();
  bool fetchResult();
};