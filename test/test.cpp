#include <iostream>
#include <fstream>
#include <string>

#include "video.h"
#include "clip.h"
#include "ctwitch.h"

int main(int argc, char** argv)
{
  std::string secretsPath = "secrets.txt";
  if (argc > 1)
  {
    secretsPath = std::string(argv[1]);
  }

  std::ifstream secretsFile(secretsPath);

  if (secretsFile.is_open())
  {
    std::string clientId, clientSecret;
    std::getline(secretsFile, clientId);
    std::getline(secretsFile, clientSecret);

    ctwitch::api twitchApi = ctwitch::api(clientId, clientSecret);

    ctwitch::ClipResponseType clip = twitchApi.GetBroadcasterClips("43246220", "2020-01-01T00:00:01Z", "2023-12-31T23:59:59Z", 5);

    std::cout << "Clip count: " << clip.GetData().size() << std::endl;
    std::cout << std::setw(2) << clip.ToJson() << std::endl;

    ctwitch::VideoResponseType video = twitchApi.GetUserVideos("43246220");

    std::cout << "Video count: " << video.GetData().size() << std::endl;
    std::cout << std::setw(2) << video.ToJson() << std::endl;
  }
  else
  {
    std::cerr << "Failed to open secrets file. Either supply a proper path or place \"secrets.txt\" in the cwd." << std::endl;
  }
}
