#include "video.h"
#include <iostream>

MutedSegmentType::MutedSegmentType(json mutedSegmentJson)
{
  m_duration = mutedSegmentJson["duration"];
  m_offset = mutedSegmentJson["offset"];
}

VideoDataType::VideoDataType(json videoDataJson)
{
  m_id = videoDataJson["id"];
  if (!videoDataJson["stream_id"].is_null())
    m_streamId = videoDataJson["stream_id"];
  m_userId = videoDataJson["user_id"];
  m_userLogin = videoDataJson["user_login"];
  m_userName = videoDataJson["user_name"];
  m_title = videoDataJson["title"];
  m_description = videoDataJson["description"];
  m_createdAt = videoDataJson["created_at"];
  m_publishedAt = videoDataJson["published_at"];
  m_url = videoDataJson["url"];
  m_thumbnailUrl = videoDataJson["thumbnail_url"];
  m_viewable = videoDataJson["viewable"];
  m_viewCount = videoDataJson["view_count"];
  m_language = videoDataJson["language"];
  m_type = VideoTypeEnum((std::string)videoDataJson["type"]);
  m_duration = videoDataJson["duration"];

  if (!videoDataJson["muted_segments"].is_null())
  {
    for (auto& seg : videoDataJson["muted_segments"])
    {
      m_mutedSegments.push_back(MutedSegmentType(seg));
    }
  }
}

VideoResponseType::VideoResponseType(json videoResponseJson)
{
  for (auto& vidData : videoResponseJson["data"])
  {
    m_data.push_back(VideoDataType(vidData));
  }

  m_pagination = PaginationType(videoResponseJson["pagination"]);
}
