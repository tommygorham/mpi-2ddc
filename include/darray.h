/* 
 * Program name: darray.h
 * Description: class definition to store heap allocated array data with one logical dimension  
 *              
 * Initial version: July 2021           
 *
 */ 

#ifndef DARRAY_H
#define DARRAY_H
#include <iostream> 
#include <string_view> 

template <typename T> 
class Darray {
public:
   // constructor
   Darray(int length) : m_length(length), m_data(new T[length]) {}
    
  // destructor
  virtual ~Darray() { delete[] m_data; }  

  // overload "()"
  T &operator()(int index) { return m_data[index]; }   
  const T &operator()(int index) const { return m_data[index]; } 

  // number of elements
  int size() const { return m_length; } // Accessor

  // get memory at memory address where data is stored
  T *getDarray() { return &m_data[0]; } 
  
  // member function to print matrix 
  void printArrayMPI(char* node_name) {
        std::cout << "\nNode : " << node_name <<  std::endl;
        for (int i = 0; i < (*this).size(); ++i) {
            std::cout << (*this)(i) << "\n";  
            }
    }
   
  void printNameAndArray(std::string_view name) {
	    std::cout << "Vector " << name << "\n";  
		for (int i = 0; i < (*this).size(); ++i) {
            std::cout << (*this)(i) << "\n";  
            }
    }
    
    // member function to fill an array with a constant var 
    void fillDarrayInt() {
        for (int i = 0; i < (*this).size(); ++i) {
            (*this)(i) = 2;   
            }
    }
    
private:
  int m_length; // size of vector
  T *m_data; // pointer to vector
};

#endif
