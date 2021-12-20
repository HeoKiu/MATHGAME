
#include <cstring>
#include <string>
#include <sstream>

class MathEquation {
public:
    MathEquation();
    char key_;
    int firstNumber;
    int secondNumber;
    int thirdNumber;
    virtual ~MathEquation();
    const void getEquation();
    void setValue(int first, int second, int third){
        firstNumber = first;
        secondNumber = second;
        thirdNumber = third;
    }
};



