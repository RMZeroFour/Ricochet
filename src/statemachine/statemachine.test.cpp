#include "statemachine/statebase.h"
#include "statemachine/statemachine.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::InSequence;

struct Shared
{
	int number;
};

class MockState : public StateBase
{
public:
	MockState(Shared& shared) : _shared{ shared } { }
	~MockState() { Destructor(); }
public:
	MOCK_METHOD(void, OnEnter, (), (override));
	MOCK_METHOD(Transition, Process, (), (override));
	MOCK_METHOD(void, OnExit, (), (override));
	MOCK_METHOD(void, Destructor, (), ());
protected:
	Shared& _shared;
};

TEST(StateMachine, StateLifecycle)
{
	Shared data{};
	auto state{ std::make_unique<MockState>(data) };

	InSequence seq;
	EXPECT_CALL(*state.get(), OnEnter());
	EXPECT_CALL(*state.get(), Process())
		.WillOnce(Return(Quit()));
	EXPECT_CALL(*state.get(), OnExit());
	EXPECT_CALL(*state.get(), Destructor());

	StateMachine fsm{ std::move(state) };
	fsm.ProcessCurrent();

	EXPECT_TRUE(fsm.HasFinished());
}

TEST(StateMachine, PushPopStates)
{
	Shared data{};
	auto first{ std::make_unique<MockState>(data) };
	auto second{ std::make_unique<MockState>(data) };

	InSequence seq;
	EXPECT_CALL(*first.get(), OnEnter());
	EXPECT_CALL(*first.get(), Process())
		.WillOnce([&second]() { return PushTransition{ std::move(second) }; });
	EXPECT_CALL(*first.get(), OnExit());
	
	EXPECT_CALL(*second.get(), OnEnter());
	EXPECT_CALL(*second.get(), Process())
		.WillOnce(Return(Pop()));
	EXPECT_CALL(*second.get(), OnExit());
	EXPECT_CALL(*second.get(), Destructor());

	EXPECT_CALL(*first.get(), OnEnter());
	EXPECT_CALL(*first.get(), Process())
		.WillOnce(Return(Quit()));
	EXPECT_CALL(*first.get(), OnExit());
	EXPECT_CALL(*first.get(), Destructor());

	StateMachine fsm{ std::move(first) };
	while (!fsm.HasFinished())
		fsm.ProcessCurrent();

	EXPECT_TRUE(fsm.HasFinished());
}

TEST(StateMachine, SwitchStates)
{
	Shared data{};
	auto first{ std::make_unique<MockState>(data) };
	auto second{ std::make_unique<MockState>(data) };

	InSequence seq;
	EXPECT_CALL(*first.get(), OnEnter());
	EXPECT_CALL(*first.get(), Process())
		.WillOnce([&second]() { return SwitchTransition{ std::move(second) }; });
	EXPECT_CALL(*first.get(), OnExit());
	EXPECT_CALL(*first.get(), Destructor());
	
	EXPECT_CALL(*second.get(), OnEnter());
	EXPECT_CALL(*second.get(), Process())
		.WillOnce(Return(Quit()));
	EXPECT_CALL(*second.get(), OnExit());
	EXPECT_CALL(*second.get(), Destructor());

	StateMachine fsm{ std::move(first) };
	while (!fsm.HasFinished())
		fsm.ProcessCurrent();

	EXPECT_TRUE(fsm.HasFinished());
}