#pragma once

#include <iostream>

using namespace std;

class Mat4 {
public:

    Mat4() : _mat{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} {};

    Mat4 operator+(const Mat4 that) const;
    
    Mat4 operator-(const Mat4 that) const;

    Mat4 operator*(const Mat4 that) const;

    float det() const;

    decltype(auto) operator[](unsigned int i) { return _mat[i]; }
    decltype(auto) operator[](unsigned int i) const { return _mat[i]; }

    friend ostream& operator<<(ostream& os, const Mat4& mat);
private: 
    float _mat[4][4];
};

ostream& operator<<(ostream& os, const Mat4& mat);

