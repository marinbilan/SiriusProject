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
