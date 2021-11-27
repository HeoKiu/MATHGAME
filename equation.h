//
// Created by duc on 27.11.2021.
//

#ifndef GAMESDL_EQUATION_H
#define GAMESDL_EQUATION_H

#include <bits/stdc++.h>
#include <cstring>

class equation
{
public:
    equation();
    char key;
    int num1;
    int num2;
    int num3;
    virtual ~equation();
    void getEquation(int level);

protected:

private:
};


#endif//GAMESDL_EQUATION_H
