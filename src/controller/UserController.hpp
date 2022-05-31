
#ifndef UserController_hpp
#define UserController_hpp

#include "service/UserService.hpp"
#include "oatpp\codegen\api_controller\cors_define.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include <iostream>
//#include "oatpp/web/server/handler/Interceptor.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class UserController : public oatpp::web::server::api::ApiController 

{
public:
  UserController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:
  UserService m_userService; // Create user service.
public:
    
  static std::shared_ptr<UserController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){

    return std::make_shared<UserController>(objectMapper);
  }
  //ADD_CORS(createUser)
 
  
  //----------------------------------------------------------------------------------------------------
 //  ADD_CORS(createUser, "192.168.1.27", "POST,GET, OPTIONS", "X-PWNT", "1337");
    //----------------------------------------------------------------------------------------------------
 
  
  //ADD_CORS(putUser)
  ADD_CORS(newUser,
      "http://localhost:4200",
      "GET, ,PUT, POST, OPTIONS, DELETE",
      "DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range",
      "1728000");


  ENDPOINT_INFO(newUser) {
      info->summary = "new user";

      info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
      info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

  }
  ENDPOINT("POST", "users/newUser", newUser,
      BODY_DTO(Object<LoginDto>, loginDto))
  {
      return createDtoResponse(Status::CODE_200, m_userService.newUser(loginDto));
  }
  //-------------
  ADD_CORS(createUser,
      "http://localhost:4200",
      "GET, ,PUT, POST, OPTIONS, DELETE",
      "DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range",
      "1728000");

  ENDPOINT_INFO(createUser) {
      info->summary = "Create new User";

      info->addConsumes<Object<UserDto>>("application/json");

      info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
      info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "users/createUser", createUser,
      BODY_DTO(Object<UserDto>, userDto))
  {

      return createDtoResponse(Status::CODE_200, m_userService.createUser(userDto));
  }
  ADD_CORS(putUser,
      "http://localhost:4200",
      "GET, ,PUT, POST, OPTIONS, DELETE",
      "DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range",
      "1728000");

  ENDPOINT_INFO(putUser) {
    info->summary = "Update User by userId";

    info->addConsumes<Object<UserDto>>("application/json");

    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("PUT", "users/updateUserById/{userId}", putUser,
           PATH(Int32, userId),
           BODY_DTO(Object<UserDto>, userDto))
  {
    userDto->id = userId;
    return createDtoResponse(Status::CODE_200, m_userService.updateUser(userDto));
  }
    
  //-------------------------------------------------------------------------------------------------------------------
  //ADD_CORS(getUserById)

  ADD_CORS(getUserById,
      "http://localhost:4200",
      "GET, ,PUT, POST, OPTIONS, DELETE",
      "DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range",
      "1728000");


  ENDPOINT_INFO(getUserById) {
  info->summary = "Get one User by userId";

  info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
  info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
  info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

  info->pathParams["userId"].description = "User Idendifier";

     }
  ENDPOINT("GET", "users/getById/{userId}", getUserById,
      PATH(Int32, userId))
  {
      return createDtoResponse(Status::CODE_200, m_userService.getUserById(userId));
  }
  //-------------------------------------------------------------------------------------------------------
  //get by tc
  ADD_CORS(getUserRecordsByTc,
      "http://localhost:4200",
      "GET, ,PUT, POST, OPTIONS, DELETE",
      "DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range",
      "1728000");


  ENDPOINT_INFO(getUserRecordsByTc) {
      info->summary = "Get User Records by user TC";

      info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
      info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

      info->pathParams["userTC"].description = "User TC number";

  }
  ENDPOINT("GET", "users/getUserRecordsByTc/{userTC}", getUserRecordsByTc,
      PATH(UInt64, userTC))
  {
      return createDtoResponse(Status::CODE_200, m_userService.getUserRecordsByTc(userTC));
  }
  //-------------------------------------------------------------------------------------------------------------------
  //ADD_CORS(getUsers)

  ADD_CORS(getUsers,
      "http://localhost:4200",
      "GET, ,PUT, POST, OPTIONS, DELETE",
      "DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range",
      "1728000");


  ENDPOINT_INFO(getUsers) {
    info->summary = "get all stored users";

    info->addResponse<oatpp::Object<UsersPageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "users/offset/{offset}/limit/{limit}", getUsers,
           PATH(UInt32, offset),
           PATH(UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_userService.getUsers(offset, limit));
  }
  //----------------------------------------------------------------------------------------------------
  ADD_CORS(getAllUsers,
      "http://localhost:4200",
      "GET, ,PUT, POST, OPTIONS, DELETE",
      "DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range",
      "1728000");


  ENDPOINT_INFO(getAllUsers) {
      info->summary = "get all stored users";

      info->addResponse<oatpp::Object<UsersPageDto>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "users/getAll", getAllUsers
     )
  {
      return createDtoResponse(Status::CODE_200, m_userService.getAllUsers());
  }
  //----------------------------------------------------------------------------------------------------
  //ADD_CORS(deleteUser)

  ADD_CORS(deleteUser,
      "http://localhost:4200",
      "GET, ,PUT, POST, OPTIONS, DELETE",
      "DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range",
      "1728000");



  ENDPOINT_INFO(deleteUser) {
    info->summary = "Delete User by userId";

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("DELETE", "users/deleteUserById/{userId}", deleteUser,
           PATH(Int32, userId))
  {
    return createDtoResponse(Status::CODE_200, m_userService.deleteUserByUserId(userId));
  }
  ADD_CORS(getEntriesByDateInterval,
      "http://localhost:4200",
      "GET, ,PUT, POST, OPTIONS, DELETE",
      "DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range",
      "1728000");



  ENDPOINT_INFO(getEntriesByDateInterval) {
      info->summary = "get entries by date interval";

      info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

      info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("GET", "/users/startDate/{startDate}/endDate/{endDate}", getEntriesByDateInterval,
      PATH(String, startDate),
      PATH(String, endDate))
  {
      return createDtoResponse(Status::CODE_200, m_userService.getEntriesByDateInterval(startDate,endDate));
  }
  ADD_CORS(getEntriesByDateIntervalAndTc,
      "http://localhost:4200",
      "GET, ,PUT, POST, OPTIONS, DELETE",
      "DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range",
      "1728000");



  ENDPOINT_INFO(getEntriesByDateIntervalAndTc) {
      info->summary = "get entries by date interval and tc";

      info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

      info->pathParams["tc"].description = "tc number";
      info->pathParams["startDate"].description = "start date";
      info->pathParams["endDate"].description = "end date";
  }
  ENDPOINT("GET", "users/tc/{tc}/startDate/{startDate}/endDate/{endDate}", getEntriesByDateIntervalAndTc,
      PATH(UInt64, tc),
      PATH(String, startDate),
      PATH(String, endDate))
  {
      return createDtoResponse(Status::CODE_200, m_userService.getEntriesByDateIntervalAndTc(tc ,startDate, endDate));
  }

  ADD_CORS(requestLogin,
      "http://localhost:4200",
      "GET, ,PUT, POST, OPTIONS, DELETE",
      "DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range",
      "1728000");


  ENDPOINT_INFO(requestLogin) {
      info->summary = "request login";

      info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
      info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

      info->pathParams["name"].description = "name";
      info->pathParams["password"].description = "password";

  }
  ENDPOINT("GET", "users/requestLogin/name/{name}/password/{password}", requestLogin,
      PATH(String, name),
      PATH(String, password))
  {
      return createDtoResponse(Status::CODE_200, m_userService.requestLogin(name,password));
  }
  //------------------

};/////users/tc/{tc}/startDate/{startDate}/endDate/{endDate}requestLogin

#include OATPP_CODEGEN_BEGIN(ApiController)

#endif 
