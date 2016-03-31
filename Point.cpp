//
//  Point.cpp
//  PA2
//
//  Created by Abdulrahman Alkaabi on 2/22/16.
//  Copyright © 2016 Abdulrahman Alkaabi. All rights reserved.

#include "Point.h"
#include <cstdlib>
#include<cmath>
#include "Exceptions.h"

using namespace Clustering;

/*
 * Single argument constructor that sets the dimensions of the point
 */
unsigned int Point::__idGen=0;
char POINT_VALUE_DELIM= ',';

Point::Point(unsigned int dimensions) {
    __dim=dimensions;
  
    if (__dim == 0){
        
        throw ZeroDimensionsEx();
        
        
    }
  	 // id generator
    __id=Point::__idGen;
    Point::__idGen++;
    __values = new double [__dim]();
    
}

/**
 * Two argument constructor that sets both the dimensions and
 * the values for each dimension of the point
 **/
Point::Point (unsigned int dimensions, double* values){
    __dim=dimensions;
    if (__dim == 0){
        
        throw ZeroDimensionsEx();
        
        
    }

    

    __values=values;
    Point::__idGen++;
    __values = new double [__dim]();
}

/**
 * Copy constructor, must set all member variables of  to
 * the current Point's member variables.
 */

Point::Point (const Point& diffPoint){
    __dim=diffPoint.getDims();
    // __values=diffPoint.__values;
    __id=diffPoint.__id;
    
    double *tempValues = new double[diffPoint.getDims()];
    for (int i = 0; i < diffPoint.getDims(); i ++)
        tempValues[i] = diffPoint.__values[i];
    __values = tempValues;
    
    
    
}




/**
 * Override the assignment operator
 */

Point& Point::operator=(const Point &otherPoint){
    if (__dim != otherPoint.__dim){
        
        throw DimensionalityMismatchEx(__dim, otherPoint.__dim);
        
    }
    __dim=otherPoint.__dim;
    __values=otherPoint.__values;
    __id=otherPoint.__id;
    
    return *this;
    
}
/**
 * Destructor
 */
Point::~Point(){
    
    
}

/**
 * Calculates the distance between two n-dimensional points
 */
double Point::distanceTo(const Point &otherPoint)const{
    //variable to return
    if (__dim != otherPoint.__dim){
        
        throw DimensionalityMismatchEx(__dim , otherPoint.__dim);
        
        
    }

    double distance=0.0;
    
    //variable for intermediate calculations
    double sum=0.0;
    
    // Pythagorean theroem: distance^2=Sum of i to n (deltaXi^2)
    for(int i =0; i<getDims(); i++){
        double difference=__values[i]-otherPoint.__values[i];
        sum += pow(difference,2.0);
        
    }
    distance = sqrt(sum);
    
    
    return distance;
    
    
}


/**
 * Getter and setter implementations
 */
int Point::getId() const {
    return __id;
}

/**
 * Returns the dimension of the point
 */
unsigned int Point::getDims() const{
    return __dim;
}

/**
 * Sets the value of a particular dimension
 * I.e. myValues[2]=4.3
 */
void Point::setValue(unsigned int position, double value){
    if ( position > getDims()-1||position < 0){
        
        throw OutOfBoundsEx(position, getDims());
        
    }

    
    __values[position] = (double) value;
  
    
}

/**
 * Return the value at the given position
 */
double Point::getValue(unsigned int position) const{

    if ( position > getDims()-1||position<0){
        
        throw OutOfBoundsEx(position, getDims());
        
    }

    
    return __values[position];
    
    
}

/***OPERATORS****/

Point& Point::operator*=(double value){
    for (int i = 0; i< __dim; i++){
        
        __values[i] *= std::floor(value * 100 + 0.005)/100;
        if(abs(__values[i]-(3.14*i))>0.001){
            //     std::cout<<__values[i]<<" "<<3.14*i<<std::endl;
        }
        
        
    }
    
    return *this;
    
}

Point& Point::operator/=(double value){
    for (int i = 0; i< __dim; i++){
        __values[i] /=1000.0*value/1000.0;
        if(abs(__values[i]-(100*i/3.14))>0.001){
            std::cout<<"Issue confirmed"<<std::endl;
        }
        
        
        
    }
    
    return *this;
}

const Point Point::operator*(double value) const{
    for (int i = 0; i< __dim; i++){
        __values[i] *= std::floor(value * 100 + 0.5)/100;
        //__values[i] *= value;
        
    }
    
    
    return *this;
    
}
const Point Point::operator/(double value) const{
    for (int i = 0; i< __dim; i++){
        
        __values[i] /= value;
        
        
        
    }
    
    return *this;
}


double& Point::operator[](unsigned int index){
    
    if ( index > getDims()-1|| index<0){
        
        throw OutOfBoundsEx(index, getDims());
        
    }
    return  __values[index];
    
    
}

/******FRIENDS******/
Point & Clustering::operator +=( Point &p1, const Point &p2 ){
    if (p1.getDims() != p2.getDims()){
        
        throw DimensionalityMismatchEx(p1.getDims(), p2.getDims());
        
        
    }

    for ( int i = 0; i<p1.getDims(); i++){
        double temp = p1.getValue(i);
        temp += p2.getValue(i);
        p1.setValue(i,temp);
        
    }
    
    return p1;
}

