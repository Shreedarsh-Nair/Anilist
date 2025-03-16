#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <set>

int write_file(std::set<std::string> ani_list);

int main(){
	short int opt;
	std::string name;
	std::set<std::string> a_list;

	std::ifstream ifile("Animelist.txt");
	if(!ifile){
		std::time_t timestamp;
		time(&timestamp);
			
		std::ofstream errfile("Error.txt", std::ios::app);
		if(!errfile){
			std::cout << "Couldn't open error file.";
			return -1;
		}
		errfile << ctime(&timestamp) << " Error opening file to read.";
		errfile.close();

		return -1;
	}
	
	while(std::getline(ifile, name)){
		a_list.insert(name);
	}

	ifile.close();

	std::cout << std::endl;
	std::cout << "There are currently " << a_list.size() << " Animes in your list\n\n";
	std::cout << "0 : Add anime\n";
	std::cout << "1 : Delete anime\n";
	std::cout << "2 : Display list\n";
	std::cout << "3 : Random anime\n";
	std::cout << "4 : Quit\n";
	
	while(1){
		std::cout << "Enter your choice: ";
		std::cin >> std::ws;
		std::cin >> opt;
		switch(opt){
			case 0:
				std::cout << "Enter the name of anime: ";
				std::cin >> std::ws;
				std::getline(std::cin, name);
				a_list.insert(name);
				std::cout << "\nAnime inserted successfully\n\n";

				write_file(a_list);	

				break;

			case 1:
				std::cout << "Enter name of anime: ";
				std::cin >> std::ws;
				std::getline(std::cin, name);
				a_list.erase(name);
				std::cout << "\nAnime removed successfully\n\n";

				write_file(a_list);

				break;

			case 2:
			{
				int i = 1;
				
				std::cout << std::endl;
				for(std::string anime : a_list){
					std::cout << i << ". "  << anime << std::endl;
					i++;
				}
				std::cout << std::endl;
			}
			
				break;

			case 3:
			{
				if(a_list.empty()){
					std::cout << "\nNo anime found in list.\n\n";
					break;
				}

				std::random_device seed;
				std::mt19937 gen(seed());
				std::uniform_int_distribution<int> num(1, a_list.size());

				std::cout << std::endl;
				std::cout << "Watch " << "\"" << *std::next(a_list.begin(), num(gen)) << "\"" << "\n\n";
		
				break;
			}

			case 4:
				return 0;
		
			default:
				std::cout << "Invalid option. Please try again!\n";
				break;
		}
	}
}

int write_file(std::set<std::string> ani_list){
	std::ofstream ofile("Animelist.txt");

	if(!ofile){
		std::time_t timestamp;
		time(&timestamp);
		
		std::ofstream errfile("Error.txt", std::ios::app);
		if(!errfile){
			std::cout << "Couldn't open error file.";
			return -1;
		}
		errfile << ctime(&timestamp) << " Error opening file to write.";
		errfile.close();
		
		return -1;
	}		
	for(std::string anime : ani_list){
		ofile << anime << std::endl;
	}
	
	ofile.close();
	return 0;
}
