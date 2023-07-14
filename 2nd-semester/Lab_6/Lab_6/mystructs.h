#ifndef MYSTRUCTS_H_
#define MYSTRUCTS_H_

#include <string>

struct TradeData
{
	std::string TypeOfSecurities;
	std::string AmountOfDeals;
	std::string TradingVolume;
};

struct Trade
{
	Trade* next{};
	TradeData data{};
};

struct DefaultTrade {
	std::string def_TypeOfSecurities;
	std::string def_AmountOfDeals;
	std::string def_TradingVolume;
};

#endif /* MYSTRUCTS_H_ */