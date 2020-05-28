#include "Hierarchy_List.h"
#include <gtest.h>
TEST(THierarchy_List, Default_Constructor_No_Throws)
{
	EXPECT_NO_THROW(THierarchy_List<char>());
}

TEST(THierarchy_List, New_Created_List_Is_Empty)
{
	THierarchy_List<char> l;
	EXPECT_EQ(true ,l.Is_Empty());
}

TEST(THierarchy_List, Correct_Insert_First)
{
	THierarchy_List<string> l;
	l.InsertFirst(string("first"));
	l.ReSetCur();
	EXPECT_EQ(string("first"), l.Get_Current_Line());
}

TEST(THierarchy_List, Correct_Hierarchy_Navigate)
{
	THierarchy_List<string> l;
	l.InsertFirst(string("first"));
	l.Insert_Down_Line(string("down1"));
	l.Insert_Down_Line(string("down2"));
	l.ReSetCur();
	l.GoDown();
	l.GoDown();
	EXPECT_EQ(string("down2"), l.Get_Current_Line());
	l.Insert_Next_Line(string("next1"));
	l.Insert_Next_Line(string("next2"));
	l.ReSetCur();
	l.GoDown();
	l.GoDown();
	l.Go(); l.Go();
	EXPECT_EQ(string("next2"), l.Get_Current_Line());
}

TEST(THierarchy_List, Correct_Hierarchy_Navigate2)
{
	THierarchy_List<string> l;
	l.InsertFirst(string("title"));
		l.Insert_Down_Line(string("down2"));
			l.Insert_Down_Line(string("down21"));
			l.Insert_Next_Line(string("next21"));
			l.Insert_Next_Line(string("next22"));
	l.ReSetCur();
		l.Insert_Down_Line(string("down1"));
			l.Insert_Down_Line(string("down11"));
			l.Insert_Next_Line(string("next11"));
			l.Insert_Next_Line(string("next12"));
	l.ReSetCur();
	l.GoDown();
	EXPECT_EQ(string("down1"), l.Get_Current_Line());
}

TEST(THierarchy_List, Correct_Hierarchy_Navigate3)
{
	THierarchy_List<string> l;
	l.InsertFirst(string("title"));
		l.Insert_Down_Line(string("d1"));
		l.Insert_Next_Line(string("d2"));
		l.Insert_Next_Line(string("d3"));
			l.Insert_Down_Line(string("dd1"));
			l.Insert_Next_Line(string("dd2"));
	l.ReSetCur();
	l.GoDown(); l.Go(); l.Go(); l.GoDown();
	EXPECT_EQ(string("dd1"), l.Get_Current_Line());
}

TEST(THierarchy_List, GoParent_Throws_When_Empty)
{
	THierarchy_List<string> l;
	EXPECT_ANY_THROW(l.Go_Parent());
}

TEST(THierarchy_List, GoParent_Stay_The_Same_When_Already_On_The_Top)
{
	THierarchy_List<string> l;
	l.InsertFirst(string("first"));
	l.ReSetCur();
	l.Go_Parent();
	l.Go_Parent();
	EXPECT_EQ(string("first"), l.Get_Current_Line());
}

TEST(THierarchy_List, GoDown_Throws_When_No_Way_Down)
{
	THierarchy_List<string> l;
	l.InsertFirst(string("first"));
	l.ReSetCur();
	EXPECT_ANY_THROW(l.GoDown());
}

TEST(THierarchy_List, Get_Current_Line_Correct)
{
	THierarchy_List<string> l;
	l.InsertFirst(string("first"));
	l.InsertFirst(string("last"));
	l.ReSetCur();
	EXPECT_EQ(string("last"), l.Get_Current_Line());
}
