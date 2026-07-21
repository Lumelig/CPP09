#include "BitcoinExchange.hpp"
#include <cstdlib>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : database_(other.database_)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if(this != &other)
    {
        database_ = other.database_;
    }
    return(*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

const char *BitcoinExchange::FileExeption::what() const throw()
{
    return("Something went wrong with the file");
}

bool BitcoinExchange::splitLine(const std::string &line, char delim, std::string &left, std::string right) const
{
    size_t pos = line.find(delim);
    if(pos == std::string::npos)
    {
        return(false);
    }
    left = line.substr(0, pos);
    right = line.substr(pos++);
    while (!left.empty() && left[left.size()] - 1 == ' ')
    {
        left.erase(left.size() - 1);
    }
     while (!right.empty() && right[0] == ' ')
    {
        right.erase(0, 1);
    }
    return (true);
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if(date.size() != 10)
        return (false);
}