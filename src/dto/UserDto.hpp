#ifndef UserDto_hpp
#define UserDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include <iostream>
#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(Role, v_int32,
    VALUE(PATIENT, 0, "ROLE_PATIENT"),
    VALUE(DOKTOR, 1, "ROLE_DOKTOR")
);
ENUM(Gender, v_int32,
    VALUE(MALE, 0, "MALE"),
    VALUE(FEMALE, 1, "FEMALE")

);

class UserDto : public oatpp::DTO {
  
  DTO_INIT(UserDto, DTO)

  DTO_FIELD(Int32, id);
 // DTO_FIELD(Int32, UserId);
  DTO_FIELD(String, name, "name");
  DTO_FIELD(String, surname, "surname");
  DTO_FIELD(UInt8, age, "age");
  DTO_FIELD(Enum<Gender>::AsString, gender, "gender");
  DTO_FIELD(UInt64, tc, "tc");
  DTO_FIELD(Float32, sp02, "sp02");
  DTO_FIELD(Float32, heartRate, "heartRate");
  DTO_FIELD(Float32, temperature, "temperature");
  DTO_FIELD(Float32, systolicBP, "systolicBP");
  DTO_FIELD(Float32, diastolicBP, "diastolicBP");
  DTO_FIELD(Enum<Role>::AsString, role, "role");
  DTO_FIELD(String, date, "date");
  DTO_FIELD(String, time, "time");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* UserDto_hpp */
