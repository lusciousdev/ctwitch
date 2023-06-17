#include "ctwitch.h"

#include <curl/curl.h>
#include <iostream>
#include <stdexcept>

using namespace ctwitch;

size_t ctwitch::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct*)userp;

  char *ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);

  if (ptr == NULL)
  {
    printf("error: not enough memory\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

api::api()
  : m_handle(curl_easy_init())
{
  if (!m_handle)
  {
    throw std::runtime_error("Failed to create handle for CURL.");
  }
}

api::api(std::string clientId, std::string clientSecret)
  : api()
{
  m_clientId = clientId;
  m_clientSecret = clientSecret;

  std::vector<std::array<std::string, 2>> params = { { "client_id", m_clientId }, { "client_secret", m_clientSecret }, { "grant_type", "client_credentials" }};
  std::vector<std::string> headers = { "Content-Type: application/x-www-form-urlencoded" };

  std::string postResp = Post(OAUTH_URL, "/token", params, headers);

  try
  {
    json postJson = json::parse(postResp);

    m_accessToken = postJson["access_token"];
  }
  catch(const std::exception& e)
  {
    std::cerr << "Client Credential Auth Error: " << e.what() << '\n';
  }
  

  std::string clientIdHeader = "Client-Id: " + clientId;
  std::string authHeader = "Authorization: Bearer " + m_accessToken;
  m_defaultHeaders = { clientIdHeader, authHeader };
}

api::~api()
{
  curl_easy_cleanup(m_handle);
}

ClipResponseType api::GetClip(std::string clipId)
{
  std::vector<std::array<std::string, 2>> params = { { "id", clipId } };

  std::string apiResp = Get(API_URL, "/clips", params, m_defaultHeaders);

  json apiJson = json::parse(apiResp);

  return ClipResponseType(apiJson);
}

std::string api::Get(std::string baseUrl, std::string endpoint, std::vector<std::array<std::string, 2>> parameters, std::vector<std::string> headers)
{
  m_handle = curl_easy_init();

  struct curl_slist *headerList = NULL;
  for (auto& header : headers)
  {
    headerList = curl_slist_append(headerList, header.c_str());
  }

  std::string endpointUrl = baseUrl + endpoint;

  CURLU* url = curl_url();
  CURLUcode ures = curl_url_set(url, CURLUPART_URL, endpointUrl.c_str(), CURLU_URLENCODE);

  if (ures != CURLUE_OK)
  {
    std::cerr << "URL ERROR: " << curl_url_strerror(ures) << std::endl;
    return std::string("{}");
  }

  for (auto& param : parameters)
  {
    std::string fullParam = param[0] + "=" + param[1];

    ures = curl_url_set(url, CURLUPART_QUERY, fullParam.c_str(), CURLU_APPENDQUERY | CURLU_URLENCODE);

    if (ures != CURLUE_OK)
    {
      std::cerr << "URL ERROR: " << curl_url_strerror(ures) << std::endl;
      return std::string("{}");
    }
  }

  struct MemoryStruct chunk;
  chunk.memory = (char*)malloc(1);
  chunk.size = 0;

  curl_easy_setopt(m_handle, CURLOPT_CURLU, url);
  curl_easy_setopt(m_handle, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(m_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(m_handle, CURLOPT_WRITEDATA, (void*)&chunk);
  curl_easy_setopt(m_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  curl_easy_setopt(m_handle, CURLOPT_HTTPHEADER, headerList);
  curl_easy_setopt(m_handle, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);

  CURLcode res = curl_easy_perform(m_handle);

  if (res != CURLE_OK)
  {
    fprintf(stderr, "ERROR: %s\n", curl_easy_strerror(res));
    free(chunk.memory);
    return std::string("{}");
  }
  else
  {
    std::string respStr = std::string(chunk.memory);
    free(chunk.memory);
    curl_easy_cleanup(m_handle);
    return respStr;
  }
}

std::string api::Post(std::string baseUrl, std::string endpoint, std::vector<std::array<std::string, 2>> parameters, std::vector<std::string> headers)
{
  m_handle = curl_easy_init();

  struct curl_slist *headerList = NULL;
  for (auto& header : headers)
  {
    headerList = curl_slist_append(headerList, header.c_str());
  }

  std::string endpointUrl = baseUrl + endpoint;

  CURLU* url = curl_url();
  CURLUcode ures = curl_url_set(url, CURLUPART_URL, endpointUrl.c_str(), CURLU_URLENCODE);

  if (ures != CURLUE_OK)
  {
    std::cerr << "URL ERROR: " << curl_url_strerror(ures) << std::endl;
    return std::string("{}");
  }

  std::string payload = "";

  for (auto& param : parameters)
  {
    std::string combo = param[0] + "=" + param[1];
    payload = payload + combo + "&";
  }
  payload.pop_back();

  struct MemoryStruct chunk;
  chunk.memory = (char*)malloc(1);
  chunk.size = 0;

  curl_easy_setopt(m_handle, CURLOPT_CURLU, url);
  curl_easy_setopt(m_handle, CURLOPT_POSTFIELDSIZE, payload.size());
  curl_easy_setopt(m_handle, CURLOPT_POSTFIELDS, payload.c_str());
  curl_easy_setopt(m_handle, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(m_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(m_handle, CURLOPT_WRITEDATA, (void*)&chunk);
  curl_easy_setopt(m_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  curl_easy_setopt(m_handle, CURLOPT_HTTPHEADER, headerList);
  curl_easy_setopt(m_handle, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);
  
  CURLcode res = curl_easy_perform(m_handle);

  if (res != CURLE_OK)
  {
    fprintf(stderr, "ERROR: %s\n", curl_easy_strerror(res));
    free(chunk.memory);
    return std::string("{}");
  }
  else
  {
    std::string respStr = std::string(chunk.memory);
    free(chunk.memory);
    curl_easy_cleanup(m_handle);
    return respStr;
  }
}

std::string api::Post(std::string baseUrl, std::string endpoint, std::vector<std::array<std::string, 2>> parameters, std::vector<std::string> headers, json payload)
{
  m_handle = curl_easy_init();

  struct curl_slist *headerList = NULL;
  for (auto& header : headers)
  {
    headerList = curl_slist_append(headerList, header.c_str());
  }

  std::string endpointUrl = baseUrl + endpoint;

  CURLU* url = curl_url();
  CURLUcode ures = curl_url_set(url, CURLUPART_URL, endpointUrl.c_str(), CURLU_URLENCODE);

  if (ures != CURLUE_OK)
  {
    std::cerr << "URL ERROR: " << curl_url_strerror(ures) << std::endl;
    return std::string("{}");
  }

  for (auto& param : parameters)
  {
    std::string fullParam = param[0] + "=" + param[1];

    ures = curl_url_set(url, CURLUPART_QUERY, fullParam.c_str(), CURLU_APPENDQUERY | CURLU_URLENCODE);

    if (ures != CURLUE_OK)
    {
      std::cerr << "URL ERROR: " << curl_url_strerror(ures) << std::endl;
      return std::string("{}");
    }
  }

  char* urlStr;
  curl_url_get(url, CURLUPART_URL, &urlStr, 0);
  std::cout << "Full URL: " << urlStr << std::endl;

  struct MemoryStruct chunk;
  chunk.memory = (char*)malloc(1);
  chunk.size = 0;

  curl_easy_setopt(m_handle, CURLOPT_CURLU, url);
  curl_easy_setopt(m_handle, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(m_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(m_handle, CURLOPT_WRITEDATA, (void*)&chunk);
  curl_easy_setopt(m_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  curl_easy_setopt(m_handle, CURLOPT_HTTPHEADER, headerList);
  curl_easy_setopt(m_handle, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);

  CURLcode res = curl_easy_perform(m_handle);

  if (res != CURLE_OK)
  {
    fprintf(stderr, "ERROR: %s\n", curl_easy_strerror(res));
    free(chunk.memory);
    return std::string("{}");
  }
  else
  {
    std::string respStr = std::string(chunk.memory);
    free(chunk.memory);
    curl_easy_cleanup(m_handle);
    return respStr;
  }
}