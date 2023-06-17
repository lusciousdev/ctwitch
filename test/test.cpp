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

    ctwitch::ClipResponseType clip = twitchApi.GetClip("DepressedFunnyEagleLeeroyJenkins-Kv_NpqUNkpqTpGgO");

    std::cout << std::setw(2) << clip.ToJson() << std::endl;
  }
  else
  {
    std::cerr << "Failed to open secrets file. Either supply a proper path or place \"secrets.txt\" in the cwd." << std::endl;
  }
}
