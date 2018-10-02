//
// Created by hagitba on 1/22/18.
//

#ifndef EX3_EXCEPTION_H
#define EX3_EXCEPTION_H

#include <exception>

/**
 * IllegalSize exception
 */
class IllegalSize : public std::exception
{
    /**
     *return the exception msg
     * @return the exception msg
     */
    virtual const char* what() const throw()
    {
        return "The matrix size need to be more or equal to one";
    }
};

/**
 * DifferentMatricesSize exception
 */
class DifferentMatricesSize : public std::exception
{
    /**
     *return the exception msg
     * @return the exception msg
     */
    virtual const char* what() const throw()
    {
        return "The matrices size need to be the same";
    }
};

/**
 * UnsquareMatrix exception
 */
class UnsquareMatrix : public std::exception
{
    /**
     *return the exception msg
     * @return the exception msg
     */
    virtual const char* what() const throw()
    {
        return "The matrix is not square";
    }
};

/**
 * IllegalIndex exception
 */
class IllegalIndex : public std::exception
{
    /**
     *return the exception msg
     * @return the exception msg
     */
    virtual const char* what() const throw()
    {
        return "The index is out of bound";
    }
};

/**
 * NoMatchNumOfCells exception
 */
class NoMatchNumOfCells : public std::exception
{
    /**
     *return the exception msg
     * @return the exception msg
     */
    virtual const char* what() const throw()
    {
        return "The number of cells need to be row*col";
    }
};

#endif //EX3_EXCEPTION_H
