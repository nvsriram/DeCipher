#ifndef VIGENERE_HPP_
#define VIGENERE_HPP_

#include<iostream>
#include<string>
#include<cassert>
#include<cctype>

//Vigenére cipher
namespace vigenere
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

	//function to check if valid alphabet keyword
	std::size_t check_valid (const std::string word)
	{
	    std::size_t i{};
	    for (; i < word.length(); ++i)
	    {
	        if (!isalpha(word[i]))
	        {
	            return 1;
	        }
	    }
	    return 0;
	}

	//function to shift plaintext based on keyword
	std::size_t shift (const char c)
	{
	    if (isupper(c))
	    {
	        return static_cast<std::size_t>(c - 'A');
	    }
	    else
	    {
	        return static_cast<std::size_t>(c - 'a');
	    }
	}

	//function to encode plaintext to ciphertext
	std::string encode (std::string plaintext, std::string key)
	{
		std::size_t i{}, j{};	//loop variables

		plaintext.resize(plaintext.length() - 1);	//resize to remove the last unwanted character

		//if alphabet then add by the shift as per key after taking care of circular mapping
		//if not, no change is done to it
		for(; i < plaintext.length(); ++i)
		{
			if(isalpha(plaintext[i]))	//if alphabet
			{
				if(j == key.length())	//if j reaches end of key, reset j
					j = 0;

				//if upper and exceeds 'Z' or lower and exceeds 'z'
				if ((isupper(plaintext[i]) && (static_cast<std::size_t>(plaintext[i]) + shift(key[j]) > 'Z')) ||
					(islower(plaintext[i]) && (static_cast<std::size_t>(plaintext[i]) + shift(key[j]) > 'z')))
			    {
					plaintext[i] = plaintext[i] + shift(key[j]) - 26;	//cycle back to 'A' or 'a' respectively
	            }
	            else
	            {
	            	plaintext[i] += shift(key[j]);
				}
				++j;
			 }
		}

		assert(is_valid_ciphertext(plaintext));
		return plaintext;
	}

	//function to decode ciphertext to plaintext
	std::string decode (std::string ciphertext, std::string key)
	{

		std::size_t i{}, j{};	//loop variables

		for(; i < ciphertext.length(); ++i)
		{
			if(isalpha(ciphertext[i]))	//if alphabet
			{
				if(j == key.length())	//if j reaches end of key, reset j
					j = 0;

				//if upper and exceeds 'A' or lower and exceeds 'a'
				if ((isupper(ciphertext[i]) && (static_cast<std::size_t>(ciphertext[i]) - shift(key[j]) < 'A')) ||
					(islower(ciphertext[i]) && (static_cast<std::size_t>(ciphertext[i]) - shift(key[j]) < 'a')))
			    {
					ciphertext[i] = ciphertext[i] - shift(key[j]) + 26;	//cycle back to 'Z' or 'z' respectively
	            }
	            else
	            {
	            	ciphertext[i] -= shift(key[j]);
				}
				++j;
			 }
		}

		assert(is_valid_plaintext(ciphertext));
		return ciphertext;
	}

	//function to showcase vigenére cipher
	void vigenere (void)
	{
		std::string vig_str;
		std::cout<<"You have chosen Vigenére cipher."<<std::endl;
		sleep(1);
		std::cout<<"Enter your plaintext: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(std::cin, vig_str, '\n');
		std::cout<<"Enter your alphabetic keyword: ";
		std::string vig_key{};
		std::cin>>vig_key;
		std::cout<<"Thank you."<<std::endl;
		sleep(2);
		ClearScreen(5);

		std::string vigplain{};
		vigplain.append(vigenere::encode(vig_str, vig_key));
		std::cout<<"The encoded text is: \""<<vigplain<<"\""<<std::endl;
		std::string vigcipher{};
		vigcipher.append(vigenere::decode(vigplain, vig_key));
		std::cout<<"The decoded text is: \""<<vigcipher<<"\""<<std::endl;

		vigplain.erase();
		vigcipher.erase();
	}

};	//namespace vigenere

#endif
