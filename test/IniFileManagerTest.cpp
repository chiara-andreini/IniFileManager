//
// Created by Chiara on 29/08/16.
//

#include "gtest/gtest.h"
#include "../IniFileManager.h"

//Test fixture:
class IniFileManagerTest : public ::testing::Test {
public:
    IniFileManagerTest() {


        /*          IMPORTANT WARNING:
         *
         * Ahead of everything else,
         * make sure you write the right path for the file test.txt!
         *
         */

        EXPECT_NO_THROW(test = new IniFileManager("TYPE/YOUR/DIRECTORY/FOR/test.txt", open));
    }

    virtual ~IniFileManagerTest() {
        delete test;
    }

    IniFileManager * test;
};

TEST_F(IniFileManagerTest, FileIsParsed) {

    EXPECT_EQ(test->readAComment("FirstSection", 0), ";Comment 1");

    EXPECT_EQ(test->read("FirstSection", "key1"), "value1");
    EXPECT_EQ(test->read("FirstSection", "key2"), "value2");

    EXPECT_EQ(test->readAComment("SecondSection", 0), ";Comment 1");
    EXPECT_EQ(test->readAComment("SecondSection", 1), ";Comment 2");

    EXPECT_EQ(test->read("SecondSection", "key1"), "value1");
    EXPECT_EQ(test->read("SecondSection", "key2"), "value2");

}

TEST_F(IniFileManagerTest, ValueIsEdited) {

    test->editValue("SecondSection", "key1", "differentvalue1");

    EXPECT_EQ(test->read("SecondSection", "key1"), "differentvalue1");

}

TEST_F(IniFileManagerTest, ValueIsStillEdited) {

    EXPECT_EQ(test->read("SecondSection", "key1"), "differentvalue1");

    test->editValue("SecondSection", "key1", "value1");
}


TEST_F(IniFileManagerTest, LineIsDeleted) {

    test->deleteLine("FirstSection", "key2");

    EXPECT_EQ(test->read("FirstSection", "key2"), "");
}

TEST_F(IniFileManagerTest, LineIsStillDeleted) {

    EXPECT_EQ(test->read("FirstSection", "key2"), "");

}

TEST_F(IniFileManagerTest, LineIsAdded) {

    test->addLine("FirstSection", "key2", "value2");
    test->addLine("FirstSection", "key2", "othervalue");

    EXPECT_EQ(test->read("SecondSection", "key2"), "value2");

}

TEST_F(IniFileManagerTest, LineIsStillThere) {

    EXPECT_EQ(test->read("SecondSection", "key2"), "value2");


}

TEST_F(IniFileManagerTest, SectionIsDeleted) {

    test->deleteSection("SecondSection");

    EXPECT_EQ(test->readAComment("SecondSection", 0), "");
    EXPECT_EQ(test->readAComment("SecondSection", 1), "");
    EXPECT_EQ(test->read("SecondSection", "key1"), "");
    EXPECT_EQ(test->read("SecondSection", "key2"), "");
}

TEST_F(IniFileManagerTest, SectionIsStillDeleted) {

    EXPECT_EQ(test->read("SecondSection", "key1"), "");
    EXPECT_EQ(test->read("SecondSection", "key2"), "");
    EXPECT_EQ(test->readAComment("SecondSection", 0), "");
    EXPECT_EQ(test->readAComment("SecondSection", 1), "");

}

TEST_F(IniFileManagerTest, CommentsandNewSectionAreAdded) {

    test->addSection("SecondSection");

    test->addComment("SecondSection", ";Comment 1");
    test->addComment("SecondSection", ";Comment 2");

    test->addLine("SecondSection", "key1", "value1");
    test->addLine("SecondSection", "key2", "value2");

    EXPECT_EQ(test->readAComment("SecondSection", 0), ";Comment 1");
    EXPECT_EQ(test->readAComment("SecondSection", 1), ";Comment 2");
    EXPECT_EQ(test->read("SecondSection", "key1"), "value1");
    EXPECT_EQ(test->read("SecondSection", "key2"), "value2");

}


TEST_F(IniFileManagerTest, CreatedSectionIsStillThere) {
    EXPECT_EQ(test->readAComment("SecondSection", 0), ";Comment 1");
    EXPECT_EQ(test->readAComment("SecondSection", 1), ";Comment 2");
    EXPECT_EQ(test->read("SecondSection", "key1"), "value1");
    EXPECT_EQ(test->read("SecondSection", "key2"), "value2");
}


TEST_F(IniFileManagerTest, SectionIsCleared) {

    test->clearSection("FirstSection");
    EXPECT_EQ(test->read("FirstSection", "key1"), "");
    EXPECT_EQ(test->read("FirstSection", "key2"), "");

}

TEST_F(IniFileManagerTest, SectionIsStillEmpty) {

    EXPECT_EQ(test->read("FirstSection", "key1"), "");
    EXPECT_EQ(test->read("FirstSection", "key2"), "");
    test->addLine("FirstSection", "key1", "value1");
    test->addLine("FirstSection", "key2", "value2");

}
