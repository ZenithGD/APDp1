#include "mat4.hpp"

Mat4 Mat4::operator+(const Mat4 that) const {
    Mat4 result;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++){
            result[i][j] = (*this)[i][j] + that[i][j];
        }
    }

    return result;
}

Mat4 Mat4::operator-(const Mat4 that) const {
    Mat4 result;
    
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            result[i][j] = (*this)[i][j] - that[i][j];
        }
    }

    return result;
}

Mat4 Mat4::operator*(const Mat4 that) const{
    Mat4 result;
    for ( int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = 0.0;
            for (int k = 0; k < 4; k++) {
                result[i][j] += (*this)[i][k] * that[k][j]; 
            }
        }
    }

    return result;
}

ostream& operator<<(ostream& os, const Mat4& mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            os << mat[i][j] << ", ";
        }
        os << mat[i][3] << endl;
    }
    return os;
}