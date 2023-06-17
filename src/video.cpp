#include "Video.h"
#include <iostream>

using namespace ctwitch;

MutedSegmentType::MutedSegmentType(json mutedSegmentJson)
{
  m_duration = mutedSegmentJson["duration"];
  m_offset = mutedSegmentJson["offset"];
}

json MutedSegmentType::ToJson()
{
  return { { "duration", m_duration }, { "offset", m_offset } };
}

VideoDataType::VideoDataType(json videoDataJson)
{
  m_id = videoDataJson["id"];
  if (!videoDataJson["stream_id"].is_null())
    m_streamId = videoDataJson["stream_id"];
  else
    m_streamId = "";
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

json VideoDataType::ToJson()
{
  json j = {
    { "id", m_id },
    { "stream_id", (m_streamId == "") ? (json)nullptr : (json)m_streamId },
    { "user_id", m_userId },
    { "user_login", m_userLogin },
    { "user_name", m_userName },
    { "title", m_title },
    { "description", m_description },
    { "created_at", m_createdAt },
    { "published_at", m_publishedAt },
    { "url", m_url },
    { "thumbnail_url", m_thumbnailUrl },
    { "viewable", m_viewable },
    { "view_count", m_viewCount },
    { "language", m_language },
    { "type", (std::string)m_type },
    { "duration", m_duration },
    { "muted_segments", (m_mutedSegments.size() > 0) ? json::array() : (json)nullptr }
  };

  if (m_mutedSegments.size() > 0)
  {
    for (auto& seg : m_mutedSegments)
    {
      j["muted_segments"].push_back(seg.ToJson());
    }
  }

  return j;
}

VideoResponseType::VideoResponseType(json videoResponseJson)
{
  for (auto& vidData : videoResponseJson["data"])
  {
    m_data.push_back(VideoDataType(vidData));
  }

  m_pagination = PaginationType(videoResponseJson["pagination"]);
}


json VideoResponseType::ToJson()
{
  json j = {
    { "data", json::array() },
    { "pagination", m_pagination.ToJson() }
  };

  for (auto& data : m_data)
  {
    j["data"].push_back(data.ToJson());
  }

  return j;
}