cmake_minimum_required(VERSION 3.5)

project(httpsvr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../IoC)
include_directories(../exceptions)
include_directories(../interface)
include_directories(../commands)

add_executable(httpsvr main.cpp
    Endpoint.h Endpoint.cpp
    IHttpRequestHandler.h
    GetHandler.h GetHandler.cpp
    HttpRequestHandler.h HttpRequestHandler.cpp
    NotAllowedHandler.h NotAllowedHandler.cpp
    ../IoC/IoC.cpp ../IoC/IoC.h
    ../IoC/IocNewScopeCommand.cpp ../IoC/IocNewScopeCommand.h
    ../IoC/IocRegisterCommand.cpp ../IoC/IocRegisterCommand.h
    ../IoC/IocSetScopeAbsoluteCommand.cpp ../IoC/IocSetScopeAbsoluteCommand.h
    ../IoC/IocSetScopeRelativeCommand.cpp ../IoC/IocSetScopeRelativeCommand.h
    ../IoC/IResolverCollection.h ../IoC/IResolverContainer.h
    ../IoC/IScope.h ../IoC/IScopeChanger.h
    ../IoC/ResolverCollection.cpp ../IoC/ResolverCollection.h
    ../IoC/ResolverContainer.h
    ../IoC/Scope.cpp ../IoC/Scope.h
    ../IoC/ScopeChangerAdapter.cpp ../IoC/ScopeChangerAdapter.h
    ../IoC/ScopeContainer.cpp ../IoC/ScopeContainer.h
    ../exceptions/RuntimeError.cpp ../exceptions/RuntimeError.h
    ../commands/FallbackCommand.cpp ../commands/FallbackCommand.h
    ../exceptions/InvalidArgument.cpp ../exceptions/InvalidArgument.h
    HttpRequestInterpretCommand.h HttpRequestInterpretCommand.cpp
    HttpRequest.h HttpRequest.cpp
    ../interface/IOutputCommandStream.h
    DirectCommandExecutor.h DirectCommandExecutor.cpp
    BadRequestHandler.h BadRequestHandler.cpp
    IRequestAcceptingObject.h
    HttpRequestAcceptingObject.h HttpRequestAcceptingObject.cpp
    DeleteHttpRequestCommand.h DeleteHttpRequestCommand.cpp
    ../commands/MacroCommand.cpp ../commands/MacroCommand.h
    ../exceptions/CommandException.cpp ../exceptions/CommandException.h
    HttpBadRequestCommand.h HttpBadRequestCommand.cpp
    HttpRedirectCommand.h HttpRedirectCommand.cpp
    HttpNotAllowedCommand.h HttpNotAllowedCommand.cpp)

# include(GNUInstallDirs)
# install(TARGETS httpsvr
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
