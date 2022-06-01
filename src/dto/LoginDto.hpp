#ifndef LoginDto_hpp
#define LoginDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include <iostream>
#include OATPP_CODEGEN_BEGIN(DTO)
ENUM(Role, v_int32,
    VALUE(PATIENT, 0, "ROLE_PATIENT"),
    VALUE(DOKTOR,  1, "ROLE_DOCTOR"),
    VALUE(ADMIN,   2, "ROLE_ADMIN")
);
class LoginDto : public oatpp::DTO {

    DTO_INIT(LoginDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(UInt64, tc, "tc");
    DTO_FIELD(String, name, "name");
    DTO_FIELD(String, surname, "surname");
    DTO_FIELD(Enum<Role>::AsString, role, "role");
    DTO_FIELD(String, password, "password");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* UserDto_hpp */
