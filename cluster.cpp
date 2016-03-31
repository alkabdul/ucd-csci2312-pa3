#include <stdio.h>
#include <algorithm>
#include "Exceptions.h"
#include <sstream>

#include "Cluster.h"
using namespace Clustering;
unsigned int Cluster::__idGenerator=0;
char POINT_CLUSTER_ID_DELIM= ':';


//void Cluster::add_begin()

/**
 * Default constructor
 */
//Cluster::Cluster(){
//    __size = 0;
//    __points = nullptr;
//    
//    
//}

Cluster::Centroid::Centroid(unsigned int d, const Cluster &c): __p(d), __c(c)

{
    
    __dimensions = d;
    __valid = false;
    
}

//Cluster::Centroid::Centroid(const Centroid &cent) {
//    
//    
//}
const Point Cluster::Centroid::get() const{
    
    
    return __p;
}

void Cluster::Centroid::set(const Point &p){
    
    setValid(true);
    __p = p;
    
}

bool Cluster::Centroid::isValid() const{
    
    return __valid;
}


void Cluster::Centroid::setValid(bool valid){
    __valid = valid;
    
}

void Cluster::Centroid::compute(){
    LNodePtr current = __c.__points;
    if (current == nullptr){
        
        toInfinity();
    }
    else{
        double sum = 0;
        double numPts = 0;
        int currIndex = 0;
        while (current != nullptr) {
            for (int i = 0; i<current->point.getDims(); i++) {
                sum += current->point[i];
                
                numPts++;
                
            }
       
            
            double average = sum/numPts;
            
            __p.setValue(currIndex, average);
            current = current->next;
            currIndex++;
            sum = 0;
            
            
        }
        setValid(true);


    }
    
}
bool Cluster::Centroid::equal(const Point& p) const{
    
    return __p==p;
  
    
}

void Cluster::Centroid::toInfinity(){
    
    //std::numeric_limits<double>::max().
    for (int i =0; i< __p.getDims(); i++) {
        __p[i] = std::numeric_limits<double>::max();
    
    
    }

    
}



Cluster::Cluster(unsigned int d): centroid(d,*this)
{
    if (d == 0){
        
        throw ZeroDimensionsEx();
    }
    __size = 0;
    __dimensionality = d;
    __id = __idGenerator;
    __points = nullptr;
    __idGenerator++;
    
}





//constructor LNode
Clustering::LNode::LNode(const Point &p, LNodePtr n):
next (n),
point (p){};


/**
 * Copy constructor, must set all member variables of  to
 * the current Point's member variables.
 */

Cluster::Cluster(const Cluster& diffCluster):centroid(diffCluster.__dimensionality,diffCluster){
   
    __size=diffCluster.__size;
      __cpy(diffCluster.__points);
    __id = diffCluster.__id;
    __dimensionality = diffCluster.__dimensionality;
    
    
}


/**
 * Override the assignment operator
 */

Cluster& Cluster::operator=(const Cluster &otherCluster){
    
    if (otherCluster.__dimensionality != __dimensionality){
        
        
        throw DimensionalityMismatchEx(__dimensionality, otherCluster.__dimensionality);
    }

    __size=otherCluster.__size;
    __points=otherCluster.__points;
    __id = otherCluster.__id;
    
    return *this;
    
}

/**
 * Destructor
 */
Cluster::~Cluster(){
//    LNodePtr current = __points;
//    LNodePtr next = __points;
//    if (current == nullptr){
//        
//        return;
//    }
//    else{
//        while (current->next != nullptr) {
//            next = current->next;
//            
//            delete current;
//            current = next;
//        }
//        delete current;
//        __points = nullptr;
//    }
//    
}


unsigned int Cluster::getSize()const {
    
    
    return __size;
}

unsigned int Cluster::getDimensionality()const{
    
    
    return __dimensionality;
}

unsigned int Cluster::getId()const{
    
    return __id;
}


bool Clustering::operator==(const Cluster& c1, const Cluster& c2){
    bool eq =true;
    
    
    if (c1.getDimensionality() != c2.getDimensionality()) {
        throw DimensionalityMismatchEx(c1.getDimensionality(), c2.getDimensionality());
        
        
    }
   
    
    if(c1.getSize() != c2.getSize())
    {
        eq = false;
    }
    else {
        for (int i = 0; i<c1.getSize(); i++) {
            
            if (c1[i] != c2[i])
            {
                
                eq = false;
                
            }
            
            
        }
        
    }
    
    return eq;
    
}

bool Clustering::operator!=(const Cluster& c1, const Cluster& c2){
    
    
    return !(c1 == c2);
    
}

//returns true if the point is found in the linked list
bool Cluster::__in(const Point &p) const{
    if (p.getDims() != __dimensionality)
    {
        
        throw DimensionalityMismatchEx(__dimensionality, p.getDims());
        
    }

    
    bool isFound=false;
    
    LNodePtr temp = __points;
    
    //check to ensure the head node is set
    if(temp != nullptr){

        //iterate through from front of the list to back
        while(temp != nullptr){
            //check to see if the point member of tempPt point equals
            //the target point 'p'
            Point tempPt= temp->point;
            if(tempPt==p)
                isFound=true;
            temp = temp->next;
        }
    }
    return isFound;
    
}


