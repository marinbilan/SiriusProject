#include "MayersCh4.h"


Mayers::MayersCh4::MayersCh4(int id) : m_Id(id)
{
    std::cout << "[MayersCh4] Constructor called" << '\n';

};


Mayers::MayersCh4::~MayersCh4()
{
    std::cout << "[MayersCh4] Destructor called" << std::endl;
}


int Mayers::MayersCh4::getId() const
{
    return m_Id;
}


void Mayers::MayersCh4::toString() const
{
    std::cout << "m_Id: " << m_Id << '\n';
}