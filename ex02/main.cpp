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

/* Ein einzelnes Token: nur Ziffern, passt in int. */
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

/* Erster Durchgang: nur pruefen und zaehlen, nichts speichern. */
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

/* Datenverwaltung: argv -> Container. Wird MITGEMESSEN. */
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

/* "Before:" direkt aus argv ausgeben, damit kein zusaetzlicher Container
   noetig ist und die Messung fuer beide Container fair bleibt. */
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

	/* ---- std::vector: Befuellen + Sortieren, beides gemessen ---------- */
	std::chrono::steady_clock::time_point	v0
		= std::chrono::steady_clock::now();
	fill(argc, argv, vec);
	PmergeMe::sortVector(vec);
	std::chrono::steady_clock::time_point	v1
		= std::chrono::steady_clock::now();

	/* ---- std::deque: dasselbe ---------------------------------------- */
	std::chrono::steady_clock::time_point	d0
		= std::chrono::steady_clock::now();
	fill(argc, argv, deq);
	PmergeMe::sortDeque(deq);
	std::chrono::steady_clock::time_point	d1
		= std::chrono::steady_clock::now();

	printSequence("After: ", vec);

	double	usVector = std::chrono::duration<double, std::micro>(v1 - v0).count();
	double	usDeque = std::chrono::duration<double, std::micro>(d1 - d0).count();

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << count
			  << " elements with std::vector<int> : " << usVector << " us"
			  << std::endl;
	std::cout << "Time to process a range of " << count
			  << " elements with std::deque<int>  : " << usDeque << " us"
			  << std::endl;

	/* Nur zum Selbsttest, fuer die Abgabe auskommentiert lassen:
	std::cout << "Number of comparisons: " << PmergeMe::comparisons() << std::endl;
	*/
	return (0);
}