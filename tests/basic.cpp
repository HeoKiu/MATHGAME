
#include <gtest/gtest.h>
#include "../include/MathEquation.h"
#include "../include/EvaluateString.h"
#include "../src/MathEquation.cpp"


TEST(GetPointString, string) {
    EvaluateString temp;
    int x = 100;
    EXPECT_EQ(temp.GetPointString(x), "100");
}
TEST(GetPointString_second, string) {
    EvaluateString temp;
    int x = 100000;
    EXPECT_EQ(temp.GetPointString(x), "100000");
}
TEST(GetStringEquationTest_1, Equation) {
    MathEquation equation;
    equation.setValue(1,2,3);
    EvaluateString temp;
    EXPECT_EQ(temp.GetStringEquation(equation),"1 + 2 = 3");
}
TEST(GetStringEquationTest_2, Equation) {
    MathEquation equation;
    equation.setValue(8,9,17);
    EvaluateString temp;
    EXPECT_EQ(temp.GetStringEquation(equation),"8 + 9 = 17");
}

TEST(GetStringEquationTest_3, Equation) {
    MathEquation equation;
    equation.setValue(9,9,18);
    EvaluateString temp;
    EXPECT_EQ(temp.GetStringEquation(equation),"9 + 9 = 18");
}

TEST(KeyPressed_2, Equation) {
    MathEquation equation;
    EvaluateString temp;
    equation.key_ = 'N';
    EXPECT_EQ(temp.KeyPressed(equation),false);
}
TEST(Time, Equation) {
    MathEquation equation;
    equation.key_='Y';
    EvaluateString temp;
    EXPECT_EQ(temp.TimeDiscounting(equation), temp.KeyPressed(equation));
}
