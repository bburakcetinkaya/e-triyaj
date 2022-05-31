#ifndef LoginDto_hpp
#define LoginDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include <iostream>
#include OATPP_CODEGEN_BEGIN(DTO)

class LoginDto : public oatpp::DTO {

    DTO_INIT(LoginDto, DTO);

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, name, "name");
    DTO_FIELD(String, password, "password");


};

#include OATPP_CODEGEN_END(DTO)

#endif /* UserDto_hpp */
