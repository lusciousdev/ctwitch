#ifndef _REQUESTS_H_
#define _REQUESTS_H_

#include <string>
#include <vector>
#include <array>
#include <memory>

#include "clip.h"
#include "video.h"
#include "json.hpp"

typedef void CURL;

namespace ctwitch
{
  const std::string API_URL = "https://api.twitch.tv/helix";
  const std::string OAUTH_URL = "https://id.twitch.tv/oauth2";

  struct MemoryStruct
  {
    char *memory;
    size_t size;
  };

  size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

  class api
  {
  public:
    api();
    api(std::string clientId, std::string clientSecret);
    ~api();

    ClipResponseType GetClip(std::string clipId);
    
  private:
    std::string m_clientId;
    std::string m_clientSecret;
    std::string m_accessToken;

    std::vector<std::string> m_defaultHeaders;

    CURL* m_handle;

    std::string Get(std::string url, std::string endpoint, std::vector<std::array<std::string, 2>> parameters, std::vector<std::string> headers);
    std::string Post(std::string url, std::string endpoint, std::vector<std::array<std::string, 2>> parameters, std::vector<std::string> headers);
    std::string Post(std::string url, std::string endpoint, std::vector<std::array<std::string, 2>> parameters, std::vector<std::string> headers, json payload);
  };
}

#endif