void Cluster::__cpy(LNodePtr pts){
    
    __points = pts;
    
}

void Cluster::add(const Point& p1){
    
  
//     if ( contains(p1) ==  true ){
//     
//     return;
//     
//     }
//     
//     
//     LNodePtr newNode = new LNode (p1, nullptr);
//     
//     LNodePtr current=__points;
//     
//    // check to ensure the head of the linked list is not null
//     if ( current != nullptr)
//     {
//     int counter =0;
//     LNodePtr prev ;
//    // traverse through the linked list until a point is greater than or equal to p1.
//     Point temp = current->point;
//     std::cout<<current->point<<std::endl;
//       std::cout<<"input>head"<<std::endl;
//     bool tempBool = p1>temp;
//     std::cout<<tempBool<<std::endl;
//     while (current!= nullptr ){
//     temp=current->point;
//       std::cout<<"current->point"<<std::endl;
//     std::cout<<current->point<<std::endl;
//     
//      std::cout<<"input>body"<<std::endl;
//        bool tempBoolB = p1>temp;
//     std::cout<<tempBoolB<<std::endl;
//     if(p1>temp){
//      std::cout<<"My PT"<<std::endl;
//      std::cout<<p1<<std::endl;
//     prev=current;
//     current =current->next;
//     
//           std::cout<<"temp"<<temp<<std::endl;
//     counter++;
//       std::cout<<"after counter++"<<std::endl;
//     
//     }
//     else{
//             std::cout<<"Before break"<<std::endl;
//     break;}
//     }
//       std::cout<<"Before nullptr"<<std::endl;
//     newNode->next=current;
//     //if head
//     if (counter ==0){
//     std::cout<<"Entering before head"<<std::endl;
//     __points=newNode;
//     
//     }
// //    if body or tail
//     else{
//        std::cout<<"Entering before tail"<<std::endl;
//     prev->next=newNode;
//     }
//    // adding the newNode to the linked list
//   //  head------>secondNode------->.....------>lastNode------->newNode------->null
//     
//     
//     }
//     
//     
//  //   block executed when the linked list is empty
//     else {
//     
//        std::cout<<std::endl<<"empty ll"<<std::endl;
//  //   Set the head of the linked list to the current node
//     __points = newNode;
//  //   Ensure the head points to nothing
//     __points->next=nullptr;
//     
//     }
//     
//   //   increment size
//     ++__size;
//     
    
    
    if (__dimensionality != p1.getDims()){
        
        throw DimensionalityMismatchEx(__dimensionality, p1.getDims());
        
    }


    if( !(__in(p1))){


    Point p(p1);
    LNodePtr newP = new LNode(p, NULL);
    LNodePtr prev = __points;
    LNodePtr next = __points;

    if (__points == nullptr) {
        __points = newP;
        __size++;
        return;
    }
    
    else if (__points->next == nullptr) {
        if (p1 < __points->point) {
            __points = newP;
            newP->next = prev;
            __size++;
        }
        else {
            __points->next = newP;
            __size++;
        }
    }
    else {
        next = next->next;
        if (p1 < prev->point) {
            __points = newP;
            newP->next = prev;
            __size++;
            return;
        }
        while (next != NULL) {
            if (p1 < next->point) {
                prev->next = newP;
                newP->next = next;
                __size++;
                return;
            }
            next = next->next;
            prev = prev->next;
        }
        prev->next = newP;
        __size++;
    }
}
    
    
}



const Point& Cluster ::remove(const Point& p1){
   
    if ( p1.getDims() != __dimensionality)
    {
        throw DimensionalityMismatchEx(__dimensionality, p1.getDims());
        
    }

    
    //check to see if the point in the linked list
    if( !(__in(p1))){
        return p1;
    }

    
    //executes if p1 is in the linked list
    LNodePtr current = __points;
    //check if the head is what should be removed
    if(current->point==p1){
        //Shift the head down to the metaphorical 'neck'
        __points=current->next;
    }
    //check if the body or tail is the targeted point
    else{
        LNodePtr prev ;
        while(current!= nullptr && current->point!=p1){
            
            //move down the linked list
            prev=current;
            current = current->next;
        }
        //when the point is found, detach the LNode from the linked list
        prev->next=current->next;
    } //end of else
    
    --__size;
    return p1;
}

const Point& Cluster::operator[](unsigned int index) const {
    if (getSize()==0) {
     
        throw EmptyClusterEx();
        
    }
    if (index > getSize()-1){
        throw OutOfBoundsEx(getSize(), index);
        
        
    }
    
    unsigned int counter=0;
    
    //initially temp is the head of the linked list
    LNodePtr temp = __points;
    
    //traverse through the while loop until the correct index is found
    while (counter<index && temp!= nullptr){
        temp=temp->next;
        counter++;
    }
    
    return temp->point;
}


