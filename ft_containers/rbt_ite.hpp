/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_ite.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini.42nice.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:55:43 by dzuntini          #+#    #+#             */
/*   Updated: 2022/09/26 16:35:39 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_ITERATOR_HPP
# define BINARY_SEARCH_TREE_ITERATOR_HPP

#include "utils.hpp"
#include "Iterator.hpp"

namespace ft
{
	template <typename T>
	class RBT_ite
	{	
		public :
			typedef 		 ft::random_access_iterator_tag				iterator_category;
			typedef	typename ft::iterator_traits<T *>::value_type 		value_type;
			typedef typename ft::iterator_traits<T *>::reference 		reference;
			typedef typename ft::iterator_traits<T *>::pointer			pointer;
			typedef typename ft::iterator_traits<T *>::difference_type	difference_type;

		private:
		
			typedef RBT_Node<value_type> * 								node_pointer;
			typedef RBT_Node<const value_type> * 						const_node_pointer;
			
			node_pointer _node;
			node_pointer _min;
			node_pointer _max;


		public :
			
			RBT_ite(): _node(u_nullptr), _min(u_nullptr), _max(u_nullptr) {}
			explicit RBT_ite(node_pointer node, node_pointer min, node_pointer max) :_node(node), _min(min), _max(max){}
		RBT_ite(const RBT_ite &cpy) {*this = cpy;}
			
			RBT_ite&	operator=(const RBT_ite &oth){
				_node = oth._node;
				_min = oth._min;
				_max=oth._max;
				return (*this);
			}
			
			virtual ~RBT_ite() { }

			inline operator RBT_ite<const T>() const {
				return RBT_ite<const T>((const_node_pointer) this->_node, (const_node_pointer) this->_min, (const_node_pointer) this->_max);
			}


 			node_pointer node() const {return (_node);}
			 bool operator==(const RBT_ite & it) {return (_node == it._node);}
			 bool operator!=(const RBT_ite & it) {return (_node != it._node);}
			reference operator*() const {return *(_node->value);}
			pointer operator->() const {return _node->value;}

			RBT_ite& operator++() {
				if (!_node)
					_node = _min;
				else
					_node = _node->next();
				return *this;
			}

			 RBT_ite operator++(int) {
				RBT_ite<value_type> temp = *this;
				if (!_node)
					_node = _min;
				else
					_node = _node->next();
				return temp;
			}

			 RBT_ite & operator--() {
				if (!_node)
					_node = _max;
				else
					_node = _node->prev();
				return *this;
			}

			 RBT_ite operator--(int) {
				RBT_ite<value_type> temp = *this;
				if (!_node)
					_node = _max;
				else
					_node = _node->prev();
				return temp;
			}
			

	};
}
#endif