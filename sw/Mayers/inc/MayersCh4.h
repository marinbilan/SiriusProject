#pragma once
#include "MayersIf.h"


namespace Mayers
{


class InvestmentIf 
{
public:
	virtual ~InvestmentIf() 
	{
		std::cout << "~InvestmentIf called! " << '\n';
	}
};


class Stock : public InvestmentIf {
public:
	Stock(int id) : m_id(id) 
	{
		stock_ptr = this;
		std::cout << "[" << stock_ptr << "]" << " Stock constructor with id = " << m_id << '\n';
	}

	~Stock() 
	{
		std::cout << "This is Stock destructor with id = " << m_id << '\n';
	}

private:
int m_id;
Stock* stock_ptr;
};


class Bond : public InvestmentIf {
public:
	Bond(int id) : m_id(id) 
	{
		std::cout << "This is Bond constructor with id = " << m_id << '\n';
	}

	~Bond() 
	{
		std::cout << "This is Bond destructor with id = " << m_id << '\n';
	}

private:
int m_id;
};


class MayersCh4 : public MayersIf
{
public:
	MayersCh4(int id);

    ~MayersCh4();

    int getId() const;

    void toString() const;

    template<typename... Ts>
    // IMPORTANT: This return type will not work!
    // std::unique_ptr<InvestmentIf>
    // nither this return type (This would work but delInvmt is declared inside method)
    //std::unique_ptr<InvestmentIf, decltype(delInvmt)>
    auto
    makeInvestment(const std::string& investmentType, Ts&&... params) 
    {
    	auto delInvmt = [](InvestmentIf* pInvestment) {
    		// ... do some logging ...
    		delete pInvestment;
    	};

    	std::unique_ptr<InvestmentIf, decltype(delInvmt)> pInv(nullptr, delInvmt);

    	if(!investmentType.compare("Stock")) {
    		std::cout << "This is Stock investment! " << '\n';
    		
    		// Create Stock with InvestmentIf
    		pInv.reset(new Stock(std::forward<Ts>(params)...));

    	} else if(!investmentType.compare("Bond")) {
    		std::cout << "This is Bond investment! " << '\n';
    		
    		// Create Bond with InvestmentIf
    		pInv.reset(new Bond(std::forward<Ts>(params)...));
    	}

    	return pInv;
    }

private:	
int m_Id;
};
} // End of namespace

