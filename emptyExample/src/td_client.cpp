#include "td_client.h"
#include "td_client.h"
#include "apikey.h"

TdClient::TdClient(){
  // Create http_client to send the request.
  client_ = new http_client(U("http://api.treasuredata.com/"));
}

void TdClient::getDatabases() {
  auto fileStream = std::make_shared<ostream>();
  // Open stream to output file.
  pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile) {
    *fileStream = outFile;
    http_request request(methods::GET);
    request.headers().add(L"AUTHORIZATION", kTDApiKey);
    request.set_request_uri(L"/v3/database/list");
    return client_->request(request);
  })
    // Handle response headers arriving.
    .then([=](http_response response) {
    printf("Received response status code:%u\n", response.status_code());

    const json::value json = response.extract_json().get();
    std::wcout << json.to_string() << std::endl;
    str_ = ::utility::conversions::to_utf8string(json.to_string());

    // Write response body into the file.
    return response.body().read_to_end(fileStream->streambuf());
  })
    // Close the file stream.
    .then([=](size_t) {
    return fileStream->close();
  });

  // Wait for all the outstanding I/O to complete and handle any exceptions
  try
  {
    requestTask.wait();
  }
  catch (const std::exception &e)
  {
    printf("Error exception:%s\n", e.what());
  }
}

void TdClient::postJob() {
  auto fileStream = std::make_shared<ostream>();
  pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile) {
    *fileStream = outFile;
    http_request request(methods::POST);
    request.headers().add(L"AUTHORIZATION", kTDApiKey);
    //request.headers().add(L"Content-Type", L"application/x-www-form-urlencoded");
    request.set_request_uri(L"/v3/job/issue/hive/eeg_datasets");
    request.set_body(
      //L"query=SELECT%20%0A%20%20AVG(concentration)%20AS%20concentration%2C%0A%20%20AVG(interest)%20AS%20interest%2C%0A%20%20AVG(drowsiness)%20AS%20drowsiness%2C%0A%20%20AVG(stress)%20AS%20stress%0AFROM%0A%20%20kansei%0AWHERE%0A%20%20time_value%20%3C%20100%0A%20%20AND%20time_value%20%3E%2040%0A%3B",
      L"query=SELECT%20%0A%20%20interest%2C%0A%20%20drowsiness%2C%0A%20%20concentration%2C%0A%20%20stress%2C%0A%20%20like%0AFROM%0A%20%20kansei%0AWHERE%0A%20%20TD_TIME_RANGE(time%2C%0A%20%20%20%20TD_TIME_ADD('2015-03-10%2011%3A17%3A00%20JST'%2C%0A%20%20%20%20%20%20'-1m')%2C%0A%20%20%20%20'2015-03-10%2011%3A17%3A00%20JST')",
      L"application/x-www-form-urlencoded");
    basic_istream<unsigned char> body_stream;
    return client_->request(request);
  })
    // Handle response headers arriving.
    .then([=](http_response response) {
    printf("Received response status code:%u\n", response.status_code());
    json::value json = response.extract_json().get();
    std::wcout << json.to_string() << std::endl;
    str_ = ::utility::conversions::to_utf8string(json.to_string());
    job_id_ = std::stoll(json[U("job_id")].as_string());
    fileStream->write(str_.c_str());
    fileStream->close();
    // Write response body into the file.
  });
  // Close the file stream.
  //.then([=](size_t) {
  //});
  // Wait for all the outstanding I/O to complete and handle any exceptions
  try
  {
    requestTask.wait();
  }
  catch (const std::exception &e)
  {
    printf("Error exception:%s\n", e.what());
  }
}

bool TdClient::checkJobFinished() {
  http_request request(methods::GET);
  request.headers().add(L"AUTHORIZATION", kTDApiKey);
  //request.headers().add(L"Content-Type", L"application/x-www-form-urlencoded");
  request.set_request_uri(L"/v3/job/status/" + std::to_wstring(job_id_));
  pplx::task<bool> requestTask = client_->request(request)
    // Handle response headers arriving.
    .then([=](http_response response) {
    printf("Received response status code:%u\n", response.status_code());
    json::value json = response.extract_json().get();
    std::wcout << json.to_string() << std::endl;
    str_ = ::utility::conversions::to_utf8string(json.to_string());
    auto hoge = json[U("status")].as_string();
    if (hoge == L"success" || hoge == L"error") {
      return false;
    }
    else {
      return true;
    }
  });
  try
  {
    requestTask.wait();
    return requestTask.get();
  }
  catch (const std::exception &e)
  {
    printf("Error exception:%s\n", e.what());
    return false;
  }
}

bool TdClient::fetchResult() {
  http_request request(methods::GET);
  request.headers().add(L"AUTHORIZATION", kTDApiKey);
  request.set_request_uri(L"/v3/job/result/" + std::to_wstring(job_id_) + L"?format=json");
  pplx::task<bool> requestTask = client_->request(request)
    .then([=](http_response response) {
    printf("Received response status code:%u\n", response.status_code());
    //response.headers().set_content_type(L"application/json");
    std::wcout << response.to_string() << std::endl;
    auto stream = response.body();
    while (!stream.is_eof()) {
      container_buffer<std::string> in_string_buffer;
      stream.read_line(in_string_buffer).then([this, in_string_buffer](size_t bytes_read){
        if (bytes_read > 0) {
          const utility::string_t &line = utility::conversions::to_string_t(in_string_buffer.collection());
          auto json_line = json::value::parse(line);
          Kansei kansei;
          kansei.interest = json_line[0].is_null() ? 0 : _wtoi(json_line[0].as_string().c_str());
          kansei.drowsiness = json_line[1].is_null() ? 0 : _wtoi(json_line[1].as_string().c_str());
          kansei.concentration = json_line[2].is_null() ? 0 : _wtoi(json_line[2].as_string().c_str());
          kansei.stress = json_line[3].is_null() ? 0 : _wtoi(json_line[3].as_string().c_str());
          kansei.like = json_line[4].is_null() ? 0 : _wtoi(json_line[4].as_string().c_str());
          kanseis_.push_back(kansei);
        }
      });
      in_string_buffer.close();
    }
    /*stream.read_to_end(in_string_buffer).then([this,in_string_buffer](size_t bytes_read){
      const std::string &str_data = in_string_buffer.collection();
      while (std::getline(str_data)) {

      }
      const utility::string_t &data = U("[") + utility::conversions::to_string_t() + U("]");
      auto json_data = json::value::parse(data);
      for (int i = 0; i < json_data.size(); i++) {
        Kansei kansei;
        kansei.interest = _wtoi(json_data[i][0].as_string().c_str());
        kansei.drowsiness = _wtoi(json_data[i][1].as_string().c_str());
        kansei.concentration = _wtoi(json_data[i][2].as_string().c_str());
        kansei.stress = _wtoi(json_data[i][3].as_string().c_str());
        kansei.like = _wtoi(json_data[i][4].as_string().c_str());
        kanseis_.push_back(kansei);
      }
    });*/
    //json::value json = response.extract_json().get();
    //str_ = ::utility::conversions::to_utf8string(json.to_string());
    return true;
  });
  try
  {
    requestTask.wait();
    return requestTask.get();
  }
  catch (const std::exception &e)
  {
    printf("Error exception:%s\n", e.what());
    return true;
  }
}

TdClient::~TdClient(){
}

std::string TdClient::getStr() {
  return str_;
}

long long TdClient::getJobId() {
  return job_id_;
}

void TdClient::setJobId(long long job_id) {
  job_id_ = job_id;
}