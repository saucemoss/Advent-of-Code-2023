#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string replace_words_with_numbers(std::string* str)
{
	std::vector<std::string> strs = {
		"zero","one","two","three","four","five","six","seven","eight","nine" };

	std::string output(*str);

	for (int i = 0; i < strs.size(); i++)
	{
		std::string s = strs[i];
		std::size_t found = output.find(s);

		while (found != std::string::npos)
		{
			output = output.replace(output.find(s) + 2, s.length() - 3, std::to_string(i));
			found = output.find(s);
		}
	}

	return output;
}

void day1p1()
{
	std::ifstream infile("day1input.txt");
	std::string line;
	std::vector<char> line_values;
	int calibration_sum = 0;
	while (std::getline(infile, line))
	{
		for (char& x : line)
		{
			if (isdigit(x))
			{
				line_values.push_back(x);
			}
		}
		std::string calibration_str;
		calibration_str.push_back(line_values[0]);
		calibration_str.push_back(line_values[line_values.size() - 1]);

		int num = std::stoi(calibration_str);
		calibration_sum += num;
		line_values.clear();
	}

	std::cout << calibration_sum;
}

void day1p2()
{
	std::ifstream infile("day1input.txt");
	std::string line;
	std::vector<char> line_values;
	int calibration_sum = 0;
	while (std::getline(infile, line))
	{
		std::string output = replace_words_with_numbers(&line);
		for (char& x : output)
		{
			if (isdigit(x))
			{
				line_values.push_back(x);
			}
		}
		std::string calibration_str;
		calibration_str.push_back(line_values[0]);
		calibration_str.push_back(line_values[line_values.size() - 1]);

		int num = std::stoi(calibration_str);
		calibration_sum += num;
		line_values.clear();
	}

	std::cout << calibration_sum << std::endl;
}


int main() {

	day1p1();
	day1p2();

	return 0;
}