#include <gtest.h>
#include "Text.h"

// CONSTRUCTOR
TEST(TText, Default_Constructor_No_Nhrows)
{
	EXPECT_NO_THROW(TText());
}

// READING
TEST(TText, Read_Correct_File_No_Throws)
{
	TText txt;
	EXPECT_NO_THROW(txt.Enter_line_to_list("Paskal.txt", 30));
}

TEST(TText, Read_Const_Or_Var_After_Begin_Throws)
{
	TText txt;
	EXPECT_ANY_THROW(txt.Enter_line_to_list("CVafterBegin.txt", 8));
}

TEST(TText, Read_Word_After_Const_Throws)
{
	TText txt;
	EXPECT_ANY_THROW(txt.Enter_line_to_list("WordAfterConst.txt", 8));
}

TEST(TText, Read_Error_Const_Throws)
{
	TText txt;
	EXPECT_ANY_THROW(txt.Enter_line_to_list("ErrorConst.txt", 9));
}

TEST(TText, Read_Error_Begin_Throws)
{
	TText txt;
	EXPECT_ANY_THROW(txt.Enter_line_to_list("ErrorBegin.txt", 10));
}

TEST(TText, Read_Error_If_Else_Throws)
{
	TText txt;
	EXPECT_ANY_THROW(txt.Enter_line_to_list("ErrorIfElse.txt", 10));
}

// CHESK END OF LINE

TEST(TText, Check_End_Of_Line_Correct)
{
	TText txt;
	string str("Write();");
	EXPECT_NO_THROW(txt.Check_End_Line(str));
}

TEST(TText, Check_End_Of_Line_Uncorrect_Throws)
{
	TText txt;
	string str("Write()");
	EXPECT_ANY_THROW(txt.Check_End_Line(str));
}

// DELETING SPACES


TEST(TText, Correct_Delete_Spaces)
{
	TText txt;
	string str("Program Example;");
	string str2("ProgramExample;");
	EXPECT_EQ(str2, txt.Delete_space_before_and_after_keywords(str));
}

// READ BEFORE SYMBOLE
TEST(TText, Correct_Read_Before_Symbole)
{
	TText txt;
	string str("Program Example;");
	string str2("rogram");
	int j = 1;
	EXPECT_EQ(str2, txt.Read_before_symbol(str, j, 'E'));
}