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
				if (s == "red") r += std::stoi(line.substr(found - 3, found - 1));
				if (s == "green") g += std::stoi(line.substr(found - 3, found - 1));
				if (s == "blue") b += std::stoi(line.substr(found - 3, found - 1));
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

	std::ifstream infile("day2input.txt");
	std::string line;
	int power_sum = 0;

	while (std::getline(infile, line))
	{

		int game_red = 0, game_green = 0, game_blue = 0;

		std::size_t find_colon = line.find(":");
		int game_id = std::stoi(line.substr(4, find_colon));

		std::size_t find_semicolon = line.find(";");

		std::string first_subset = line.substr(find_colon + 1, find_semicolon - (find_colon + 1));
		rgb_count rgb(first_subset);

		game_red = rgb.r;
		game_green = rgb.g;
		game_blue = rgb.b;

		while (find_semicolon != std::string::npos)
		{
			line = line.substr(find_semicolon + 1, line.length());
			find_semicolon = line.find(";");

			std::string subset = line.substr(0, find_semicolon);
			rgb_count rgb(subset);

			rgb.r > game_red ? game_red = rgb.r : true;
			rgb.g > game_green ? game_green = rgb.g : true;
			rgb.b > game_blue ? game_blue = rgb.b : true;
		}

		std::cout << "\nGame " << game_id << " top values" << "\n";
		std::cout << "Red: " << game_red << "\n";
		std::cout << "Green: " << game_green << "\n";
		std::cout << "Blue: " << game_blue << "\n";

		power_sum += game_red * game_green * game_blue;
	}

	std::cout << "Sum of all powers: " << power_sum;
}

bool check_for_symbol_neighbour(std::vector<std::vector<char>>& arr, int y, int x)
{
	// Check top
	if (y - 1 >= 0 && !isdigit(arr[y - 1][x]) && arr[y - 1][x] != '.')
		return true;

	// Check top-right
	if (y - 1 >= 0 && x + 1 < arr[y].size() && !isdigit(arr[y - 1][x + 1]) && arr[y - 1][x + 1] != '.')
		return true;

	// Check right
	if (x + 1 < arr[y].size() && !isdigit(arr[y][x + 1]) && arr[y][x + 1] != '.')
		return true;

	// Check bottom-right
	if (y + 1 < arr.size() && x + 1 < arr[y].size() && !isdigit(arr[y + 1][x + 1]) && arr[y + 1][x + 1] != '.')
		return true;

	// Check bottom
	if (y + 1 < arr.size() && !isdigit(arr[y + 1][x]) && arr[y + 1][x] != '.')
		return true;

	// Check bottom-left
	if (y + 1 < arr.size() && x - 1 >= 0 && !isdigit(arr[y + 1][x - 1]) && arr[y + 1][x - 1] != '.')
		return true;

	// Check left
	if (x - 1 >= 0 && !isdigit(arr[y][x - 1]) && arr[y][x - 1] != '.')
		return true;

	// Check top-left
	if (y - 1 >= 0 && x - 1 >= 0 && !isdigit(arr[y - 1][x - 1]) && arr[y - 1][x - 1] != '.')
		return true;

	return false;
}

std::vector<int> get_digit_neighbour_coords(std::vector<std::vector<char>>& arr, int y, int x)
{
	int neighbour_count = 0;
	std::vector<int> n_coords;

	// Check top-left
	if (y - 1 >= 0 && x - 1 >= 0 && isdigit(arr[y - 1][x - 1]))
	{
		neighbour_count++;
		n_coords.push_back(y - 1);
		n_coords.push_back(x - 1);
	}

	// Check top
	if (y - 1 >= 0 && isdigit(arr[y - 1][x]))
	{
		neighbour_count++;
		n_coords.push_back(y - 1);
		n_coords.push_back(x);
	}

	// Check top-right
	if (y - 1 >= 0 && x + 1 < arr[y].size() && isdigit(arr[y - 1][x + 1]))
	{
		neighbour_count++;
		n_coords.push_back(y - 1);
		n_coords.push_back(x + 1);
	}

	// Check bottom-left
	if (y + 1 < arr.size() && x - 1 >= 0 && isdigit(arr[y + 1][x - 1]))
	{
		neighbour_count++;
		n_coords.push_back(y + 1);
		n_coords.push_back(x - 1);
	}

	// Check bottom
	if (y + 1 < arr.size() && isdigit(arr[y + 1][x]))
	{
		neighbour_count++;
		n_coords.push_back(y + 1);
		n_coords.push_back(x);
	}

	// Check bottom-right
	if (y + 1 < arr.size() && x + 1 < arr[y].size() && isdigit(arr[y + 1][x + 1]))
	{
		neighbour_count++;
		n_coords.push_back(y + 1);
		n_coords.push_back(x + 1);
	}

	// Check left
	if (x - 1 >= 0 && isdigit(arr[y][x - 1]))
	{
		neighbour_count++;
		n_coords.push_back(y);
		n_coords.push_back(x - 1);
	}

	// Check right
	if (x + 1 < arr[y].size() && isdigit(arr[y][x + 1]))
	{
		neighbour_count++;
		n_coords.push_back(y);
		n_coords.push_back(x + 1);
	}

	return n_coords;

}

