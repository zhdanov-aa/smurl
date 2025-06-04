cmake_minimum_required(VERSION 3.5)

project(redirector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../IoC)
include_directories(../exceptions)
include_directories(../interface)
include_directories(../commands)
include_directories(../endpoint)

add_executable(redirector main.cpp

    ../endpoint/Endpoint.h ../endpoint/Endpoint.cpp
    ../endpoint/IMessageQueue.h
    ../endpoint/DirectCommandExecutor.cpp ../endpoint/DirectCommandExecutor.h

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
    ../commands/MacroCommand.cpp ../commands/MacroCommand.h
    ../commands/PrintJsonObjectCommand.cpp ../commands/PrintJsonObjectCommand.h

    ../interface/IException.h
    ../interface/ICommand.h
    ../interface/IJsonObject.h

    InitializeCommand.cpp InitializeCommand.h
    UdpRequestAcceptor.h UdpRequestAcceptor.cpp
    UdpRequestData.h UdpRequestData.cpp
    DeleteRequestCommand.h DeleteRequestCommand.cpp
    RequestJsonObject.h RequestJsonObject.cpp
    IRules.h
    RedirectRules.cpp RedirectRules.h
    CheckConditionCommand.cpp CheckConditionCommand.h
    ICondition.h
    PluginCondition.h PluginCondition.cpp
    FindRequestRulesCommand.h FindRequestRulesCommand.cpp
    SendResponseCommand.h SendResponseCommand.cpp
    IRulesObject.h
    RequestRulesObject.h RequestRulesObject.cpp
    IResponseSender.h
    UdpResponseSender.h UdpResponseSender.cpp
    JsonFile.h JsonFile.cpp
)

add_subdirectory(plugins)

