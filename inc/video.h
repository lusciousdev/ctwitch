#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <vector>
#include <string>

#include "json.hpp"

#include "enumerations.h"
#include "pagination.h"

using json = nlohmann::json;

class MutedSegmentType
{
public:
  MutedSegmentType() {};

  MutedSegmentType(json mutedSegmentJson);

  ~MutedSegmentType() {};

  void SetDuration(int duration) { m_duration = duration; }
  int GetDuration() { return m_duration; }

  void SetOffset(int offset) { m_offset = offset; }
  int GetOffset() { return m_offset; }

private:
  int m_duration;
  int m_offset;
};

class VideoDataType
{
public:
  VideoDataType() {};

  VideoDataType(json videoDataJson);

  ~VideoDataType() {};

  void SetId(std::string id) { m_id = id; }
  const std::string& GetId() { return m_id; }

  void SetStreamId(std::string streamId) { m_streamId = streamId; }
  const std::string& GetStreamId() { return m_streamId; }

  void SetUserId(std::string userId) { m_userId = userId; }
  const std::string& GetUserId() { return m_userId; }

  void SetUserLogin(std::string userLogin) { m_userLogin = userLogin; }
  const std::string& GetUserLogin() { return m_userLogin; }

  void SetUserName(std::string userName) { m_userName = userName; }
  const std::string& GetUserName() { return m_userName; }

  void SetTitle(std::string title) { m_title = title; }
  const std::string& GetTitle() { return m_title; }

  void SetDescription(std::string description) { m_description = description; }
  const std::string& GetDescription() { return m_description; }

  void SetCreatedAt(std::string createdAt) { m_createdAt = createdAt; }
  const std::string& GetCreatedAt() { return m_createdAt; }

  void SetPublishedAt(std::string publishedAt) { m_publishedAt = publishedAt; }
  const std::string& GetPublishedAt() { return m_publishedAt; }

  void SetUrl(std::string url) { m_url = url; }
  const std::string& GetUrl() { return m_url; }

  void SetThumbnailUrl(std::string thumbnailUrl) { m_thumbnailUrl = thumbnailUrl; }
  const std::string& GetThumbnailUrl() { return m_thumbnailUrl; }

  void SetViewable(std::string viewable) { m_viewable = viewable; }
  const std::string& GetViewable() { return m_viewable; }

  void SetViewCount(int viewCount) { m_viewCount = viewCount; }
  const int& GetViewCount() { return m_viewCount; }

  void SetLanguage(std::string language) { m_language = language; }
  const std::string& GetLanguage() { return m_language; }

  void SetType(std::string typeString) { m_type = VideoTypeEnum(typeString); }
  void SetType(VideoTypeEnum type) { m_type = type; }
  const VideoTypeEnum& GetType() { return m_type; }
  std::string GetTypeString() { return (std::string)m_type; }

  void SetDuration(std::string duration) { m_duration = duration; }
  const std::string& GetDuration() { return m_duration; }

  std::vector<MutedSegmentType>& GetMutedSegments() { return m_mutedSegments; }
 
private:
  std::string   m_id;
  std::string   m_streamId;
  std::string   m_userId;
  std::string   m_userLogin;
  std::string   m_userName;
  std::string   m_title;
  std::string   m_description;
  std::string   m_createdAt;
  std::string   m_publishedAt;
  std::string   m_url;
  std::string   m_thumbnailUrl;
  std::string   m_viewable;
  int           m_viewCount;
  std::string   m_language;
  VideoTypeEnum m_type;
  std::string   m_duration;

  std::vector<MutedSegmentType> m_mutedSegments;
};

class VideoResponseType
{
public:
  VideoResponseType() {};

  VideoResponseType(json videoResponseJson);

  ~VideoResponseType() {};

  std::vector<VideoDataType>& GetData() { return m_data; }
  PaginationType& GetPagination() { return m_pagination; }

private:
  std::vector<VideoDataType> m_data;
  PaginationType m_pagination;
};

#endif