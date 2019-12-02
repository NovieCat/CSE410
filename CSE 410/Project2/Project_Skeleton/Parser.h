/*
 * File    : Parser.h
 *
 * Header for the Parser class for Project2.
 *
 * Class   : Parser.h
 * Impl    : Parser.cpp
 * Created : Jan 10, 2012
 * Author  : CSE410 Spring 2012
 *
 * Notes   : Do NOT modify this class
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <string>
class Parser
{
public:
	static const std::string BinPath;
	static const std::string UsrBinPath;
	Parser();
	virtual ~Parser();
	std::string FindPath(const std::string cmd, const std::string searchPath);
};

#endif /* PARSER_H_ */
