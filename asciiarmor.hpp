#ifndef ASCIIARMOR_HPP_
#define ASCIIARMOR_HPP_

#include<iostream>
#include<cstring>
#include<cmath>
#include<cassert>
#include<cctype>

#include "clearscreen.hpp"

//ASCII armor encryption with base85
namespace asciiarmor
{
	//function to check if valid plaintext
	bool is_valid_plaintext (const char *str)
	{
		for(int i{}; str[i] != '\0'; ++i)
		{
			if(!(std::isprint(str[i])||std::isspace(str[i])))
				return false;
		}
		return true;
	}

	//function to check if valid ciphertext
	bool is_valid_ciphertext (const char *str)
	{
		for(int i{}; str[i] != '\0'; ++i)
		{
			if((str[i] < '!') || (str[i] > 'u'))
				return false;
		}
		return true;
	}

	//function to encode plaintext to ciphertext
	char *encode (char *plaintext, unsigned long key)
	{
		//Key Shuffle
		unsigned int i{0}, j{0}, k{0}, l{0} , m{0}, n{0};
		//initialize values of S with 0 to 256
		unsigned char S[256]{};
		for (k = 0; k < 256; ++k)
		{
			S[k] = k;
		}

		for(int var{0}; var < 256; ++var)
		{
			k = i % 64;
			j = (j + S[i] + ((key&(1L<<k))>>k))%256;
			unsigned char temp{};	//temporary variable to swap i and j
			temp = S[i];
			S[i] = S[j];
			S[j] = temp;
			i = (i + 1)%256;
		}

		unsigned int strl = std::strlen(plaintext);
		unsigned int X{0};
		X = 4 - (strl%4);	//number of null characters needed
		if(strl%4 != 0)
			strl += X;
		//make it multiple of 4 by filling rest with '\0'
		char *newplaintext = new(std::nothrow) char[strl]{};	//make space for extra characters

		//concatenate old plaintext onto new one of increased size
		for(n = 0; n < strl; ++n)
			if(n < std::strlen(plaintext))
				newplaintext[n] = plaintext[n];
			else
				newplaintext[n] = '\0';	//pad remaining space with null characters

		char R{0};
		int r{0};
		for(l = 0; l < strl; l++)
		{
			++i;
			i %= 256;
			j = (j + S[i])%256;
			char temp{};	//temporary variable to swap
			temp = S[i];
			S[i] = S[j];
			S[j] = temp;
			r = (S[i] + S[j])% 256;
			R = S[r];
			newplaintext[l] ^= R;
		}

		//ASCII armour
		i = j = k = l = m = n = 0;
		unsigned int dec{};	//integer to store the 4-byte changed char
		unsigned int newstrl = (strl/4)*5;
		char *str = new(std::nothrow) char[newstrl]{};
		k = 0;
		for(m = 0; m < strl/4; ++m)
		{
			//every 4 bytes(characters)
			for(j = 0; j < 4; ++j)
			{
				//receives a 8-bit binary from every character, shifts it to make space to append next 8-bit until a 32-bit integer is obtained
				dec += (static_cast<unsigned char>(newplaintext[k]))<<8*(3-j);
				++k;
			}

			//convert dec to base-85
			for(l = 0; l < 5; ++l)
			{
				str[k - l + m] = (dec % 85) + '!';
				dec /= 85;
			}
		}
		str[newstrl] = '\0';

		delete[] newplaintext;
		newplaintext = nullptr;

		assert(is_valid_ciphertext(str));
		return str;
	}

	//function to decode ciphertext to plaintext
	char *decode (char *ciphertext, unsigned long key)
	{

		//to decode, we first recreate R using key. Then convert every 5 base-85 character to integer(unsigned char).
		//then concatenate into a string and XOR that with R to get the plaintext back.
		unsigned int i{}, j{}, k{}, l{} , m{}, n{};
		//Makes string length a multiple of 5
		unsigned int strl{};
		strl = std::strlen(ciphertext);
		int X = 5 - (strl%5);
		if(strl%5 != 0)
		{
			strl += X;
		}
		ciphertext[strl] = '\0';
		unsigned int newstrl = (strl/5)*4;	//length of new string to be XOR should be (4/5)strl
		char* string = new(std::nothrow) char[newstrl]{};
		unsigned int dec{};

		for(m = 0; m < strl/5; ++m)
		{
			dec = 0;
			//every 5 bytes(characters)
			for(j = 0; j < 5; ++j)
			{
				//converts the base 85 into integer by multiplying (ciphertext[j] - '!')*85^(4-j) for MSB being the left most bit
				dec += static_cast<unsigned int>(ciphertext[k++] - '!')*pow(85,(4-j));
			}
			std::size_t BIT_MAX{255UL};	//0B1111111 used to get 8 bits of integer
			//convert dec to char and concatenate with str
			for(l = 0; l < 4; ++l)
			{
				string[n++] = static_cast<unsigned char>((dec>>8*(3-l))&(BIT_MAX));
			}
		}

		//Key Shuffle
		i = j = k = 0;
		//initialize values of S with 0 to 256
		unsigned char S[256]{};
		for (k = 0; k < 256; ++k)
		{
			S[k] = k;
		}

		for(int var{0}; var < 256; ++var)
		{
			k = i % 64;
			j = (j + S[i] + ((key&(1L<<k))>>k))%256;
			unsigned char temp{};	//temporary variable to swap i and j
			temp = S[i];
			S[i] = S[j];
			S[j] = temp;
			i = (i + 1)%256;
		}

		//XOR with R to retrieve original plaintext
		char R{0};
		int r{0};
		for(l = 0; l < newstrl; ++l)
		{
			++i;
			i %= 256;
			j = (j + S[i])%256;
			char temp{};	//temporary variable to swap
			temp = S[i];
			S[i] = S[j];
			S[j] = temp;
			r = (S[i] + S[j])% 256;
			R = S[r];
			string[l] ^= R;
		}
		string[l] = '\0';

		assert(is_valid_plaintext(string));
		return string;
	}

	//function to showcase ASCII armor
	void asciiarmor (void)
	{
		char ascii_str[255]{};
		std::cout<<"You have chosen ASCII armor."<<std::endl;
		sleep(1);
		std::cout<<"Enter your plaintext: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.getline(ascii_str, 255, '\n');
		ascii_str[strlen(ascii_str) - 1] = '\0';
		std::cout<<"Enter your numeric key: ";
		long int ascii_key{};
		std::cin>>ascii_key;
		std::cout<<"Thank you."<<std::endl;
		sleep(2);
		ClearScreen(5);

		char *ascii_plain{asciiarmor::encode(ascii_str, ascii_key)};
		std::cout<<"The encoded text is: \""<<ascii_plain<<"\""<<std::endl;
		char *ascii_cipher{asciiarmor::decode(ascii_plain, ascii_key)};
		std::cout<<"The decoded text is: \""<<ascii_cipher<<"\""<<std::endl;

		delete[] ascii_plain;
		delete[] ascii_cipher;
	}

};	//namespace asciiarmor

#endif