std::ostream& Clustering::operator<<(std::ostream& os , const Cluster& cl){
//    LNodePtr current = cl.__points;
//    
//    if (&current != NULL)
//    {
//        for (current; &current->point != NULL; current = current->next)
//        {
//            os << current->point;
//            if (&current->next != NULL)
//                os << "\n";
//        }
//    }
    std::cout<<cl.__size<<std::endl;
    // Point temp;
    for(int i=0; i<cl.__size; i++){
        //temp=__points.point;
        os<<cl.__points[i].point<<"\n";
    }
    return os;
    
    
}

std::istream& Clustering::operator>>(std::istream & is, Cluster & cl){
    std::string line;
    while (getline(is, line))
    {
        int numCommas = 0;
        
        for (int i = 0; i < line.size(); i++)
            if (line[i] == '_') numCommas++;
        

        Point *pointPtr = new Point(numCommas + 1);
        std::stringstream lineStream(line);
        
        lineStream >> *pointPtr;
        
        cl.add(*pointPtr);
    }
    
    
    
    return is;
    
}

bool Cluster::contains ( const Point& p1)const{
    
    return __in(p1);
    
}
Cluster& Cluster::operator+=(const Point& p1){
    if (p1.getDims() != __dimensionality) {
        throw DimensionalityMismatchEx(__dimensionality, p1.getDims());
    
    }
    add(p1);
    
    return *this;
}

Cluster& Cluster::operator-=(const Point& p1){
    if (p1.getDims() != __dimensionality) {
        throw DimensionalityMismatchEx(__dimensionality, p1.getDims());
        
    }

    remove(p1);
    
    return *this;
}

Cluster& Cluster::operator+=(const Cluster& c1){
    if (c1.getDimensionality() != __dimensionality) {
        throw DimensionalityMismatchEx(__dimensionality, c1.getDimensionality());
        
    }
    
    LNodePtr temp = c1.__points;
    while (temp != nullptr)
    {
        add (temp->point);
        temp = temp->next;
        
        
    }
    
    //std::cout<< getSize()<<std::endl;
    return *this;
}

Cluster& Cluster::operator-=(const Cluster& c1){
    if (c1.getDimensionality() != __dimensionality) {
        throw DimensionalityMismatchEx(__dimensionality, c1.getDimensionality());
        
    }

    LNodePtr temp = c1.__points;

    while (temp!= nullptr)
    {

        Point tempPt = remove(temp->point);

        temp = temp->next;
    }

    
    return *this;
}





const Cluster Clustering:: operator+(const Cluster& c1, const Point& p1){
    
    if (c1.getDimensionality() != p1.getDims()) {
        throw DimensionalityMismatchEx(c1.getDimensionality(), p1.getDims());
    }

    Cluster *temp = new Cluster(c1);
    
    if (c1.__in(p1)){

        return c1;
    }
    temp->add(p1);

    return *temp;
}

const Cluster Clustering::operator-(const Cluster& c1, const Point& p1){
    if (c1.getDimensionality() != p1.getDims()) {
        throw DimensionalityMismatchEx(c1.getDimensionality(), p1.getDims());
    }
    
    Cluster temp(c1);
    
    temp.remove(p1);
    
    
    return temp;
}
const Cluster Clustering:: operator+(const Cluster& c1, const Cluster& c2){
    if (c1.getDimensionality() != c2.getDimensionality()) {
        throw DimensionalityMismatchEx(c1.getDimensionality(), c2.getDimensionality());
    }
    
    Cluster newCluster(c1);
    return newCluster += c2;
    
    
    return c1;
}


const Cluster Clustering:: operator-(const Cluster& c1, const Cluster& c2){
    if (c1.getDimensionality() != c2.getDimensionality()) {
        throw DimensionalityMismatchEx(c1.getDimensionality(), c2.getDimensionality());
    }

    Cluster newCluster(c1);
    return newCluster -=c2;
    
    return c1;
}
Cluster::Move::Move(const Point &p, Cluster &from, Cluster &to):__p(p), __from(from),__to(to)
{
    
    
}
void Cluster::Move::perform(){
    __from.remove(__p);
    __to.add(__p);
    
}

void Cluster::pickCentroids(unsigned int k, Clustering::Point **pointArray){
    
    if(k<getSize() || k == getSize()){
        int i =0;
        while (i < k ){
            
            *pointArray[i] = (*this)[i];
            i++;
            
        }
        return;
    }
    int i =0;
    while (i<getSize()) {
        *pointArray[i] = (*this)[i];
        i++;
    }
    while (i<k) {
        for (int l = 0; l<getDimensionality()  ; l++) {
            pointArray[l] -> setValue(l, std::numeric_limits<double>::max());
 
            
        }
        
        i++;
        
    }
    
}






