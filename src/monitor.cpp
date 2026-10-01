#include <fstream>
#include <iostream>

#include "io.h"

word monitor::write(word value) {
	std::ofstream fout("monitor.io", std::ios::trunc);
	fout << value;
	std::cout << value << std::endl;
	return value;
}