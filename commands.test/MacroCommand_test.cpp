#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MacroCommand.h>
#include <ICommand_mock.h>
#include <IException_mock.h>
#include <CommandException.h>
#include <vector>

using namespace std;
using ::testing::Throw;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::_;
using ::testing::InSequence;

TEST(MacroCommand, ExecuteCommands)
{
    shared_ptr<ICommandMock> cmd1 = make_shared<ICommandMock>();
    shared_ptr<ICommandMock> cmd2 = make_shared<ICommandMock>();
    shared_ptr<ICommandMock> cmd3 = make_shared<ICommandMock>();
    vector<ICommandPtr> commands = { cmd1, cmd2, cmd3 };
    MacroCommand cmd(commands);

    {
        InSequence s;

        EXPECT_CALL(*cmd1, Execute());
        EXPECT_CALL(*cmd2, Execute());
        EXPECT_CALL(*cmd3, Execute());
    }
    
    EXPECT_NO_THROW(cmd.Execute());
}

TEST(MacroCommand, StopOnException)
{
    shared_ptr<ICommandMock> cmd1 = make_shared<ICommandMock>();
    shared_ptr<ICommandMock> cmd2 = make_shared<ICommandMock>();
    vector<ICommandPtr> commands = { cmd1, cmd2 };
    MacroCommand cmd(commands);

    {
        InSequence s;

        EXPECT_CALL(*cmd1, Execute());
        EXPECT_CALL(*cmd2, Execute()).WillOnce(Throw(new IExceptionMock));
    }
    
    try
    {
        cmd.Execute();
        FAIL();
    }
    catch(IException *exception)
    {
        EXPECT_NE(dynamic_cast<CommandException*>(exception), nullptr);
        delete exception;
    }
}
