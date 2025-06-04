#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <FallbackCommand.h>
#include <ICommand_mock.h>
#include <IException_mock.h>
#include <vector>

using namespace std;
using ::testing::Throw;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::_;
using ::testing::InSequence;

TEST(FallbackCommand, StopOnSuccessCommand)
{
    shared_ptr<ICommandMock> command1 = make_shared<ICommandMock>();
    shared_ptr<ICommandMock> command2 = make_shared<ICommandMock>();
    vector<ICommandPtr> commands = { command1, command2 };
    FallbackCommand cmd(commands);

    EXPECT_CALL(*command1, Execute());
    
    EXPECT_NO_THROW(cmd.Execute());
}

TEST(FallbackCommand, SkipFailedCommands)
{
    shared_ptr<ICommandMock> command1 = make_shared<ICommandMock>();
    shared_ptr<ICommandMock> command2 = make_shared<ICommandMock>();
    vector<ICommandPtr> commands = { command1, command2 };
    FallbackCommand cmd(commands);

    EXPECT_CALL(*command1, Execute()).WillOnce(Throw(new IExceptionMock));
    EXPECT_CALL(*command2, Execute());
    
    EXPECT_NO_THROW(cmd.Execute());
}

TEST(FallbackCommand, ExceptionOnFailedAllCommands)
{
    shared_ptr<ICommandMock> command1 = make_shared<ICommandMock>();
    shared_ptr<ICommandMock> command2 = make_shared<ICommandMock>();
    vector<ICommandPtr> commands = { command1, command2 };
    FallbackCommand cmd(commands);

    EXPECT_CALL(*command1, Execute()).WillOnce(Throw(new IExceptionMock));
    EXPECT_CALL(*command2, Execute()).WillOnce(Throw(new IExceptionMock));

    try
    {
        cmd.Execute();
        FAIL();
    }
    catch(IException *exception)
    {
        delete exception;
        SUCCEED();
    }
}