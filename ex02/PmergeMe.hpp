/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpflegha <jpflegha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:12:50 by Jpflegha          #+#    #+#             */
/*   Updated: 2026/09/21 12:26:15 by Jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <deque>
#include <vector>


//https://claude.ai/artifact/XEqbpCqCXCbi4mpukvuW6S

class PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();
    
        static void sortVector(std::vector<int> &data);
        static void sortDeque(std::deque<int> &data);

        static unsigned long	compar();
	    static void				resetCompar();

    private:
        typedef std::vector<int>    VecRun;
        typedef std::vector<VecRun> VecRuns;
        typedef std::deque<int>     DeqRun;
        typedef std::deque<DeqRun>  DeqRuns;
        
        static unsigned long    comparisons_;
        
        static bool cmpVec(const VecRun &a, const VecRun &b);
        static bool cmpDeq(const DeqRun &a, const DeqRun &b);

        static void mergeInsertVec(VecRuns &runs);
        static void mergeInsertDeq(DeqRuns &runs);
};

#endif