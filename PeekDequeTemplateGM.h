/** File "PeekDequeGM.cpp", by Gelareh Malek Pour for CSE250 Spring 2014.  Assignment 3+4 answer, as well as part one of assignment 5.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

//#include <cmath>   //for fabs

using std::vector;
using std::endl;
using std::cerr;
using std::ostringstream;
using std::string;
using std::cout;

template<typename T>
class PeekDeque;

template<typename T>
class Deque {
   friend class PeekDeque<T>;  //specifying that peekDeque is a template. From now one everytime you mention peekDeque, you use <T> as well.

   vector<T>* elements;//change string to <T>
   int rearSpace;
   int frontItem;
   int upperBound;

   //CLASS INV: frontSpace indicates first empty cell for pushFront
   //           rearItem designates rear item (not space) for popRear---
   //           ---or if there is no such item, rearItem == frontSpace;

 public: 

   explicit Deque<T>(int guaranteedCapacity) //mention <T> in constructor to say it's a template as well
    : elements(new vector<T>(2*guaranteedCapacity)), //string to T
      frontItem(guaranteedCapacity),
      rearSpace(guaranteedCapacity),
      upperBound(2*guaranteedCapacity) 
   { }

   virtual ~Deque<T>() { delete elements; cout << "It's Deque Season!" << endl; }

   virtual bool empty() const { return frontItem == rearSpace; }

   virtual bool full() const { return rearSpace == upperBound; }

   virtual size_t size() const { return rearSpace - frontItem; }

   virtual void pushFront(T newItem) {   //string to T. Now you can push anything in Deque class
      if (full()) {
         cerr << "Are you playing with a full Deque?" << endl;
         cerr << toString() << endl;
      } else {
         elements->at(--frontItem) = newItem;
      }
   }

   virtual void pushRear(T newItem) {
      if (full()) {
         cerr << "Are you playing with a full Deque?" << endl;
         cerr << toString() << endl;
      } else {
         elements->at(rearSpace++) = newItem;
      }
   }

   virtual T popFront() {  //changing the return type here
      if (empty()) {
         cerr << "Too lazy to throw an EmptyDequeException." << endl;
         return T() ;  //no longer return an empty string only. Just return T(). The empty parantheses represent the default constructor.
      } else {
         return elements->at(frontItem++);
      }
   }

   virtual T popRear() {
      if (empty()) {
         cerr << "Too lazy to throw an EmptyDequeException." << endl;
         return T();
      } else {
         return elements->at(--rearSpace);  //translates Java "next()"
      }
   }

   virtual string toString() const { //it is converting to string, so don't change return type 
      ostringstream OUT;
      //string out = "";
      for (int i = frontItem; i < rearSpace; i++) {
         //out += elements->at(i).str() + " ";
         OUT << elements->at(i) << " ";
      }
      //return out;
      return OUT.str();
   }

};


template<typename T>
class PeekDeque : public Deque<T> {

   int peekIndex;

 public:

   explicit PeekDeque<T>(int guaranteedCapacity)
    : Deque<T>(guaranteedCapacity), peekIndex(this->frontItem) { } //whenever you want to access the element of this class, like front item, you need to include this->

   virtual ~PeekDeque() { cerr << "No peeking..."; } //automatically calls ~Deque()

   virtual void moveFrontward() { peekIndex--; }

   virtual void moveRearward() { peekIndex++; }

   virtual T peek() const { return this-> elements->at(peekIndex); }  //added this-> here

   virtual T popFront() { 
      if (this->empty()) { cerr << "Pop attempt from empty PeekDeque" << endl;
	return T(); }
      else return Deque<T>::popFront();   //Do either this->popFront or do what is already in the code. They're the same!
   }

   virtual T popRear() {
      if (this->empty()) { cerr << "Pop attempt from empty PeekDeque" << endl;
	return T(); }
      else return Deque<T>::popRear();
   }

   //Extra functionality

   virtual void setPeekToFront() { peekIndex =this-> frontItem; }

   virtual bool atRear() const { return peekIndex == this->rearSpace; }   //this for this and prev method

};
