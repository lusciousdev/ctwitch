#include "clip.h"
#include <iostream>

using namespace ctwitch;

ClipDataType::ClipDataType(json dataJson)
{
  m_id = dataJson["id"];
  m_url = dataJson["url"];
  m_embedUrl = dataJson["embed_url"];
  m_broadcasterId = dataJson["broadcaster_id"];
  m_broadcasterName = dataJson["broadcaster_name"];
  m_creatorId = dataJson["creator_id"];
  m_creatorName = dataJson["creator_name"];
  m_videoId = dataJson["video_id"];
  m_gameId = dataJson["game_id"];
  m_language = dataJson["language"];
  m_title = dataJson["title"];
  m_viewCount = dataJson["view_count"];
  m_createdAt = dataJson["created_at"];
  m_thumbnailUrl = dataJson["thumbnail_url"];
  m_duration = dataJson["duration"];
  if (!dataJson["vod_offset"].is_null())
    m_vodOffset = dataJson["vod_offset"];
  else
    m_vodOffset = -1;
}

json ClipDataType::ToJson()
{
  return {
    {"id", m_id},
    {"url", m_url},
    {"embed_url", m_embedUrl},
    {"broadcaster_id", m_broadcasterId},
    {"broadcaster_name", m_broadcasterName},
    {"creator_id", m_creatorId},
    {"creator_name", m_creatorName},
    {"video_id", m_videoId},
    {"game_id", m_gameId},
    {"language", m_language},
    {"title", m_title},
    {"view_count", m_viewCount},
    {"created_at", m_createdAt},
    {"thumbnail_url", m_thumbnailUrl},
    {"duration", m_duration},
    {"vod_offset", (m_vodOffset == -1) ? (json)nullptr : (json)m_vodOffset}
  };
}

ClipResponseType::ClipResponseType(json respJson)
{
  for (auto& data : respJson["data"])
  {
    m_data.push_back(ClipDataType(data));
  }

  m_pagination = PaginationType(respJson["pagination"]);
}

json ClipResponseType::ToJson()
{
  json j = {
    {"data", json::array()},
    {"pagination", m_pagination.ToJson()}
  };

  for (auto& data : m_data)
  {
    j["data"].push_back(data.ToJson());
  }

  return j;
}