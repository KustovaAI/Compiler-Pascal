#include "Hash1Table.h"
#include <gtest.h>

TEST(THash1Table, Default_Constructor_No_Throws)
{
	EXPECT_NO_THROW(THash1Table());
}

TEST(THash1Table, Find_Unexisting_Element_Return_Null)
{
	THash1Table t;
	EXPECT_EQ(t.Search("unexist"), nullptr);
}

TEST(THash1Table, Find_Existing_Element_Return)
{
	THash1Table t;
	TNote n("key", "val", "integer");
	t.Insert(n);
	EXPECT_EQ(t.Search("key")->val, n.val);
}

TEST(THash1Table, Inserting_Element_With_Existing_Key)
{
	THash1Table t;
	TNote n("key", "val", "integer");
	t.Insert(n);
	EXPECT_ANY_THROW(t.Insert(n));
}

TEST(THash1Table, Deleting_Existing_Key)
{
	THash1Table t;
	TNote n("key", "val", "integer");
	t.Insert(n);
	EXPECT_NO_THROW(t.Delete("key"));
	EXPECT_EQ(t.Search("key"), nullptr);
}

TEST(THash1Table, Deleting_Unexisting_Key)
{
	THash1Table t;
	TNote n("key", "val", "integer");
	t.Insert(n);
	EXPECT_ANY_THROW(t.Delete("keyy"));
}

