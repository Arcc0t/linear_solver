#include "solver.hpp"
#include <cstring>


template <typename T>
int main_body(bool human)
{
	auto data = read_data<T>(std::cin, human);
	if (!data.second) {
		std::cerr << "input error\n";
		return 1;
	}
	solve_system(data.first);
	return 0;
}

int main(int argc, char** argv)
{
	bool human_format = false;
	bool float_solution = false;
	
	for (int i = 1; i < argc; ++i){
		if (std::strcmp(argv[i], "-H") == 0)
			human_format = true;
		if (std::strcmp(argv[i], "--float") == 0)
			float_solution = true;
	}

	if (!float_solution){
		return main_body<int64_t>(human_format);	
	} else {
		return main_body<long double>(human_format);	

	}
}