int get_number_from_coords(std::vector<std::vector<char>>& arr, int& y, int& x)
{
	std::string num_str = "";
	int temp_x = x;
	while (temp_x < arr[y].size() && std::isdigit(arr[y][temp_x]))
	{
		num_str.push_back(arr[y][temp_x]);
		temp_x += 1;
	}

	temp_x = x - 1;

	while (temp_x > 0 && std::isdigit(arr[y][temp_x]))
	{
		std::string::iterator it = num_str.begin();
		num_str.insert(it, arr[y][temp_x]);
		temp_x -= 1;
	}

	std::cout << "\n" << num_str;
	return std::stoi(num_str);

}

void day3p1()
{
	//load char 2d array
	std::vector<std::vector<char>> arr;
	std::ifstream infile("day3input.txt");
	std::string line;
	std::vector<char> line_values;
	int total = 0;

	while (std::getline(infile, line))
	{
		std::vector<char> line_values;
		for (char& x : line)
		{
			line_values.push_back(x);
		}
		arr.push_back(line_values);
	}

	//nested for
	for (int y = 0; y < arr.size(); y++)
	{
		bool has_symbol = false;
		for (int x = 0; x < arr[y].size(); x++)
		{
			std::string num_string;
			int digit_counter = 0;

			while ((x + digit_counter < arr[y].size()) && isdigit(arr[y][x + digit_counter]))
			{
				if (!has_symbol) has_symbol = check_for_symbol_neighbour(arr, y, x + digit_counter);
				num_string.push_back(arr[y][x + digit_counter]);
				digit_counter++;
			}
			x += digit_counter;
			if (!num_string.empty() && has_symbol)
			{
				total += std::stoi(num_string);
				has_symbol = false;
			}
		}

	}

	std::cout << "\ntotal: " << total << std::endl;

}

void day3p2()
{
	//load char 2d array
	std::vector<std::vector<char>> arr;
	std::ifstream infile("day3input.txt");
	std::string line;
	std::vector<char> line_values;
	int total = 0;

	while (std::getline(infile, line))
	{
		std::vector<char> line_values;
		for (char& x : line)
		{
			line_values.push_back(x);
		}
		arr.push_back(line_values);
	}

	//nested for
	for (int y = 0; y < arr.size(); y++)
	{
		for (int x = 0; x < arr[y].size(); x++)
		{
			if (arr[y][x] == '*')
			{
				std::vector<int> neighbours = get_digit_neighbour_coords(arr, y, x);

				if (neighbours.size() == 4)
				{
					for (int i = 0; i < neighbours.size(); i += 2)
					{
						std::cout << neighbours[i] << ", " << neighbours[i + 1] << ":";
					}
					std::cout << "\n";
					/*std::cout << "\n\n" << "COORDS: " << neighbours[0] <<"," << neighbours[1] << "--" << neighbours[2] << "," << neighbours[3];
					total += get_number_from_coords(arr, neighbours[0], neighbours[1]) * get_number_from_coords(arr, neighbours[2], neighbours[3]);*/
				}
			}
		}
	}

	std::cout << "\ntotal: " << total << std::endl;


	//find gear
	//check if 2 neighbours exist - returns two sets of y,x
	//get full number returns number based on y,x
	//multipy all

}

int main() {

	//day1p1();
	//day1p2();
	//day2p1();
	//day2p2();
	//day3p1();
	day3p2();

	return 0;
}