Point & Clustering::operator -=( Point &p1, const Point &p2 ){
    if (p1.getDims() != p2.getDims()){
        
        throw DimensionalityMismatchEx(p1.getDims(), p2.getDims());
        
        
    }

    for ( int i = 0; i<p1.getDims(); i++){
        double temp = p1.getValue(i);
        temp -= p2.getValue(i);
        p1.setValue(i,temp);
        
    }
    
    return p1;
    
    
}

const Point Clustering::operator+(const Point& p1, const Point& p2){
    if (p1.getDims() != p2.getDims()){
        
        throw DimensionalityMismatchEx(p1.getDims(), p2.getDims());
        
        
    }

    Point pt(p1);
    for ( int i = 0; i<p1.getDims(); i++){
        double temp = p1.getValue(i);
        temp += p2.getValue(i);
        pt.setValue(i,temp);
    }
    return pt;
    
    
}
const Point Clustering::operator-(const Point& p1, const Point& p2){
    if (p1.getDims() != p2.getDims()){
        
        throw DimensionalityMismatchEx(p1.getDims(), p2.getDims());
        
        
    }

    Point pt(p1);
    for ( int i = 0; i<p1.getDims(); i++){
        double temp = p1.getValue(i);
        temp -= p2.getValue(i);
        pt.setValue(i,temp);
    }
    return pt;
    
    
}

bool Clustering::operator==(const Point& p1, const Point& p2){
        bool bo = false;
 if (p1.__id == p2.__id) {
        if (p1.getDims() == p2.getDims()) {
            bo = true;
            for (int i = 0; i<p1.getDims(); i++) {
                
                if (p1.__values[i] != p2.__values[i]) {
                    bo = false;
                    break;
               }
            }
            
        }
     
        else {
            
            throw DimensionalityMismatchEx(p1.getDims(), p2.getDims());
            
        }
    }
    return bo;
}




bool Clustering::operator!=(const Point& p1, const Point& p2){
    
    
    return !(p1==p2);
    
    
}

bool Clustering:: operator<(const Point& p1, const Point& p2){
    
    if (p1.getDims() != p2.getDims()){
        
        throw DimensionalityMismatchEx(p1.getDims(), p2.getDims());

        
    }
    
    int i =0;
    while (i<p1.getDims() && (p1.getValue(i)==p2.getValue(i))){
        i++;
    }
    if(i<p1.getDims()){
        return p1.getValue(i)<p2.getValue(i);
    }
    
    //if at end of point(s)
    return false;
    
}
bool Clustering::operator>(const Point& p1, const Point& p2){
    if (p1.getDims() != p2.getDims()){
        
        throw DimensionalityMismatchEx(p1.getDims(), p2.getDims());
        
        
    }

    int i =0;
    while (i<p1.getDims() && (p1.getValue(i)==p2.getValue(i))){
        i++;
    }
    if(i<p1.getDims()){
        return p1.getValue(i)>p2.getValue(i);
    }
    
    
    
    return false;
    
}
bool Clustering::operator<=(const Point& p1, const Point& p2){
    if (p1.getDims() != p2.getDims()){
        
        throw DimensionalityMismatchEx(p1.getDims(), p2.getDims());
        
        
    }

    bool bo = true;
    bool boEq= true;
    for ( int i = 0; i<p1.getDims(); i++){
        double temp = p1.getValue(i);
        if(temp > p2.getValue(i)){
            bo = false;
        }
        else if(temp == p2.getValue(i)){
            boEq = false;
        }
        
    }
    
    
    return (bo||boEq);
    
    
    
}
bool Clustering::operator>=(const Point& p1, const Point& p2){
    if (p1.getDims() != p2.getDims()){
        
        throw DimensionalityMismatchEx(p1.getDims(), p2.getDims());
        
        
    }

    bool bo = true;
    bool boEq= true;
    for ( int i = 0; i<p1.getDims(); i++){
        double temp = p1.getValue(i);
        if(temp < p2.getValue(i)){
            bo = false;
        }
        else if(temp == p2.getValue(i)){
            boEq = false;
        }
        
    }
    
    
    return (bo||boEq);
    
    
    
}


std::ostream& Clustering::operator<<(std::ostream& os, const Point& pt){
    
       if (pt.getDims() != 0) {
        for (int i = 0; i < pt.getDims() - 1; i++) {
            os << pt.__values[i];
            os << ", ";
        }
        os << pt.__values[pt.getDims() - 1];
    }
    else {
        os<< 0;
    }
    return os;
}
std::istream& Clustering::operator>>(std::istream& is, Point& pt){
    const char POINT_VALUE_DELIM = ',';
    int i = 0;
   
    while( i < pt.getDims()&& is.peek() != EOF ){
        std::string line;
        std::getline(is, line, POINT_VALUE_DELIM);
        pt.setValue(i, atof(line.c_str()));
        i++;
    }
    if ((is.peek() == EOF && i<pt.getDims())||(is.peek() != EOF)) {
        
        throw DimensionalityMismatchEx(i, pt.getDims());
        
    }
    return is;
}

