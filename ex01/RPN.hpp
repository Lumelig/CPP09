/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpflegha <jpflegha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 18:49:53 by Jpflegha          #+#    #+#             */
/*   Updated: 2026/09/09 14:34:01 by Jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <stack>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>


class RPN
{
    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();
        
        int eval(const std::string &command);
        
        class InvalidCommand : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
        
        private:
            std::stack<int> stack_;
            
            bool    isOperator(const std::string &token) const;
            bool    isNumber(const std::string &token) const;
            int     calculator(int a, int b, const std::string &op) const;
};

#endif