
#ifndef CRUD_USERSERVICE_HPP
#define CRUD_USERSERVICE_HPP

#include "db/UserDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include <iostream>

class UserService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database);
public:

  oatpp::Object<UserDto> createUser(const oatpp::Object<UserDto>& dto);
  oatpp::Object<UserDto> updateUser(const oatpp::Object<UserDto>& dto);
  oatpp::Object<UserDto> getUserById(const oatpp::Int32& id);
  oatpp::Object<UserDto> getUserByTc(const oatpp::UInt64& tc);
  oatpp::Object<PageDto<oatpp::Object<UserDto>>> getUsers(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
  oatpp::Object<StatusDto> deleteUserByUserId(const oatpp::Int32& userId);
  oatpp::Object<PageDto<oatpp::Object<UserDto>>> getAllUsers();

};

#endif //CRUD_USERSERVICE_HPP
