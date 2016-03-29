//
//  Exceptions.cpp
//  PA#3
//
//  Created by Abdulrahman Alkaabi on 3/28/16.
//  Copyright © 2016 Abdulrahman Alkaabi. All rights reserved.
//
#include "Exceptions.h"
#include <stdio.h>

using namespace Clustering;

OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r){
    
    __current = c;
    __rhs = r;
    
    
}

unsigned int OutOfBoundsEx::getCurrent()const{
    
    return __current;
    
}

int OutOfBoundsEx::getRhs()const{
    
    return __rhs;
    
}
std::string OutOfBoundsEx::getName()const{
    
    
    return __name;
}
std::ostream& Clustering::operator<<(std::ostream &os, const OutOfBoundsEx &ex){
    
    os << ex << std::endl;
    return os;
    
}
DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r)
{
    __current = c;
    __rhs = r;
    
}


unsigned int DimensionalityMismatchEx::getCurrent()const
{
    
    return __current;
}
unsigned int DimensionalityMismatchEx::getRhs()const{
    
    return __rhs;
    
}

std::string DimensionalityMismatchEx::getName()const{
    
    
    return __name;
}


std::ostream& Clustering::operator<<(std::ostream &os, const DimensionalityMismatchEx &ex){
    os << ex << std::endl;
    return os;
    
}
ZeroClustersEx::ZeroClustersEx(){
    
}

std::string ZeroClustersEx::getName()const{
    return __name;
}
std::ostream& Clustering::operator<<(std::ostream &os, const ZeroClustersEx &ex){
    
    os << ex << std::endl;
    return os;
}
DataFileOpenEx::DataFileOpenEx(std::string filename){
    __filename= filename;
    
}

std::string DataFileOpenEx::getFilename()const{
    
    return __filename;
}
std::string DataFileOpenEx::getName()const{
    
    return __name;
}
std::ostream& Clustering::operator<<(std::ostream &os, const DataFileOpenEx &ex){
    
    os << ex << std::endl;

    return os;
}
ZeroDimensionsEx::ZeroDimensionsEx(){
    
    
}

std::string ZeroDimensionsEx::getName()const{
    
    return __name;
}
std::ostream& Clustering::operator<<(std::ostream &os, const ZeroDimensionsEx &ex){
    
    os << ex << std::endl;

    return os;
}

EmptyClusterEx::EmptyClusterEx(){
    
}
std::string EmptyClusterEx::getName()const{
    
    return __name;
}
std::ostream& Clustering::operator<<(std::ostream &os, const EmptyClusterEx &ex){
    os << ex << std::endl;

    return os;
}










