#include "Postfix.h"
#include <gtest.h>

TEST(TPostfix, Constr_No_Throws)
{
	EXPECT_NO_THROW(TPostfix("a+b"));
	EXPECT_NO_THROW(TPostfix());
}

TEST(TPostfix, To_Postfix1)
{
	TPostfix a("a+b");
	THash1Table t;
	t.ReadFile("Keywords.txt");
	a.ToPostfix(&t);
	EXPECT_EQ(a.GetPostfix(), "a b +");
}

TEST(TPostfix, To_Postfix2)
{
	TPostfix a("(a+b)*b-a");
	THash1Table t;
	t.ReadFile("Keywords.txt");
	a.ToPostfix(&t);
	EXPECT_EQ(a.GetPostfix(), "a b + b * a -");
}

TEST(TPostfix, To_Postfix3)
{
	TPostfix a("a+b*b-a");
	THash1Table t;
	t.ReadFile("Keywords.txt");
	a.ToPostfix(&t);
	EXPECT_EQ(a.GetPostfix(), "a b b * + a -");
}

TEST(TPostfix, To_Postfix_Throws_When_Unknown_Token)
{
	TPostfix a("a+b*b-a+c");
	THash1Table t;
	t.ReadFile("Keywords.txt");
	EXPECT_ANY_THROW(a.ToPostfix(&t););
}

TEST(TPostfix, To_Postfix_Throws_When_Uncorect_Brackets1)
{
	TPostfix a("a+b+(a-b))");
	THash1Table t;
	t.ReadFile("Keywords.txt");
	EXPECT_ANY_THROW(a.ToPostfix(&t););
}

TEST(TPostfix, To_Postfix_Throws_When_Uncorect_Brackets2)
{
	TPostfix a(")a+b(+a-b");
	THash1Table t;
	t.ReadFile("Keywords.txt");
	EXPECT_ANY_THROW(a.ToPostfix(&t););
}

TEST(TPostfix, Correct_Calculate)
{
	TPostfix a("a+b*b-a");
	THash1Table t;
	t.ReadFile("Keywords.txt");
	a.ToPostfix(&t);
	EXPECT_EQ(a.Calculate(&t, "double"), 9.0);
}

TEST(TPostfix, Correct_Calculate2)
{
	TPostfix a("a+b+(a-b)");
	THash1Table t;
	t.ReadFile("Keywords.txt");
	a.ToPostfix(&t);
	EXPECT_EQ(a.Calculate(&t, "double"), 6.0);
}