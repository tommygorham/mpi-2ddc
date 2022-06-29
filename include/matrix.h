/* Program name: matrix.h
 * Description: class definition to store data logically in 2 dimensions, representing a matrix 
 *             
 */ 

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream> 
#include <string_view> 

// NOTE: definitions in class header since we are using templates 
template <typename T> class Matrix{
public: 
    // constructor: uses size_t to generalize unsigned int, size_t defined in std namespace     
    Matrix(int  rows, int  cols) : m_rows(rows), m_cols(cols), m_data(new T[rows*cols]) {} 
	
	  // destructor 
    virtual ~Matrix() { delete[] m_data; }

    // overload "=" for copying 
    Matrix &operator=(const Matrix<T> &rhs);
        
    // overload "()" for m_data(i, j) accessors 
    T &operator()(int  i, int  j) {
    return m_data[i*m_cols+j];
    } // row major
    T operator()(int  i, int  j) const {
    return m_data[i*m_cols+j]; } // row major 

    void Resize(int  Mprime, int  Nprime); //if we copy a matrix of different num rows, cols
    
    // member function to print mpi matrix 
    void printMatMPI(char* node_name, int mpi_rank) {
        std::cout << "\nMPI Rank: " << mpi_rank << " On Node : " << node_name <<  std::endl;
        for (int i = 0; i < (*this).Rows(); ++i) {
            for (int j = 0; j < (*this).Cols(); ++j) {
            std::cout << (*this)(i,j) << " "; 
            }
            std::cout << ("\n"); 
        }
        std::cout << ("\n"); 
     }
   
   void printNameAndMat(std::string_view name) {
	   std::cout << "\nMatrix " << name << "\n"; 
        for (int i = 0; i < (*this).Rows(); ++i) {
            for (int j = 0; j < (*this).Cols(); ++j) {
            std::cout << (*this)(i,j) << " "; 
            }
            std::cout << ("\n"); 
        }
        std::cout << ("\n"); 
     }
        
    // member function to fill matrix with mpirank 
    void fillMatIntRank(int& world_rank) {
        int fill_a = world_rank; 
        for (int i = 0; i < (*this).Rows(); ++i) {
            for (int j = 0; j < (*this).Cols(); ++j) {
            (*this)(i,j) = fill_a;  
            fill_a++; 
            }
        }
    }
   void fillMatInt() {
	    int fill = 1; 
        for (int i = 0; i < (*this).Rows(); ++i) {
            for (int j = 0; j < (*this).Cols(); ++j) {
            (*this)(i,j) = fill;  
            // fill++;  
            }
        }
    }

    T *get_Matrix() { return &m_data[0]; } // can use for mpi calls
    
    //const size_t Index(const size_t rows, const size_t cols) const;
    
    // matrix dimensions accessors 
    int  Rows() const {return m_rows;}
    int  Cols() const {return m_cols;}
    
private:
  int m_rows, m_cols;
  T *m_data;
};
#endif
