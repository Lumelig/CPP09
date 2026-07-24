/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpflegha <jpflegha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 19:09:09 by Jpflegha          #+#    #+#             */
/*   Updated: 2026/07/24 14:23:33 by Jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void loadDatabase(const std::string &filename);
        void processInput(const std::string &filename);
  
        class FileException : public std::exception
        {
          public:
            virtual const char *what() const throw();  
        };
    private:
        std::map<std::string, float> database_;

        bool isValidDate(const std::string &date) const;
        bool isValidValue(const std::string &valueStr, float &value, const std::string &line) const;
        bool splitLine(const std::string &line, char delim, std::string &left, std::string &right) const;
        float getRate(const std::string &date) const;
        
};

#endif