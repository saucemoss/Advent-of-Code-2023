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

struct rgb_count
{
	bool over_max()
	{
		return (r > 12 || g > 13 || b > 14);
	}

	rgb_count(std::string line)
	{
		for (int i = 0; i < strs.size(); i++)
		{
			std::string s = strs[i];
			std::size_t found = line.find(s);

			while (found != std::string::npos)
			{
				if (s == "red") r += std::stoi(line.substr(found -3, found-1));
				if (s == "green") g += std::stoi(line.substr(found - 3, found-1));
				if (s == "blue") b += std::stoi(line.substr(found - 3, found-1));
				line = line.replace(line.find(s), s.length(), "");
				found = line.find(s);
			}
		}
	}
	int r = 0, g = 0, b = 0;
	std::vector<std::string> strs = {
		"red","green","blue" };
};


void day2p1()
{
	std::ifstream infile("day2input.txt");
	std::string line;

	int sum_of_possible_games_ids = 0;

	while (std::getline(infile, line))
	{

		std::size_t find_colon = line.find(":");
		int game_id = std::stoi(line.substr(4, find_colon));
		bool over_rgb_count = false;
		std::cout << "\n-------------------------------------";
		std::cout << "\nID: " << game_id << std::endl;
		
		std::size_t find_semicolon = line.find(";");

		std::string first_subset = line.substr(find_colon + 1, find_semicolon - (find_colon + 1));
		std::cout << "\nsubset: " << first_subset;
		rgb_count rgb(first_subset);
		std::cout << "\nrgb: " << rgb.r << "," << rgb.g << "," << rgb.b;
		std::cout << "\npossible: " << !rgb.over_max();
		rgb.over_max() ? over_rgb_count = true : over_rgb_count = over_rgb_count;

		while (find_semicolon != std::string::npos)
		{
			line = line.substr(find_semicolon + 1, line.length());
			find_semicolon = line.find(";");

			std::string subset = line.substr(0, find_semicolon);
			std::cout << "\nsubset: " << subset;
			rgb_count rgb(subset);
			std::cout << "\nrgb: " << rgb.r << "," << rgb.g << "," << rgb.b;
			std::cout << "\npossible: " << !rgb.over_max();
			rgb.over_max() ? over_rgb_count = true : over_rgb_count = over_rgb_count;
		}

		if (!over_rgb_count)
		{
			sum_of_possible_games_ids += game_id;
		}

	}

	std::cout << "\n" << sum_of_possible_games_ids;
}

void day2p2()
{

}

int main() {

	//day1p1();
	//day1p2();
	//day2p1();
	day2p2();

	return 0;
}