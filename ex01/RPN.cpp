/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpflegha <jpflegha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 18:49:50 by Jpflegha          #+#    #+#             */
/*   Updated: 2026/10/01 11:26:38 by Jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

RPN::RPN()
{}

RPN::RPN(const RPN &other) : list_(other.list_)
{
    
}

RPN &RPN::operator=(const RPN &other)
{
    if(this != &other)
    {
        list_ = other.list_;
    }
    return(*this);
}

RPN::~RPN()
{
    
}

const char *RPN::InvalidCommand::what() const throw()
{
    return("Error");
}

bool RPN::isOperator(const std::string &token) const
{
    return(token == "+" || token == "-" || token == "*" || token == "/");
}
 bool RPN::isNumber(const std::string &token) const
 {
    if(token.empty())
        return (false);
    
    size_t i = 0;
    if(token[0] == '-' || token[0] == '+')
        i = 1;
    if(i == token.size())
        return(false);
    for(; i < token.size(); ++i)
    {
        if(!std::isdigit(token[i]))
            return(false);
    }
    return(true);
 }

 int RPN::calculator(int a, int b, const std::string &op) const
 {
    if(op == "+")
        return (a + b);
    else if (op == "-")
        return (a - b);
    else if(op == "*")
    return (a * b);
    else if(op == "/")
    {
        if(b == 0)
            throw std::overflow_error("division by zero");
        return (a / b);
    }
    else
        throw InvalidCommand();
 }

 int RPN::eval(const std::string &command)
 {
    std::istringstream iss(command);
    std::string token;

    while (iss >> token) 
    {
        if(isNumber(token))
        {
            std::istringstream tokenValue(token);
            int value;
            tokenValue >> value;
            list_.push_back(value);            
        }
        else if(isOperator(token))
        {
            if(list_.size() < 2)
                throw InvalidCommand();
            int b = list_.back();
            list_.pop_back();
            int a = list_.back();
            list_.pop_back();
            
            int result = calculator(a, b, token);
            list_.push_back(result); 
        }
        else 
        {
            throw InvalidCommand();
        }
    }
    if(list_.size() != 1)
        throw InvalidCommand();
    
    return (list_.back());
 }