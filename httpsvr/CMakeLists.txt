cmake_minimum_required(VERSION 3.5)

project(httpsvr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../IoC)
include_directories(../exceptions)
include_directories(../interface)
include_directories(../commands)
include_directories(../endpoint)

add_executable(httpsvr main.cpp
    ../endpoint/Endpoint.h ../endpoint/Endpoint.cpp
    ../endpoint/IMessageQueue.h
    ../endpoint/DirectCommandExecutor.h ../endpoint/DirectCommandExecutor.cpp

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
    ../exceptions/InvalidArgument.cpp ../exceptions/InvalidArgument.h
    ../exceptions/CommandException.cpp ../exceptions/CommandException.h

    ../commands/FallbackCommand.cpp ../commands/FallbackCommand.h
    ../commands/PrintJsonObjectCommand.h ../commands/PrintJsonObjectCommand.cpp
    ../commands/MacroCommand.cpp ../commands/MacroCommand.h

    ../interface/IOutputCommandStream.h
    ../interface/IJsonObject.h

    IRequestHandler.h
    GetHandler.h GetHandler.cpp
    RequestHandler.h RequestHandler.cpp
    NotAllowedHandler.h NotAllowedHandler.cpp
    BadRequestHandler.h BadRequestHandler.cpp
    RequestInterpretCommand.h RequestInterpretCommand.cpp
    HttpRequest.h HttpRequest.cpp
    DeleteHttpRequestCommand.h DeleteHttpRequestCommand.cpp
    SendBadRequestCommand.h SendBadRequestCommand.cpp
    SendRedirectCommand.h SendRedirectCommand.cpp
    SendNotAllowedCommand.h SendNotAllowedCommand.cpp
    HttpRequestJsonObject.h HttpRequestJsonObject.cpp
    IRedirector.h
    MonolithRedirector.h MonolithRedirector.cpp
    IRules.h
    RedirectRules.h RedirectRules.cpp
    ICondition.h
    CheckConditionCommand.h CheckConditionCommand.cpp
    BeforeCondition.h BeforeCondition.cpp
    HttpRequestAcceptor.h HttpRequestAcceptor.cpp)

# include(GNUInstallDirs)
# install(TARGETS httpsvr
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
