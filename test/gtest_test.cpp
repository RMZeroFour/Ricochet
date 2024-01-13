#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;

// Verify googletest is setup correctly
TEST(GoogleTest, BasicAssertions)
{
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}

// Verify googlemock is setup correctly
TEST(GoogleTest, BasicMocking)
{
    struct Mock
    {
        MOCK_METHOD(int, Add, (int, int), (const));
        MOCK_METHOD(int, Sub, (int, int), (const));
    } m{};
    
    EXPECT_CALL(m, Add(1, 2))
        .WillOnce(Return(3));
    EXPECT_CALL(m, Sub(2, 2))
        .WillRepeatedly(Return(0));

    EXPECT_EQ(m.Add(1, 2), 3);
    EXPECT_EQ(m.Sub(2, 2), 0);
    EXPECT_EQ(m.Sub(2, 2), 0);
}