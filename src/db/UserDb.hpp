
#ifndef CRUD_USERDB_HPP
#define CRUD_USERDB_HPP

#include "dto/UserDto.hpp"
#include "dto/LoginDto.hpp"
#include "oatpp-sqlite/orm.hpp"
#include <iostream>
//#include <chrono>
//#include <sstream>
//#include <iomanip>

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen
//std::string getTime()
//{   
//    std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
//    std::string format = "UTC: %Y-%m-%d %H:%M:%S";
//    std::time_t tt = std::chrono::system_clock::to_time_t(time);
//    std::tm tm = *std::gmtime(&tt); 
//    std::stringstream ss;
//    ss << std::put_time(&tm, format.c_str());
//    return ss.str();
//}
/**
 * UserDb client definitions.
 */
class UserDb : public oatpp::orm::DbClient {
public:

  UserDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
    {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 , DATABASE_MIGRATIONS "/e-triyaj-db-init.sql");

    migration.migrate(); 

    auto version = executor->getSchemaVersion();
    OATPP_LOGD("UserDb", "Migration - OK. Version=%d.", version);

  }
  //  migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/e-triyajDB.sql");
  //  // TODO - Add more migrations here.
  //  migration.migrate(); // <-- run migrations. This guy will throw on error.



  //}
  QUERY(newUser,
        "INSERT INTO LoginTable"
        "(name,password)"
        "VALUES (:user.name, :user.password);",
        PARAM(oatpp::Object<LoginDto>,user))
  QUERY(createUser,
        "INSERT INTO AppUser"
        "(name,         surname,        age,        gender,     tc,         sp02,       heartRate,       temperature,       systolicBP,         diastolicBP,    role,   date,  time) VALUES "
        "(:user.name, :user.surname, :user.age, :user.gender, :user.tc, :user.sp02, :user.heartRate, :user.temperature, :user.systolicBP, :user.diastolicBP, :user.role, :user.date ,:user.time);",
        PARAM(oatpp::Object<UserDto>, user))
      /*  DTO_FIELD(double, sp02, "sp02");
  DTO_FIELD(double, heartRate, "heartRate");
  DTO_FIELD(double, temperature, "temperature");
  DTO_FIELD(double, systolicBP, "systolicBP");
  DTO_FIELD(double, diastolicBP, "diastolicBP");*/
  QUERY(updateUser,
        "UPDATE AppUser "
        "SET "
        " name=:user.name, "
        " surname=:user.surname, "
        " gender:user.gender,"
        " age:user.age,"
        " tc=:user.tc, "
        " sp02=:user.sp02, "
        " heartRate=:user.heartRate, "
        " temperature=:user.temperature, "
        " systolicBP=:user.systolicBP, "
        " diastolicBP=:user.diastolicBP, "
        " role=:user.role, "
        " date =:user.date,"
        " time =:user.time,"

        
        "WHERE "
        " id=:user.id;",
        PARAM(oatpp::Object<UserDto>, user))

    
 //----------------------------------------------------------------------------------------------
      QUERY(getUserById,
          "SELECT * FROM AppUser WHERE id=:id;",
          PARAM(oatpp::Int32, id))
      QUERY(requestLoginResponse,
          "SELECT * FROM LoginTable WHERE id=:id;",
          PARAM(oatpp::Int32,id))
          
      QUERY(getUserRecordsByTc,
          "SELECT * FROM AppUser WHERE tc=:tc;",
          PARAM(oatpp::UInt64, tc))
 //----------------------------------------------------------------------------------------------

  QUERY(getUsers,
        "SELECT * FROM AppUser LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deleteUserByUserId,
      "DELETE FROM AppUser WHERE tc=:tc;",
        PARAM(oatpp::Int32, id))

  QUERY(getAllUsers,
        "SELECT * FROM AppUser")

  QUERY(getEntriesByDateInterval,
      "SELECT * FROM AppUser WHERE :startDate <= date AND :endDate >= date ;",
      PARAM(oatpp::String, startDate),
      PARAM(oatpp::String, endDate))

  QUERY(getEntriesByDateIntervalAndTc,
      "SELECT * FROM AppUser WHERE tc=:tc AND :startDate <= date AND :endDate >= date ;",
      PARAM(oatpp::UInt64, tc),
      PARAM(oatpp::String, startDate),
      PARAM(oatpp::String, endDate))
  QUERY(requestLogin,
      "SELECT * FROM LoginTable WHERE name=:name AND password=:password;",
      PARAM(oatpp::String, name),
      PARAM(oatpp::String, password))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //CRUD_USERDB_HPP
