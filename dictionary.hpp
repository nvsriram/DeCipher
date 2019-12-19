#ifndef DICTIONARY_HPP_
#define DICTIONARY_HPP_

#include<string.h>
#include<cstring>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<cctype>
#include<cassert>

#define LENGTH 45	//length of longest word
#define DICTIONARY "large.txt"	//dictionary file
#define N 26	//max index for hashtable (alphabet)

namespace dictionary
{
	//Function prototypes
	std::size_t hash (const std::string word);
	bool unload (void);
	bool load (const std::string dictionary);
	bool check (const std::string word);
	std::size_t size (void);
	bool is_equal (const std::string str1, const std::string str2);

	//Class node for linked list
	class node
	{
	private:
		std::string word;
		node *next;
	public:
		node (void);
		~node (void);
		std::string get_word (void) const;
		node *get_next (void) const;
		void set_next (node *p_next);
		void set_word (std::string p_word);
	};

	//Class definitions
	node::node (void):next{nullptr}
	{}
	node::~node (void)
	{}
	std::string node::get_word (void) const
	{
		return this->word;
	}
	node *node::get_next (void) const
	{
		return this->next;
	}
	void node::set_next (node *p_next)
	{
		this->next = p_next;
	}
	void node::set_word (std::string p_word)
	{
		word.clear();
		word.replace(0, p_word.length(), p_word);
	}

	//Dictionary functions

	node *hashtable[N]{};	//pointer to hashtable
	std::size_t words{};	//variable to store number of loaded words

	//function to hash word to respective index
	std::size_t hash (const std::string word)
	{
		return static_cast<std::size_t>(std::tolower(word[0]) - 'a');
	}

	//function to load words from file into hashtable
	bool load (const std::string dictionary)
	{
		//initialize hashtable
		for(std::size_t i{}; i < N; ++i)
		{
			hashtable[i] = nullptr;
		}

		//opens dictionary for reading
		std::ifstream file;
		file.open(dictionary, std::ios::in);

		//if file is empty
		if(!file)
		{
			unload();
			return false;
		}

		std::string word;	//buffer for word

		while(file >> word)
		{

			node *temp{nullptr};
			temp = new(std::nothrow) node;

			//if out of memory
			if(temp == nullptr)
			{
				unload();
				return false;
			}

			temp->set_word(word);	//set temp's word to word
			std::size_t index{hash(word)};	//index for hashed word

			//insert into hashtable
			//if empty hashtable[index], them make it index
			if (hashtable[index] == nullptr)
			{
				hashtable[index] = temp;
				temp->set_next(nullptr);
			}
			//else attach to first
			else
			{
				temp->set_next(hashtable[index]);
				hashtable[index] = temp;
				temp = nullptr;
			}
			//increment words added
			++words;
		}
		file.close();
		return true;
	}

	//function to return number of loaded words
	std::size_t size (void)
	{
		return words;
	}

	//function to check if word exists in hashtable
	bool check (const std::string word)
	{
		//assign checknode to respective hashtable[hash]
		std::size_t index = hash(word);
		node *checknode{hashtable[index]};

		while(checknode != nullptr)
		{
			//checks if word and checknode match ignoring case
			if(is_equal(word,checknode->get_word()))
					return true;
			//moves checknode to its next node
			checknode = checknode->get_next();
		}
		checknode = nullptr;
		//if word not found
		return false;
	}

	//function to unload dictionary
	bool unload (void)
	{
		//iterate from 0 till N-1 index
		for(std::size_t i{}; i < N; ++i)
		{
			node *cursor{};
			cursor = hashtable[i];
			//delete every node in the hashtable[index]
			while(cursor != nullptr)
			{
				node *temp = cursor;
				cursor = cursor->get_next();
				delete temp;
				temp = nullptr;
			}
			//remove dangling pointers
			cursor = nullptr;
			hashtable[i] = nullptr;
		}
		return true;
	}

	//function to compare if 2 strings are equal (case-insensitive)
	bool is_equal (const std::string str1, const std::string str2)
	{
		//if unequal lengths then unequal strings
		if(str1.length() != str2.length())
			return false;

		//if unequal when same case then unequal strings
		for(std::size_t i{}; i < str1.length(); ++i)
			if(std::tolower(str1[i]) != std::tolower(str2[i]))
				return false;
		return true;
	}

};	//namespace dictionary

#endif
