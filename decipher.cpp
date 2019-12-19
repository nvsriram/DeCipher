#include<iostream>
#include<stdlib.h>
#include<string>
#include<unistd.h>
#include<limits>
#include<iomanip>
#include<stdio.h>

#include "clearscreen.hpp"
#include "asciiarmor.hpp"
#include "caesar.hpp"
#include "vigenere.hpp"
#include "dictionary.hpp"

void print_table (void);

int main (void)
{

	char choice{};
	do {
			ClearScreen(5);
			print_table();
			std::cout<<"Enter your choice: ";
			int option{};
			std::cin>>option;

			while(option != 1 && option != 2 && option != 3 && option != 4)
				{
					std::cout<<"Processing . . ."<<std::endl;
					sleep(1);
					if(option == -1)
					{
						ClearScreen(5);
						std::cout<<"You have chosen to exit the program. Thank you for your time!";
						exit(-1);
					}

					std::cout<<"Invalid option. Try again . . ."<<std::endl<<"Enter -1 to exit the program."<<std::endl;
					std::cin>>option;
				}
			std::cout<<"Processing . . ."<<std::endl;
			sleep(1);
			ClearScreen(5);
			switch(option)
			{
				case 1:
				{
					//ASCII armor
					asciiarmor::asciiarmor();
					break;
				}
				case 2:
				{
					//Caesar cipher
					caesar::caesar();
					break;
				}
				case 3:
				{
					//Vigenere cipher
					vigenere::vigenere();
					break;
				}
				case 4:
				{
					//Exit
					std::cout<<"You have chosen to exit the program. Thank you for your time!";
					sleep(2);
					exit(0);
					break;
				}
				default:
					std::cout<<"How did you get so far?"<<std::endl;
			}
			std::cout<<std::endl<<"Would you like to continue?"<<std::endl;
			std::cout<<"Press 'y' to continue and 'n' to exit: ";
			std::cin>>choice;
			sleep(1);

		} while((choice == 'y') || (choice == 'Y'));
	if((choice != 'y') && (choice != 'Y'))
		std::cout<<std::endl<<"You have chosen to exit the program. Thank you for your time!";

	return 0;
}


//prints choice table
void print_table (void)
{
	std::cout<<"Welcome to DeCipher!"<<std::endl;
	std::cout<<std::left<<"_"<<std::setfill('_')<<std::setw(30)<<"_"<<std::endl;
	std::cout<<std::right<<"|="<<std::setfill('=')<<std::setw(9)<<"="<<std::setw(20)<<"=|"<<std::endl;
	std::cout<<std::left<<"|: "<<std::setfill(' ')<<std::setw(6)<<"Choice"<<" | "<<std::setw(16)<<"Tasks"<<" :|"<<std::endl;
	std::cout<<std::right<<"|="<<std::setfill('=')<<std::setw(9)<<"|"<<std::setw(20)<<"=|"<<std::endl;
	std::cout<<std::left<<"|: "<<std::setfill(' ')<<std::setw(6)<<"1"<<" | "<<std::setw(16)<<"ASCII Armor"<<" :|"<<std::endl;
	std::cout<<"|: "<<std::setw(6)<<"2"<<" | "<<std::setw(16)<<"Caesar Cipher"<<" :|"<<std::endl;
	std::cout<<"|: "<<std::setw(6)<<"3"<<" | "<<std::setw(16)<<"Vigenere Cipher"<<" :|"<<std::endl;
	std::cout<<"|: "<<std::setw(6)<<"4"<<" | "<<std::setw(16)<<"Exit program"<<" :|"<<std::endl;
	std::cout<<std::right<<"|_"<<std::setfill('_')<<std::setw(9)<<"|"<<std::setw(20)<<"_|"<<std::endl;
	std::cout<<"*"<<std::setfill('*')<<std::setw(30)<<"*"<<std::endl;
}
