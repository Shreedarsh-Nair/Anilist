#include <iostream>
#include <fstream>
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

	std::cout << "0 : Add anime\n";
	std::cout << "1 : Delete anime\n";
	std::cout << "2 : Display list\n";
	std::cout << "3 : Quit\n";
	
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

				if(write_file(a_list)){
					std::cout << "Error in writing to file." << std::endl;
				}	

				break;

			case 1:
				std::cout << "Enter name of anime: ";
				std::cin >> std::ws;
				std::getline(std::cin, name);
				a_list.erase(name);

				if(write_file(a_list)){
					std::cout << "Error in writing to file." << std::endl;
				}

				break;

			case 2:
			{
				int i = 1;
				
				for(std::string anime : a_list){
					std::cout << i << ". "  << anime << std::endl;
					i++;
				}
			}
			
				break;
			
			case 3:
				return 0;
		
			default:
				std::cout << "Invalid option. Please try again!";
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
