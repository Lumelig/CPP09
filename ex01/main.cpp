/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpflegha <jpflegha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 18:49:44 by Jpflegha          #+#    #+#             */
/*   Updated: 2026/09/09 14:32:49 by Jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <ostream>

int main(int ac, char** av)
{
    if(ac != 2)
    {
        std::cout << "You need exactly one argument." << std::endl;
        return(1);
    }
    try {
    {
        RPN rpn;
        int result = rpn.eval(av[1]);
        std::cout << result << std::endl;
    }
    } catch (std::exception &e) 
    {
        std::cerr << e.what() << std::endl;
        return(1);
    }
    return(0);
}