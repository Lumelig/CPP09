#include "PmergeMe.hpp"

#include <cctype>
#include <cerrno>
#include <chrono>
#include <climits>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/* A single token: digits only, must fit in an int. */
static bool	parseToken(const std::string &tok, int &out)
{
	if (tok.empty())
		return (false);
	for (std::size_t i = 0; i < tok.size(); ++i)
		if (!std::isdigit(static_cast<unsigned char>(tok[i])))
			return (false);

	errno = 0;
	char	*end = NULL;
	long	value = std::strtol(tok.c_str(), &end, 10);
	if (errno == ERANGE || *end != '\0' || value > INT_MAX)
		return (false);
	out = static_cast<int>(value);
	return (true);
}

/* First pass: only check and count, don't store anything yet. */
static bool	checkArgs(int argc, char **argv, std::size_t &count)
{
	count = 0;
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream	iss(argv[i]);
		std::string			tok;

		while (iss >> tok)
		{
			int	value;
			if (!parseToken(tok, value))
				return (false);
			++count;
		}
	}
	return (count > 0);
}

/* Fill the container from argv. This IS included in the timing. */
template <typename Container>
static void	fill(int argc, char **argv, Container &c)
{
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream	iss(argv[i]);
		std::string			tok;

		while (iss >> tok)
			c.push_back(static_cast<int>(std::strtol(tok.c_str(), NULL, 10)));
	}
}

template <typename Container>
static void	printSequence(const std::string &label, const Container &c)
{
	std::cout << label;
	for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

/* Print "Before:" straight from argv, so we don't need an extra
   container and the timing stays fair for both containers. */
static void	printBefore(int argc, char **argv)
{
	std::cout << "Before:";
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream	iss(argv[i]);
		std::string			tok;

		while (iss >> tok)
			std::cout << ' ' << tok;
	}
	std::cout << std::endl;
}

int	main(int argc, char **argv)
{
	std::size_t	count = 0;

	if (argc < 2 || !checkArgs(argc, argv, count))
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	std::vector<int>	vec;
	std::deque<int>		deq;

	printBefore(argc, argv);

	/* ---- std::vector: ---------- */
	std::chrono::steady_clock::time_point	v0
		= std::chrono::steady_clock::now();
	fill(argc, argv, vec);
	PmergeMe::sortVector(vec);
	std::chrono::steady_clock::time_point v1 = std::chrono::steady_clock::now();

	// unsigned long	cmpVec = PmergeMe::compar();

	/* ---- std::deque: ---------------------------------------- */
	std::chrono::steady_clock::time_point	d0
		= std::chrono::steady_clock::now();
	fill(argc, argv, deq);
	PmergeMe::sortDeque(deq);
	std::chrono::steady_clock::time_point d1 = std::chrono::steady_clock::now();

	// unsigned long	cmpDeq = PmergeMe::compar() - cmpVec;

	printSequence("After:", vec);

	double	usVector = std::chrono::duration<double, std::micro>(v1 - v0).count();
	double	usDeque = std::chrono::duration<double, std::micro>(d1 - d0).count();

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << count
			  << " elements with std::vector<int> : " << usVector << " us"
			  << std::endl;
	std::cout << "Time to process a range of " << count
			  << " elements with std::deque<int>  : " << usDeque << " us"
			  << std::endl;

	// For self-testing only, keep this commented out for submission:
	// std::cout << "Number of comparisons Vec: " << cmpVec << std::endl;
	// std::cout << "Number of comparisons Deq: " << cmpDeq << std::endl;
	
	return (0);
}