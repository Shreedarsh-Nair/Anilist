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
				{
					std::cout << "Enter the name of anime: ";
					std::cin >> std::ws;
					std::getline(std::cin, name);
					a_list.insert(name);
	
					std::ofstream ofile("Animelist.txt", std::ios::trunc);
					if(!ofile){
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

					for(std::string a_name : a_list){
						ofile << a_name << std::endl;
					}

					ofile.close();
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
		ofile << anime;
	}
	
	ofile.close();
	return 0;
}
