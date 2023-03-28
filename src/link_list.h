#ifndef LEON_LINK_LIST_H
#define LEON_LINK_LIST_H
/*************************** Built-in Reference *******************************

 * The API is designed with 3 layers of abstraction/implementation with each
 * level getting closer to the underlying implementation. This is to allow
 * usage of the library in a simple way at level 1 while still allowing the
 * user to customize the library at different granularities at levels 2 and 3.



 ******************************* Level 1 **************************************


 * link_list(type, list_name)
 * ----------------------------------------------------------------------------
 * type 		-- type to be stored
 * list_name 	-- name of the list type
 * ----------------------------------------------------------------------------
 * Defines a linked list of whatever type you want and these functions:
 * 
 * list_name* list_name_create()					-- Create the list
 * void list_name_free(list_name* list)				-- Free the list
 * void list_name_push(list_name* list, type value) -- Pushes value onto list
 * type list_name_pop(list_name* list, uint index)	-- Pop + return list[index]
 * type list_name_get(list_name* list, uint index)	-- Return list[index]
 * ----------------------------------------------------------------------------


 * link_list_w_print(type, list_name, spec)
 * ----------------------------------------------------------------------------
 * type is the type to be stored
 * list_name is the name of the list type
 * spec is the specifier character to use for printf (e.g. d = int, f = float )
 * ----------------------------------------------------------------------------
 * Same as above but additionally defines the following function:
 * 
 * void list_name_print(list_name* list)			-- Prints the list
 * ----------------------------------------------------------------------------


 ******************************* Level 2 **************************************


 * def_link_list_node(type, node_name)
 * ----------------------------------------------------------------------------
 * type 		-- type to be stored
 * node_name	-- name of the node type
 * ----------------------------------------------------------------------------
 * Defines a new node type called node_name that stores a value of the type 
 * requested and a pointer to another node. The struct has 2 members:
 * 
 * type value;
 * node_name* next;
 * ----------------------------------------------------------------------------


 * def_link_list(type, list_name, node_name)
 * ----------------------------------------------------------------------------
 * type 		-- type to be stored
 * list_name 	-- name of the list type
 * node_name	-- type name of the nodes to use
 * ----------------------------------------------------------------------------
 * Defines a new linked list type called list_name that uses node_name nodes
 * to store elements of the type requested. The struct has 2 members:
 * 
 * node_name head;
 * node_name* tail;
 * ----------------------------------------------------------------------------
 

 * link_list_base_functions(type, list_name, node_name)  
 * ----------------------------------------------------------------------------
 * type 		-- type to be stored
 * list_name 	-- type name of the list to use
 * node_name	-- type name of the nodes to use
 * ----------------------------------------------------------------------------
 * Defines a collection of standard functions that create basic input and
 * output capabilities for a list called list_name that uses nodes called
 * node_name to store values of the type specified. The signatures of these
 * functions are listed here:
 * 
 * list_name* list_name_create()					-- Create the list
 * void list_name_free(list_name* list)				-- Free the list
 * void list_name_push(list_name* list, type value) -- Pushes value onto list
 * type list_name_pop(list_name* list, uint index)	-- Pop + return list[index]
 * type list_name_get(list_name* list, uint index)	-- Return list[index]
 * ----------------------------------------------------------------------------               


 ******************************* Level 3 **************************************


 * ----------------------------------------------------------------------------
 * link_list_create_function(fun_name, list_name)
 *
 * link_list_free_function(fun_name, list_name, node_name)
 *
 * link_list_push_function(fun_name, type, list_name, node_name)
 *
 * link_list_pop_function(fun_name, type, list_name, node_name)
 *
 * link_list_get_function(fun_name, list_name, node_name)
 *
 * link_list_print_function(fun_name, list_name, node_name, spec)


 *************************** End of Reference ********************************/


/**************************** Implementation *********************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef uint
	#define uint unsigned int
#endif

/* stringify a list of arguments including commas */
#ifndef str_m
	#define str_m(...) #__VA_ARGS__
#endif

/******************************* Level 1 *************************************/

