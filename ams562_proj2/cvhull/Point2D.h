#ifndef __POINT2D_H
#define __POINT2D_H

#include <iostream>
#include <cmath>

namespace ams562 {

class Point2D {
public:
    //
    // Constructors
    Point2D(){
        x_ = 0;
        y_ = 0; 
    }                      
    // implementation needed
    Point2D(const Point2D &p){
        x_ = p.x_;
        y_ = p.y_;
    }      
    // implementation needed
    Point2D(int x, int y){
        x_ = x;
        y_ = y;
    }          
    // implementation needed

    //
    // Methods for accessing
    // implementation needed

    int getx(){
        return this -> x_;
    }

    int cogetx() const {
        return this -> x_;
    }

    int gety(){
        return this -> y_;
    }

    int cogety() const {
        return this -> y_;
    }

    //
    // orientation
    // implementation needed
    int orientation(const Point2D &a, const Point2D &b) const{
        int res = (b.cogetx() - a.cogetx()) * (this -> y_ -  a.cogety()) 
            - (this -> x_ - a.cogetx()) * (b.cogety() - a.cogety());
        return res;
    }

    //
    // backend swapping
    // implementation needed
    void swap(Point2D &other){
        Point2D temp(*this);
        *this =  other;
        other =  temp;        
    }

    //
    // Operator =
    // implementation needed
    Point2D & operator=(const Point2D &p){
        this -> x_ = p.x_;
        this -> y_ = p.y_;
        return *this; 
    }

private:
    int x_, y_;
    friend std ::ostream & operator<<(std::ostream &, const Point2D &);
    friend std ::istream & operator>>(std::istream &, Point2D &);
};

//
// ostream::operator<<
inline std::ostream & operator<<(std::ostream &out, const Point2D &p) {
    out << p.x_ << ' ' << p.y_ << ' ';
    return out;
}

//
// istream::operator>>
// implementation needed
inline std::istream & operator>>(std::istream &in, Point2D &p){
    in >> p.x_ >> p.y_;
    return in;
}

//
// distance square
// implementation needed
inline int dist_sq(const Point2D &p1, const Point2D &p2){
    
    int dis = pow(p1.cogetx() - p2.cogetx(), 2) + pow(p1.cogety() - p2.cogety(),2);

    return dis;
} 

}

#endif
