#pragma once

/**
* @file dictionary.h
* @brief Contains the definition of custom class to mange a Python-like dictionary object.
*/

#include "vector"
#include "string"

//! Namespace with definitions of custom data structures
namespace custom_structures
{
	/**
	* @brief Class created to copy Python's dictionary type (avoids the use of tuple).
	*
	* Class Dictionary is collection of keys values, used to store data values like a map, which, unlike other data types which hold only a single value as an element.
	*
	* Developement comment: Nesting of Dictionary instances as "values" of a "key" is not currently supported.
	*/
	class Dictionary
	{
	public:
		/**
		* @brief Constructor of the Dictionary class (default).
		*/
		Dictionary() {};

		/**
		* @brief Destructor of the Dictionary class
		*/
		~Dictionary()
		{
			m_keys.clear();
			for (auto value_list : m_values)
				value_list.clear();
		};

		/** 
		* @brief Method to check if the dictionary contains the given key
		* @param key [in] the key to find
		* @return Returns the index of the key in the container if the key exists in the dictionaryl otherwise it returns 0
		*/
		int contains(std::string key) const
		{
			auto it = std::find(m_keys.begin(), m_keys.end(), key);
			if (it == m_keys.end())
				return int(-1);
			else
				return int(it - m_keys.begin());
		};

		/** 
		* @brief Method to find the number of keys the dictionary holds.
		* @return returns the number of keys that are stored in the dictionary.
		*/
		int size()
		{
			return (int)m_keys.size();
		};

		/**
		* @brief Method to find the number of values assigned to a key of the dictionary.
		* @return returns a non-negative number if the key contains the given key, or a negative number if the key does not exist in the dictionary
		*/
		int size(std::string key)
		{
			int idx = this->contains(key);
			if (idx < 0)
				return int(-1);
			else
				return (int)(m_values.at(idx)).size();
		};

		/**
		* @brief Method to insert key with value in the dictionary or add a value to an existing key
		* @param key [in] dictionary key
		* @param value [in] value of the key in the dictionary 
		*/
		void insert(std::string key, std::string value)
		{
			int idx = this->contains(key);
			if (idx < 0) {
				m_keys.push_back(key);
				m_values.push_back({ value });
			}
			else {
				(m_values.at(idx)).push_back(value);
			}
		};

		/** @brief Method to insert (copy) keys and their values from an existing dictionary
		* @param source [in] source dictionary to copy
		*/
		void insert(const Dictionary* source)
		{
			for (auto key : source->keys())
			{
				int idx = this->contains(key);
				if (idx < 0)
					this->remove(key);
				for (auto value : source->value(key))
					this->insert(key, value);
			}
		};

		/**
		* @brief Method to remove a key and the values assigned to it from the dictionary
		* @param key [in] dictionary key
		*/
		void remove(std::string key)
		{
			int idx = this->contains(key);
			if (idx >= 0) {
				m_keys.erase(m_keys.begin() + idx);
				m_values.erase(m_values.begin() + idx);
			}
		};

		/**
		* @brief Method to replace the value of a key with the given value
		* @param key [in] key identifier
		* @param value [in] replacement value
		*/
		void replace(std::string key, std::string value)
		{
			int idx = this->contains(key);
			if (idx >= 0) {
				m_values.at(idx) = { value };
			}
		};

		/**
		* @brief Method to retrieve the keys held in the dictionary
		* @return returns a vector with keys that are stored in the dictionary.
		*/
		std::vector<std::string> keys() const
		{
			return m_keys;
		};

		/**
		* @brief Method to retriee the values help in the dictionary
		* @return returns a vector of value lists (list per key) held in the dictionary
		*/
		std::vector<std::vector<std::string>> values() const
		{
			return m_values;
		};

		/**
		* @brief Method to retrieve the value(s) assigned to the given key in the dictionary
		* @param key [in] key identifier
		* @return returns a list of values assigned to a key in the dictionary
		*/
		std::vector<std::string> value(std::string key) const
		{
			int idx = this->contains(key);
			if (idx >= 0) {
				return m_values.at(idx);
			}
		};

	private:

		std::vector<std::string> m_keys; //!< vector with keys 
		std::vector<std::vector<std::string>> m_values; //!< vector with value(s) assigned to a key; level 0: number of keys; level 1: number values assigned to a key
		//nesting dictionaries?

	};
};
