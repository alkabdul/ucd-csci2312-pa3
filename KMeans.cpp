//
//  KMeans.cpp
//  PA#3
//
//  Created by Abdulrahman Alkaabi on 3/28/16.
//  Copyright © 2016 Abdulrahman Alkaabi. All rights reserved.
//
#include <fstream>
#include "Exceptions.h"
#include "KMeans.h"

#include <stdio.h>
using namespace Clustering;
KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter){
    
    if (k == 0){
        
        throw ZeroClustersEx();
        
        }
    if (dim == 0) {
        throw ZeroDimensionsEx();
    }
    __dimensionality = dim;
    __k = k;
    __iFileName = filename;
    __maxIter = maxIter;
    
    //Teasting the validity of the file name
    
    std::ifstream file (filename);
    if (!(file.good())){
        throw DataFileOpenEx(filename);
        
    }
    //populating cluster's array
    __clusters = new Cluster*[k];
    int i = 0;
    while (i < k) {
        __clusters[i] = new Cluster(dim);
        __initCentroids[i] = new Point(dim);
        i++;
    }
    file >> (*__clusters)[0];
    file.close();
    
    __clusters[0] -> pickCentroids(k,__initCentroids);
    i =0;
    while (i < k) {
        
        __clusters[i] -> centroid.set(*__initCentroids[i]);
        i++;
    }
    
}


KMeans::~KMeans(){
    
    
}

unsigned int KMeans::getMaxIter(){
    
    
    return 0;
}

unsigned int KMeans::getNumIters(){
    
    
    return 0;
}
unsigned int KMeans::getNumNonemptyClusters(){
    
    
    return 0;
}
unsigned int KMeans::getNumMovesLastIter(){
    
    
    return 0;
}
Cluster& KMeans::operator[] (unsigned int u){
    int i = 0;
    
    return *__clusters[i];
}


const Cluster& KMeans::operator[] (unsigned int u) const{
    int i = 0;
    
    return *__clusters[i];
    
    
}
std::ostream& Clustering::operator<<(std::ostream &os, const KMeans &kmeans){
    
    
    return os;
}

void KMeans:: run(){
    
    
}








