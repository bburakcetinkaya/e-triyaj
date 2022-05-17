
#include "UserService.hpp"
#include <iostream>
oatpp::Object<UserDto> UserService::createUser(const oatpp::Object<UserDto>& dto) 
{

  auto dbResult = m_database->createUser(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto userId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

  return getUserById(userId);

}

oatpp::Object<UserDto> UserService::updateUser(const oatpp::Object<UserDto>& dto) 
{

  auto dbResult = m_database->updateUser(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  return getUserById(dto->id);

}

//--------------------------------------------------------------------------------------------------------------------
oatpp::Object<UserDto> UserService::getUserById(const oatpp::Int32& id)
{

    auto dbResult = m_database->getUserById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();
   
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];

}



//--------------------------------------------------------------------------------------------------------------------
oatpp::Object<PageDto<oatpp::Object<UserDto>>> UserService::getUserRecordsByTc(const oatpp::UInt64& tc)
{

    auto dbResult = m_database->getUserRecordsByTc(tc);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();

    auto page = PageDto<oatpp::Object<UserDto>>::createShared();
    page->count = items->size();
    page->items = items;

    return page;
   //return result[0];

}
oatpp::Object<PageDto<oatpp::Object<UserDto>>> UserService::getEntriesByDateIntervalAndTc(const oatpp::UInt64 tc, const oatpp::String startDate, const oatpp::String endDate)
{
    auto dbResult = m_database->getEntriesByDateIntervalAndTc(tc,startDate,endDate);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();

    auto page = PageDto<oatpp::Object<UserDto>>::createShared();
    page->count = items->size();
    page->items = items;

    return page;
}

//-----------------------------------------------------------------------------------------------------------------------
oatpp::Object<PageDto<oatpp::Object<UserDto>>> UserService::getUsers(const oatpp::UInt32& offset, const oatpp::UInt32& limit) 
{
    
  oatpp::UInt32 countToFetch = limit;
  /*
  if(limit > 10) 
  {
    countToFetch = 10;
  }
  */
  auto dbResult = m_database->getUsers(offset, countToFetch);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();

  auto page = PageDto<oatpp::Object<UserDto>>::createShared();
  page->offset = offset;
  page->limit = countToFetch;
  page->count = items->size();
  page->items = items;

  return page;

}

oatpp::Object<StatusDto> UserService::deleteUserByUserId(const oatpp::Int32& userId)
{
  auto dbResult = m_database->deleteUserByUserId(userId);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "User was successfully deleted";
  return status;
}
oatpp::Object<PageDto<oatpp::Object<UserDto>>> UserService::getAllUsers()
{
  
  auto dbResult = m_database->getAllUsers();
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();

  auto page = PageDto<oatpp::Object<UserDto>>::createShared();
  page->count = items->size();
  page->items = items;

  return page;

}
oatpp::Object<PageDto<oatpp::Object<UserDto>>> UserService::getEntriesByDateInterval(const oatpp::String startDate, const oatpp::String endDate)
{
    auto dbResult = m_database->getEntriesByDateInterval(startDate,endDate);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();

    auto page = PageDto<oatpp::Object<UserDto>>::createShared();
    page->count = items->size();
    page->items = items;

    return page;
}