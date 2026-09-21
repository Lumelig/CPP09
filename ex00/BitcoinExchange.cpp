#include "BitcoinExchange.hpp"
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>

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

const char *BitcoinExchange::FileException::what() const throw()
{
    return("Something went wrong with the file");
}

bool BitcoinExchange::splitLine(const std::string &line, char delim, std::string &left, std::string &right) const
{
    size_t pos = line.find(delim);

    if (pos == std::string::npos)
        return false;

    left = line.substr(0, pos);
    right = line.substr(pos + 1);

    // Trim left
    while (!left.empty() && left[0] == ' ')
        left.erase(0, 1);

    while (!left.empty() && left[left.size() - 1] == ' ')
        left.erase(left.size() - 1);

    // Trim right
    while (!right.empty() && right[0] == ' ')
        right.erase(0, 1);

    while (!right.empty() && right[right.size() - 1] == ' ')
        right.erase(right.size() - 1);

    return true;
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if(date.size() != 10)
        return (false);
    if(date[4] != '-' || date[7] != '-')
        return (false);
    for(size_t i = 0; i <date.size(); i++)
    {
        if(i == 4 || i == 7)
            continue;
        if(!std::isdigit(date[i]))
            return(false);
    }
    int year, month, day;
    try
    {
        year = std::stoi(date.substr(0, 4));
        month = std::stoi(date.substr(5, 2));
        day = std::stoi(date.substr(8, 2));
    }
    catch (std::exception &e)
    {
        return (false);
    }

    if(month < 1 || month > 12)
        return(false);
    else if(day < 1 || day > 31)
        return(false);

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (month == 2)
    {
        if (isLeap && day > 29)
            return false;

        if (!isLeap && day > 28)
            return false;
    }
    else if (day > daysInMonth[month - 1])
    {
        return false;
    }
    
    return (true);
}

bool BitcoinExchange::isValidValue(const std::string &valueStr, float &value, const std::string &line) const
{
    if(valueStr.empty())
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return(false);
    }
    std::istringstream iss(valueStr);
    iss >> value;
    if(iss.fail() || !iss.eof())
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return(false);
    }
    else if (value < 0)
     {
        std::cout << "Error: not a positive number." << std::endl;
        return(false);
     }
    else if(value > 1000)
    {
        std::cout << "Error: too large a number." << std::endl;
        return(false);
    }
    return(true);
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
   std::ifstream file(filename);

    if (!file.is_open())
        throw FileException();

    std::string line;

    // Check the header
    if (!std::getline(file, line))
        throw FileException();

    if (line.find("date") == std::string::npos ||
        line.find("exchange_rate") == std::string::npos)
    {
        std::cout << "Error: invalid database header." << std::endl;
        return;
    }
    while (std::getline(file, line))
    {
        if(line.empty())
            continue;
        std::string date, rateStr;
        if(!splitLine(line, ',', date, rateStr))
            continue;
        if(!isValidDate(date))
            continue;
        float rate = std::stof(rateStr);
        database_[date] = rate;
    }
    file.close();
}


float BitcoinExchange::getRate(const std::string &date) const
{
    std::map<std::string, float>::const_iterator it = database_.lower_bound(date);

    //date fits poerfect
    if(it != database_.end() && it->first == date)
        return(it->second);
    if(it == database_.begin())
        throw std::out_of_range("No date available before " + database_.begin()->first);
    // if not, lower_bound give you the next higher or equal date but we need the one befor if not fit
    --it;
    return(it->second); 
}

void BitcoinExchange::processInput(const std::string &filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
        throw FileException();

    std::string line;
    float value;
    
    // Check the header
    if (!std::getline(file, line))
        throw FileException();

    if (line.find("date") == std::string::npos || line.find("value") == std::string::npos)
    {
        std::cout << "Error: invalid input header." << std::endl;
        return;
    }

    while (std::getline(file, line))
    {
        if(line.empty())
            continue;
        std::string date, valueStr;
        if(!splitLine(line, '|', date, valueStr))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        else if(!isValidDate(date))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        else if(!isValidValue(valueStr, value, line))
        {
            continue;
        }
         try
        {
            float rate = getRate(date);
            std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
        }
        file.close();
}