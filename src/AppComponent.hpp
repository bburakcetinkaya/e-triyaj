
#ifndef AppComponent_hpp
#define AppComponent_hpp

#include "SwaggerComponent.hpp"
#include "DatabaseComponent.hpp"

#include "ErrorHandler.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/utils/ConversionUtils.hpp"

#include "oatpp/core/macro/component.hpp"

oatpp::String getIpFromConfigFile()
{        
    
        oatpp::String ip =oatpp::base::StrBuffer::loadFromFile("config/ipconfig.txt"); //read data from file object and put it into string.
        return ip;
}
oatpp::UInt16 getPortFromConfigFile()
{
    bool ok;
    oatpp::String portStr = oatpp::base::StrBuffer::loadFromFile("config/portconfig.txt"); 
    oatpp::Int32 port = oatpp::utils::conversion::strToUInt32(portStr, ok);
    if (ok)
    {
        return static_cast<oatpp::UInt16>(port);
    }
    else
        return 8000;
}

//const char ip[] = "192.168.1.22";
//const int port = 80;
/**
 *  Class which creates and holds Application components and registers components in oatpp::base::Environment
 *  Order of components initialization is from top to bottom
 */
class AppComponent {
public:
  
    
  /**
   *  Swagger component
   */
  SwaggerComponent swaggerComponent;

  /**
   * Database component
   */
  DatabaseComponent databaseComponent;

  /**
   * Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    objectMapper->getDeserializer()->getConfig()->allowUnknownFields = false;
    return objectMapper;
  }());
  
  /**
   *  Create ConnectionProvider component which listens on the port
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
      
      //std::cout << "Server started at: 192.168.1.29" << std::endl;
      oatpp::String ip = getIpFromConfigFile();
      oatpp::UInt16 port = getPortFromConfigFile();
      //OATPP_LOGD("ip", " %s...", ip.toString()->c_str());
      //OATPP_LOGD("port", " %s...", port.toString()->c_str());
      
      return oatpp::network::tcp::server::ConnectionProvider::createShared({ ip,port, oatpp::network::Address::IP_4});

  }());
  
  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
    return oatpp::web::server::HttpRouter::createShared();
  }());
  
  /**
   *  Create ConnectionHandler component which uses Router component to route requests
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {

    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper); // get ObjectMapper component

    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
    connectionHandler->setErrorHandler(std::make_shared<ErrorHandler>(objectMapper));
    return connectionHandler;

  }());

};

#endif /* AppComponent_hpp */
