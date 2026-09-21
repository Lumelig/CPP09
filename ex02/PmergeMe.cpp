/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpflegha <jpflegha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:12:53 by Jpflegha          #+#    #+#             */
/*   Updated: 2026/09/21 11:54:40 by Jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

PmergeMe::PmergeMe()
{
    
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    (void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    (void)other;
    return(*this);
}

PmergeMe::~PmergeMe()
{
    
}

unsigned long	PmergeMe::comparisons_ = 0;

unsigned long PmergeMe::compar()
{
    return(comparisons_);
}

void    PmergeMe::resetCompar()
{
    comparisons_ = 0;
}

// VECTOR

bool PmergeMe::cmpVec(const VecRun &a, const VecRun &b)
{
    ++comparisons_;
    return (a.back() < b.back());
}

void PmergeMe::mergeInsertVec(VecRuns &runs)
{
    const std::size_t   NO_BOUND = static_cast<std::size_t>(-1);
    const std::size_t   n = runs.size();

    if(n < 2)
        return;
    
    // get rid of the stranggler
    bool	hasStraggler = (n % 2 != 0);
	VecRun	straggler;
	if (hasStraggler)
	{
		straggler = runs.back();
		runs.pop_back();
	}

    // make pairs 
    VecRuns pairs;
    for(std::size_t i = 0; i < runs.size(); i += 2)
    {
        VecRun  &x = runs[i];
        VecRun  &y = runs[i + 1];
        VecRun merged;
        if(cmpVec(x, y))
        {
            merged = x;
            merged.insert(merged.end(), y.begin(), y.end());
        }
        else
        {
            merged = y;
            merged.insert(merged.end(), x.begin(), x.end());
        }
        pairs.push_back(merged);
    }
    //recursive sorting of the biggest number of the pair or the biggest partner
    mergeInsertVec(pairs);
    
    //split again
    const std::size_t           half = pairs.front().size() / 2;
    VecRuns                     main_chain;
    VecRuns                     pend;
    std::vector<std::size_t>    partner;

    main_chain.push_back(VecRun(pairs[0].begin(), pairs[0].begin() + half));
    for(std::size_t i = 0; i < pairs.size(); ++i)
    {
        main_chain.push_back(VecRun(pairs[i].begin() + half, pairs[i].end()));
    }
    for(std::size_t i = 1; i < pairs.size(); ++i)
    {
        pend.push_back(VecRun(pairs[i].begin(), pairs[i].begin() + half));
        partner.push_back(i + 1);
    }
    if(hasStraggler)
    {
        pend.push_back(straggler);
        partner.push_back(NO_BOUND);
    }

    const std::size_t   k = pend.size();
    std::size_t         prev = 1;
    std::size_t         curr = 3;
    std::size_t         done = 1;

    while (done < k + 1) 
    {
        std::size_t last = std::min(curr, k + 1);
        for(std::size_t j = last; j >prev; --j)
        {
            std::size_t     p = j - 2;
            std::size_t hi;
            if (partner[p] == NO_BOUND)
                hi = main_chain.size();
            else
                hi = partner[p];
            VecRuns::iterator   stop = main_chain.begin() + hi;
            VecRuns::iterator   pos = std::upper_bound(main_chain.begin(), stop, pend[p], PmergeMe::cmpVec);
            std::size_t         index = static_cast<std::size_t>(pos - main_chain.begin());
            
            main_chain.insert(pos, pend[p]);
            for(std::size_t t = 0; t < partner.size(); ++t)
            {
                if(partner[t] != NO_BOUND && partner[t] >= index)
                    ++partner[t];
            }
        }
        done = last;
        std::size_t next = curr + 2 * prev;
        prev = curr;
        curr = next;
    }
    runs.swap(main_chain);
}

void    PmergeMe::sortVector(std::vector<int> &data)
{
    if(data.size() < 2)
        return;
    
    VecRuns runs;
    for(std::vector<int>::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        runs.push_back(VecRun(1, *it));
    }
    mergeInsertVec(runs);
    
    data.clear();
    for(VecRuns::const_iterator it = runs.begin(); it != runs.end(); ++it)
    {
        data.push_back(it->back());
    }
}

bool PmergeMe::cmpDeq(const DeqRun &a, const DeqRun &b)
{
    ++comparisons_;
    return(a.back() < b.back());
}

void PmergeMe::mergeInsertDeq(DeqRuns &runs)
{
    const std::size_t   NO_BOUND = static_cast<std::size_t>(-1);
    const std::size_t   n = runs.size();

    if (n < 2)
		return ;

	bool	hasStraggler = (n % 2 != 0);
	DeqRun	straggler;
	if (hasStraggler)
	{
		straggler = runs.back();
		runs.pop_back();
	}
    DeqRuns	pairs;
	for (std::size_t i = 0; i < runs.size(); i += 2)
	{
		DeqRun	&x = runs[i];
		DeqRun	&y = runs[i + 1];
		DeqRun	merged;

		if (cmpDeq(x, y))
		{
			merged = x;
			merged.insert(merged.end(), y.begin(), y.end());
		}
		else
		{
			merged = y;
			merged.insert(merged.end(), x.begin(), x.end());
		}
		pairs.push_back(merged);
	}
    	mergeInsertDeq(pairs);

	const std::size_t			half = pairs.front().size() / 2;
	DeqRuns						main_chain;
	DeqRuns						pend;
	std::deque<std::size_t>		partner;

	main_chain.push_back(DeqRun(pairs[0].begin(), pairs[0].begin() + half));
	for (std::size_t i = 0; i < pairs.size(); ++i)
		main_chain.push_back(DeqRun(pairs[i].begin() + half, pairs[i].end()));
	for (std::size_t i = 1; i < pairs.size(); ++i)
	{
		pend.push_back(DeqRun(pairs[i].begin(), pairs[i].begin() + half));
		partner.push_back(i + 1);
	}
	if (hasStraggler)
	{
		pend.push_back(straggler);
		partner.push_back(NO_BOUND);
	}

	const std::size_t	k = pend.size();
	std::size_t			prev = 1;
	std::size_t			curr = 3;
	std::size_t			done = 1;

    while (done < k + 1) 
    {
        std::size_t last = std::min(curr, k + 1);
        for(std::size_t j = last; j > prev; --j)
        {
            std::size_t p = j - 2;
            std::size_t    hi;
            if (partner[p] == NO_BOUND)
                hi = main_chain.size();
            else
                hi = partner[p];
            DeqRuns::iterator		stop = main_chain.begin() + hi;
			DeqRuns::iterator		pos = std::upper_bound(main_chain.begin(),
										stop, pend[p], PmergeMe::cmpDeq);
			std::size_t				idx = static_cast<std::size_t>(
										pos - main_chain.begin());

			main_chain.insert(pos, pend[p]);
			for (std::size_t t = 0; t < partner.size(); ++t)
				if (partner[t] != NO_BOUND && partner[t] >= idx)
					++partner[t];
		}
		done = last;
		std::size_t	next = curr + 2 * prev;
		prev = curr;
		curr = next;
	}

	runs.swap(main_chain);
}

void	PmergeMe::sortDeque(std::deque<int> &data)
{
	if (data.size() < 2)
		return ;

	DeqRuns	runs;
	for (std::deque<int>::const_iterator it = data.begin();
		 it != data.end(); ++it)
		runs.push_back(DeqRun(1, *it));

	mergeInsertDeq(runs);

	data.clear();
	for (DeqRuns::const_iterator it = runs.begin(); it != runs.end(); ++it)
		data.push_back(it->back());
}