#define link_list(type, name)												\
	def_link_list_node(type, name##_node)									\
	def_link_list(type, name, name##_node) 									\
	link_list_base_functions(type, name, name##_node)

#define link_list_w_print(type, name, spec)									\
	link_list(type, name)													\
	link_list_print_function(name##_print, name, name##_node, spec)	

/*****************************************************************************/



/******************************* Level 2 *************************************/

#define def_link_list_node(type, node_name)									\
	typedef struct node_name												\
	{																		\
		type value;															\
		struct node_name* next; 											\
	} node_name ;															\

#define def_link_list(type, list_name, node_name)							\
	typedef struct 															\
	{																		\
		node_name head;														\
		node_name * tail;													\
	} list_name;															\

#define link_list_base_functions(type, list_name, node_name)				\
	link_list_create_function(list_name##_create, list_name)				\
	link_list_free_function(list_name##_free, list_name, node_name)			\
	link_list_push_function(list_name##_push, type, list_name, node_name)	\
	link_list_pop_function(list_name##_pop, type, list_name, node_name)		\
	link_list_get_function(list_name##_get, type, list_name, node_name)

/*****************************************************************************/



/******************************* Level 3 *************************************/

#define link_list_create_function(fun_name, list_name)						\
	list_name* fun_name()													\
	{																		\
		list_name* list = malloc(sizeof(list_name));						\
		list->tail = 0;														\
		return list;														\
	}

#define link_list_free_function(fun_name , list_name, node_name)			\
	void fun_name(list_name* list)											\
	{																		\
		if(&list->head == list->tail || list->tail == 0)					\
		{																	\
			free(list);														\
			return;															\
		}																	\
		node_name * cur = list->head.next;									\
		node_name * next;													\
		while(cur != list->tail)											\
		{																	\
			next = cur->next;												\
			free(cur);														\
			cur = next;														\
		}																	\
		free(cur);															\
		free(list);															\
	}

#define link_list_push_function(fun_name, type, list_name, node_name)		\
	void fun_name(list_name* list, type value)								\
	{																		\
		if(list->tail == 0)													\
		{																	\
			list->head.value = value;										\
			list->tail = &list->head;										\
			return;															\
		}																	\
		list->tail->next = malloc(sizeof(node_name));						\
		list->tail = list->tail->next;										\
		list->tail->value = value;											\
	}

#define link_list_pop_function(fun_name, type, list_name, node_name) 		\
	type fun_name(list_name* list, uint index)								\
	{																		\
		type val = list->head.value;										\
		node_name* p = list->head.next;										\
																			\
		if(list->tail==0)													\
			return 0;														\
																			\
		if(list->tail == &list->head)										\
		{																	\
			if(index != 0)													\
				return 0;													\
			list->tail = 0;													\
			return val;														\
		}																	\
																			\
		if(index == 0)														\
		{																	\
			list->head.value = p->value;									\
			if(list->head.next == list->tail)								\
				list->tail = &list->head;									\
			else															\
				list->head.next = p->next;									\
			val = p->value;													\
			free(p);														\
		}																	\
		else																\
		{																	\
			node_name* o = &list->head;										\
			int i = 1;														\
			for(; i < index; i++)											\
			{																\
				if(p == list->tail)											\
					break;													\
				o = p;														\
				p = p->next;												\
			}																\
			if(p == list->tail)												\
				if(i < index)												\
					return 0;												\
				else 														\
					list->tail = o;											\
			else															\
				o->next = p->next;											\
			val = p->value;													\
			free(p);														\
		}																	\
																			\
		return val;															\
	}

#define link_list_get_function(fun_name, type, list_name, node_name) 		\
	type fun_name(list_name* list, uint index)								\
	{																		\
		if(list->tail==0)													\
			return 0;														\
																			\
		if(list->tail == &list->head || index == 0)							\
			return list->head.value;										\
																			\
		node_name* p = list->head.next;										\
		int i = 1;															\
		for(;i < index; i++)												\
		{																	\
			if(p == list->tail)												\
				break;														\
			p = p->next;													\
		}																	\
																			\
		if(i < index)														\
			return 0;														\
		else 																\
			return p->value;												\
	}

#define link_list_print_function(fun_name, list_name, node_name, spec) 		\
	void fun_name(list_name* list)											\
	{																		\
		if(list->tail == 0)													\
		{																	\
			printf("[]\n");													\
			return;															\
		} 																	\
		else if(list->tail == &list->head)									\
		{																	\
			printf(str_m([%spec]), list->head.value);						\
			return;															\
		}																	\
		node_name* p = list->head.next;										\
		printf(str_m([%spec), list->head.value);							\
		while(p != list->tail)												\
		{																	\
			printf(str_m(, %spec), p->value);								\
			p = p->next;													\
		}																	\
		printf(str_m(, %spec]\n), p->value);								\
	}

/*****************************************************************************/
#endif