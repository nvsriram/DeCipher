#ifndef CAESAR_HPP_
#define CAESAR_HPP_

#include<iostream>
#include<string>
#include<cassert>
#include<cctype>

#include "clearscreen.hpp"
#include "dictionary.hpp"

//Caesar cipher
namespace caesar
{
	//function to check if valid plaintext
	bool is_valid_plaintext (const std::string plaintext)
	{
		for(std::size_t i{}; plaintext[i] != '\0'; ++i)
		{
			if(!(std::isprint(plaintext[i])||std::isspace(plaintext[i])))	//invalid if not printable character or space
				return false;
		}
		return true;
	}

	//function to check if valid ciphertext
	bool is_valid_ciphertext (const std::string ciphertext)
	{
		for(std::size_t i{}; ciphertext[i] != '\0'; ++i)
		{
			if(!(std::isprint(ciphertext[i])||std::isspace(ciphertext[i])))	//invalid if not printable character or space
				return false;
		}
		return true;
	}

	//function to encode plaintext to ciphertext
	std::string encode (std::string plaintext, unsigned long key)
	{
		std::size_t i{};	//loop variable
		key %= 26;	//make key in terms of 26 alphabets
		plaintext.resize(plaintext.length() - 1);	//resize to remove the last unwanted character

		//if alphabet then add by the key after taking care of circular mapping
		//if not, no change is done to it
		for(; i < plaintext.length(); ++i)
		{
			if(isalpha(plaintext[i]))	//if alphabet
			{
				if(isupper(plaintext[i]))	//if uppercase
				{
					if((static_cast<std::size_t>(plaintext[i]) + key) > 'Z')	//if it exceeds Z
					{
						plaintext[i] = plaintext[i] + key - 26; //cycles back to A
					}
					else
					{
						plaintext[i] += key;
					}
				}
				else	//if lowercase
				{
					if((static_cast<std::size_t>(plaintext[i]) + key) > 'z')	//if it exceeds z
					{
						plaintext[i] = plaintext[i] + key - 26;	//cycles back to a
					}
					else
					{
						plaintext[i] += key;
					}
				}
			}
		}

		assert(is_valid_ciphertext(plaintext));
		return plaintext;
	}

	//function to decode ciphertext to plaintext
	std::string decode (std::string ciphertext, unsigned long key)
	{
		std::size_t i{};	//loop variable
		key %= 26;	//makes key in terms of 26 alphabets

		for(i = 0; i < ciphertext.length(); ++i)
		{
			if(isalpha(ciphertext[i]))	//if alphabet
			{
				if(isupper(ciphertext[i]))	//if uppercase
				{
					if((static_cast<std::size_t>(ciphertext[i]) - key) < 'A')	//if it exceeds A
					{
						ciphertext[i] = ciphertext[i] - key + 26;	//cycles back to Z
					}
					else
					{
						ciphertext[i] -= key;
					}
				}
				else
				{
					if((static_cast<std::size_t>(ciphertext[i]) - key) < 'a')	//if it exceeds a
					{
						ciphertext[i] = ciphertext[i] - key + 26;	//cycles back to z
					}
					else
					{
						ciphertext[i] -= key;
					}
				}
			}
		}

		assert(is_valid_plaintext(ciphertext));
		return ciphertext;
	}

	//function to implement dictionary for bruteforce plaintext cracking
	void bruteforce_dictionary (std::string plain)
	{
		plain.resize(plain.length() - 1);	//resize to remove last unwanted character

		//load hashmap from dictionary
		bool loaded = dictionary::load(DICTIONARY);
		std::cout<<"Loading dictionary . . ."<<std::endl;
		sleep(2);
		if(!loaded)
		{
			std::cout<<"Could not load dictionary"<<std::endl;
		}

		std::cout<<"Loading possible deciphered passwords . . ."<<std::endl;
		sleep(2);
		ClearScreen(5);
		bool exists{true};
		std::size_t possible{};

		//spell check deciphered plaintext for key from 0 to 26
		for(std::size_t i{}; i < 26; ++i)
		{
			std::string str{};
			str.append(caesar::decode(plain, i));

			// Check word's spelling
			bool flag = dictionary::check(str);

			// Print word if it matches with word in dictionary
			if (flag)
			{
				if(exists)
					std::cout<<"Possible deciphered passwords: "<<std::endl;
				exists = false;
				++possible;
				std::cout<<possible<<".\""<<str<<"\" for key ="<<i<<std::endl;
			}

			// Prepare for next word
			str.clear();
		}

		//if no possible passwords
		if(!possible)
			std::cout<<"Sorry, no possible passwords found."<<std::endl;

		//unload dictionary from hashmap
		bool unloaded = dictionary::unload();
		if(!unloaded)
			std::cout<<"Could not unload."<<std::endl;

	}

	//function to showcase caesar cipher
	void caesar (void)
	{
		std::string caesar_str;
		std::cout<<"You have chosen Caesar cipher."<<std::endl;
		sleep(1);
		std::cout<<"Enter your plaintext: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(std::cin, caesar_str, '\n');
		std::cout<<"Enter your whole* number key: ";
		long int caesar_key{};
		std::cin>>caesar_key;
		std::cout<<"Thank you."<<std::endl;
		sleep(2);
		ClearScreen(5);

		std::string plain{};
		std::string cipher{};

		//special case to call bruteforce dictionary
		if(caesar_key == 0)
		{
			std::cout<<"You have chosen to bruteforce the ciphertext."<<std::endl;
			bruteforce_dictionary(caesar_str);
		}

		//normal caesar cipher
		else
		{
			plain.append(caesar::encode(caesar_str, caesar_key));
			std::cout<<"The encoded text is: \""<<plain<<"\""<<std::endl;

			cipher.append(caesar::decode(plain, caesar_key));
			std::cout<<"The decoded text is: \""<<cipher<<"\""<<std::endl;
		}
		plain.erase();
		cipher.erase();
	}

};	//namespace caesar


#endif
