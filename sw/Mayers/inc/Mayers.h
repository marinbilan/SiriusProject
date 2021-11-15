#pragma once
#include "MayersIf.h"


namespace Mayers
{
class Mayers : public MayersIf
{
public:
	Mayers(int id);

    ~Mayers();

    int getId() const;

    void toString() const;

    // ITEM: 1
    // ----
    /*
    template<typename T>
    void f(ParamType param)
    */

    // [Case 1] : ParamType is a Reference or Pointer, but not a Universal Reference
    template<typename T>
    void f(T& param) 
    {
        param = 27;
        std::cout << " This is call of method f(T& param) | param = " << param << '\n';
    }

    template<typename T>
    void ff(const T& param) 
    {
        // Param is now const so we are not able now to change it
        // error: assignment of read-only reference ‘param’
        // param = 27;
        std::cout << " This is call of method ff(const T& param) | param = " << param << '\n';
    }

    // [Case 2] : ParamType (T&&) is a Universal Reference
    /*
    Unversal References are declared as rvalue reverences (diff beh when lvalue and rvalue are
    passed in)
    IMPORTANT: T&& - ONLY if we pass rvalue is passed (for ex: number Item 24)
    */
    template<typename T> 
    void fff(T&& param)
    { 
        param = 23; 
        std::cout << " This is call of method fff(const T& param) | param = " << param << '\n';
    }

    // Item 10
    // Case: 1 
    template<typename E> 
    constexpr typename std::underlying_type<E>::type 
    toUType1(E enumerator) noexcept 
    { 
        return static_cast<typename std::underlying_type<E>::type>(enumerator); 
    } 

    // Case: 2 C++ 14  
    template<typename E> // C++14 
    constexpr std::underlying_type_t<E> 
    toUType2(E enumerator) noexcept 
    { 
        return static_cast<std::underlying_type_t<E>>(enumerator); 
    } 

    // Case: 3 auto  
    template<typename E> // C++14 
    constexpr auto 
    toUType3(E enumerator) noexcept 
    { 
        return static_cast<std::underlying_type_t<E>>(enumerator); 
    } 

    void testItem10_0();

private:	
int m_Id;
};
} // End of namespace

