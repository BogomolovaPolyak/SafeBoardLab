/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScannerClass.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:35:28 by natali            #+#    #+#             */
/*   Updated: 2021/11/05 07:20:59 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_CLASS_HPP
#define SCANNER_CLASS_HPP

#include "SearchThreadClass.hpp"

class Scanner
{

using clock_t = std::chrono::high_resolution_clock;
using second_t = std::chrono::duration<double, std::ratio<1> >;

private:

	std::atomic<int> *_errors;
	std::atomic<int> *_processedFiles;
	std::chrono::time_point<clock_t> _execTime;
	SearchThread target[3];

public:

	Scanner(std::string str);
	~Scanner() {delete _errors; delete _processedFiles;}
	int getProcessedfiles() {return *_processedFiles;}
	int getErrors() {return *_errors;}
	void init();
	// void stopWatch();
	void printReport();
};

#endif