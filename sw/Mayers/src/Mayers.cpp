#include "Mayers.h"


Mayers::Mayers::Mayers(int id) : m_Id(id)
{
    std::cout << "[Mayers] Constructor called" << '\n';

};


Mayers::Mayers::~Mayers()
{
    std::cout << "[Mayers] Destructor called" << std::endl;
}


int Mayers::Mayers::getId() const
{
    return m_Id;
}


void Mayers::Mayers::toString() const
{
    std::cout << "m_Id: " << m_Id << '\n';
}


void Mayers::Mayers::testItem10_0()
{
    std::cout << "> START TestItem10" << '\n';

    // Case: 1 
    // enum Color { black, white, red }; 
    // auto white = false; // error: Already declared 

    // Case: 2 
    enum class Color { black, white, red }; 
    auto white = false; // OK 

    // Color c = white; // error 
    Color c = Color::white; // Ok 

    /* 
    Enumerators for unscoped 
    enums implicitly convert to integral types (and, from there, to floating-point 
    types). 
    */ 

    // if (c < 15.5) { ... } // error! can't compare Color and double 
    // If your really want to cast Color to double static_cast<double>(c) 

    // Also OK  
    // enum class Status: std::uint32_t { good = 0, // To define type specifications 
    enum Status { good = 0, 
                failed = 1, 
                incomplete = 100, 
                corrupt = 200, 
                audited = 500, 
                indeterminate = 0xFFFFFFFF 
    }; 

    // Case: 3  
    using UserInfo = std::tuple<std::string, std::string, std::size_t>; 

    // UserInfo uInfo; // Define object and unit test this 
    // auto val = std::get<1>(uInfo); // get value of field 1 
    // OR 
    enum UserInfoFields { uiName, uiEmail, uiReputation }; 
    // auto val = std::get<uiEmail>(uInfo); // ah, get value of email field 

    // Case: 4 
    enum class UserInfoFields2 { uiName, uiEmail, uiReputation }; 
    // auto val = std::get<static_cast<std::size_t>(UserInfoFields::uiEmail)>(uInfo); 

    // Case: 5 - Move std::get<static_cast<std::size_t> to template toUTypeX 
    // Check call of three template mathods above 
    // auto val = std::get<toUTypeX(UserInfoFields::uiEmail)>(uInfo); 
}