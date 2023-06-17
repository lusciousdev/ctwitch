#ifndef _CLIP_H_
#define _CLIP_H_

#include <vector>
#include <string>

#include "json.hpp"

#include "apiobject.h"
#include "enumerations.h"
#include "pagination.h"

using json = nlohmann::json;

namespace ctwitch
{
  class ClipDataType : ApiObject
  {
  public:
    ClipDataType() {};
    ClipDataType(json dataJson);
    ~ClipDataType() {};

    json ToJson();

    void SetId(std::string id) { m_id = id; }
    std::string GetId() { return m_id; }

    void SetUrl(std::string url) { m_url = url; }
    std::string GetUrl() { return m_url; }

    void SetEmbedUrl(std::string embedUrl) { m_embedUrl = embedUrl; }
    std::string GetEmbedUrl() { return m_embedUrl; }

    void SetBroadcasterId(std::string broadcasterId) { m_broadcasterId = broadcasterId; }
    std::string GetBroadcasterId() { return m_broadcasterId; }

    void SetBroadcasterName(std::string broadcasterName) { m_broadcasterName = broadcasterName; }
    std::string GetBroadcasterName() { return m_broadcasterName; }

    void SetCreatorId(std::string creatorId) { m_creatorId = creatorId; }
    std::string GetCreatorId() { return m_creatorId; }

    void SetCreatorName(std::string creatorName) { m_creatorName = creatorName; }
    std::string GetCreatorName() { return m_creatorName; }

    void SetVideoId(std::string videoId) { m_videoId = videoId; }
    std::string GetVideoId() { return m_videoId; }

    void SetGameId(std::string gameId) { m_gameId = gameId; }
    std::string GetGameId() { return m_gameId; }

    void SetLanguage(std::string language) { m_language = language; }
    std::string GetLanguage() { return m_language; }

    void SetTitle(std::string title) { m_title = title; }
    std::string GetTitle() { return m_title; }

    void SetViewCount(int viewCount) { m_viewCount = viewCount; }
    int GetViewCount() { return m_viewCount; }

    void SetCreatedAt(std::string createdAt) { m_createdAt = createdAt; }
    std::string GetCreatedAt() { return m_createdAt; }

    void SetThumbnailUrl(std::string thumbnailUrl) { m_thumbnailUrl = thumbnailUrl; }
    std::string GetThumbnailUrl() { return m_thumbnailUrl; }

    void SetDuration(float duration) { m_duration = duration; }
    float GetDuration() { return m_duration; }

    void SetVodOffset(int vodOffset) { m_vodOffset = vodOffset; }
    int GetVodOffset() { return m_vodOffset; }

  private:
    std::string m_id;
    std::string m_url;
    std::string m_embedUrl;
    std::string m_broadcasterId;
    std::string m_broadcasterName;
    std::string m_creatorId;
    std::string m_creatorName;
    std::string m_videoId;
    std::string m_gameId;
    std::string m_language;
    std::string m_title;
    int         m_viewCount;
    std::string m_createdAt;
    std::string m_thumbnailUrl;
    float       m_duration;
    int         m_vodOffset;
  };

  class ClipResponseType : ApiObject
  {
  public:
    ClipResponseType() {};
    ClipResponseType(json respJson);
    ~ClipResponseType() {};

    json ToJson();

    std::vector<ClipDataType>& GetData() { return m_data; }

    PaginationType& GetPagination() { return m_pagination; }

  private:
    std::vector<ClipDataType> m_data;
    PaginationType m_pagination;
  };
}

#endif