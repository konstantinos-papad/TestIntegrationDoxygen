#pragma once

/**
* @file tree_structure.h
* @brief Contains the definition of custom class to manage a tree - data structure
*/

#include "vector"
#include "string"
#include "dictionary.h"

//! Namespace with definitions of custom data structures
namespace custom_structures
{
	/**
	* @brief A container to store and handle data organised in a hierarchical form.
	* 
	* Class TreeStructure has been constructed to enable the organisation of data in a hierarchical form. 
	* The class is provided in a template to enable the classification of node types according to a custom type enumerator.
	* 
	* Developement comment: expand template to control the kind "value" is stored in the instance.
	*/
	template <typename node_t>
	class TreeStructure
	{
	public:

		/**
		* @brief Constructor of the TreeStructure class.
		* @param node_type [in] type of the node to construct
		* @param node_level [in] the count of edges on the path from the root node to the constructed node
		*/
		TreeStructure(const node_t node_type, const int node_level)
		{
			m_level = node_level;
			m_node_type = node_type;
			m_attributes = new custom_structures::Dictionary();
			m_value = 0;
			m_value_len = 0;
		};

		/**
		* @brief Constructor of the TreeStructure class.
		* @param node_type [in] type of the node to construct
		* @param node_level [in] the count of edges on the path from the root node to the constructed node
		* @param node_value [in] value to assign to node
		*/
		TreeStructure(const node_t node_type, const int node_level, std::string node_value)
		{
			m_level = node_level;
			m_node_type = node_type;
			m_attributes = new custom_structures::Dictionary();
			m_value_len = node_value.size() + 1;
			m_value = new char[m_value_len];
			strcpy_s(m_value, m_value_len, node_value.c_str());
		};

		/**
		* @brief Destructor of the TreeStructure class.
		*/
		~TreeStructure()
		{
			for (auto children : m_children)
				delete children;
			m_children.clear();
			delete m_attributes;
			if (m_value)
				delete[] m_value;
		};

		/** 
		* @brief Method to check if the node is the topmost node of the tree.
		* @return returns true if this node is the topmost of the tree and false otherwise
		*/
		bool is_root()
		{
			return (m_level == 0);
		};

		/** 
		* @brief Method to check if the node has any children.
		* @return returns true if this node has children and false otherwise
		*/
		bool is_leaf()
		{
			return (m_children.size() < 1);
		};

		/** 
		* @brief Method for adding a child to this node.
		* @param node [in] object of type "TreeStructure"
		*/
		void add_child(TreeStructure* node)
		{
			m_children.push_back(node);
		};

		/**
		* @brief Method to create/add attributes to this node.
		* @param attribute_name [in] attribute name
		* @param attribute_value [in] attribute value
		*/
		void add_attribute(std::string attribute_name, std::string attribute_value) 
		{
			m_attributes->insert(attribute_name, attribute_value);
		};

		/**
		* @brief Method to replace the values assigned to an attribute of this node.
		* @param attribute_name [in] identifier of the attribute
		* @param attribute_value [in] replacement value
		*/
		void replace_attribute(std::string attribute_name, std::string attribute_value)
		{
			m_attributes->replace(attribute_name, attribute_value);
		};

		/** 
		* @brief Method to find the number of children that are nested at the next level within this node.
		* @return returns the number of children nodes that are nested at the next level within this node
		*/
		int number_of_children()
		{
			return (int)m_children.size();
		};

		/** 
		* @brief Method to retrieve a (child) node nested in the current from it index (0-based).
		* @param node_idx [in] 0-based index of the "child" node in the container
		* @return returns a copy of the requested "child" node if the index is valid and 0 otherwise
		*/
		TreeStructure* get_child(int node_idx = -1)
		{
			if (m_children.size() < 1)
				return 0;
			else {
				if (node_idx < 0)
					return m_children.back();
				else if (node_idx < m_children.size())
					return m_children.at(node_idx);
				else
					return 0;
			}
		};

		/** 
		* @brief Method for giving read access to this node's children
		* @return Vector with children nodes
		*/
		std::vector<TreeStructure*> get_children() const
		{
			return m_children;
		}

		/** 
		* @brief Method to retrieve the level of this node.
		* @return returns the count of edges on the path from the root node to this node (the root node has m_level = 0)
		*/
		int get_level()
		{
			return m_level;
		};		

		/**
		* @brief Method to get the type of this instance.
		* @return Returns the type of this instance.
		*/
		node_t get_type() const
		{
			return m_node_type;
		};

		/**
		* @brief Method to get the value of a node, when the node is a "leaf".
		* @return Returns the value of a node value if the node is a "leaf" and 0 if the node is not a leaf or a value has not been assigned to the node.
		*/
		const char* get_value() const
		{
			return m_value;
		};

		/**
		* @brief Method to get the value of a "child"'s node of the given type.
		* @param node_type [in] Type of node to look for.
		* @return Returns the value of a node, if the node is a "leaf" and 0 if there is no node of the specified type, or a value has not been assigned to the node. 
		*/
		const char* get_value(node_t node_type) const
		{
			for (auto node : m_children) {
				if (node->get_type() == node_type) {
					return node->get_value();
				}
			}
			return 0;
		}

	private:

		int m_level; //!< the count of edges on the path from the root node to this node; the root node has m_level = 0
		node_t m_node_type; //!< type of configuration node
		std::vector<TreeStructure*> m_children; //!< nodes specified as children of the object node
		custom_structures::Dictionary* m_attributes; //!< attributes assigned to the node
		char* m_value; //!< value of node 
		size_t m_value_len; //!< number of characters in m_value
	};

	/*enum TreeStructureValueType
	{
		character = 1,
		integer = 2,
		float = 3,
		double = 4
	};*/
};
