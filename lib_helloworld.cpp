//
// Created by User on 25.02.2018.
//
#include <string>
#include "lib_helloworld.h"

std::string version()
{
	return std::to_string(PROJECT_VERSION_MAJOR)
		   + "." + std::to_string(PROJECT_VERSION_MINOR)
		   + "." + std::to_string(PROJECT_VERSION_PATCH);
}

