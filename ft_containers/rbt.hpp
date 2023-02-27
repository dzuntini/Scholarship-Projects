/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini.42nice.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:55:48 by dzuntini          #+#    #+#             */
/*   Updated: 2022/09/26 21:14:35 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

#include "./utils.hpp"
#include "./rbt_ite.hpp"
#include "./stack.hpp"

/*Arbre binaire , pour un node N si N+1 > N il ira a droite , sinon si N+1 <= N il ira a gauche. Si aucun node a cet endroit il se creer sinon il continue a descendre*/
/*Recreation de Red Black Tree*/
/*http://www.aoc.nrao.edu/php/tjuerges/ALMA/STL/html-3.4.6/stl__8h-source.html*/

namespace ft
{
	template <class T, class Compare = ft::less<T>,  class Allocator = std::allocator<T> >
	class RBT
	{
		public :
			
			typedef T															value_type;
			typedef Compare														value_compare;
			typedef Allocator													allocator_type;
			typedef ft::RBT_Node<T>												node_type;
			typedef typename Allocator::template rebind<node_type>::other		node_allocator;
			typedef	typename node_allocator::pointer							node_pointer;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef std::ptrdiff_t												difference_type;
			typedef ft::RBT_ite<T>												iterator;
			typedef ft::RBT_ite<const T>										const_iterator;
			typedef	ft::reverse_iterator<iterator>								reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>						const_reverse_iterator;


		private :
		
			allocator_type				_valuealloc;
			node_allocator				_nodealloc;
			value_compare 				_comp;
			node_pointer				_root;
			size_t						_size;
		
		public :

			RBT(const Compare & comp = value_compare(), const allocator_type & a = allocator_type()) : _valuealloc(a), _nodealloc(node_allocator()), _comp(comp), _root(u_nullptr), _size(0) {}
			
			RBT(const RBT & cpy) {
				if (empty())
					clear();
				_nodealloc = cpy._nodealloc;
				_valuealloc = cpy._valuealloc;
				_comp = cpy._compare;
				_root = u_nullptr;
				_size = 0;
				if (!cpy.empty())
					this->insert(cpy.cbegin(), cpy.cend());
			}	
			
			~RBT (){this->clear();}
			
			RBT& operator=(const RBT &oth) 
			{
    			if (empty())
					clear();
					_nodealloc = oth._nodealloc;
					_valuealloc = oth._valuealloc;
					_comp = oth._comp;
					_root = u_nullptr;
					_size = 0;
				if (oth.empty())
					return(*this);
				this->insert(oth.cbegin(), oth.cend());
				return *this;
			}
			
			iterator end() {return (iterator(u_nullptr, this->_min(), this->_max()));}
			const_iterator end() const {return (iterator(u_nullptr, this->_min(), this->_max()));}
			const_iterator cend() const {return (iterator(u_nullptr, this->_min(), this->_max()));}
			iterator begin() {return (iterator(this->_min(), this->_min(), this->_max()));}
			const_iterator begin() const {return (iterator(this->_min(), this->_min(), this->_max()));}
			const_iterator cbegin() const {return (iterator(this->_min(), this->_min(), this->_max()));}
			reverse_iterator rbegin() {return (reverse_iterator(this->end()));}
			const_reverse_iterator rbegin() const {return (reverse_iterator(this->end()));}
			const_reverse_iterator rcbegin() const {return (reverse_iterator(this->end()));}
			reverse_iterator rend() {return (reverse_iterator(this->begin()));}
			const_reverse_iterator rend() const {return (const_reverse_iterator(this->begin()));}
			const_reverse_iterator rcend() const {return (const_reverse_iterator(this->begin()));}

			node_pointer search(const value_type & value, node_pointer node) const {
				if(!node)
					return u_nullptr;
				if (this->_comp((value.first), node->value->first))
					return this->search(value, node->left);
				if (this->_comp((node->value->first), value.first))
					return this->search(value, node->right);
				return node;
			}

			iterator find(const value_type & value) {
				node_pointer ret = search(value, _root);
				if (ret == u_nullptr)
					return end();
				return iterator(ret, _min(), _max());
			}

			const_iterator find(const value_type & value) const {
				node_pointer ret = search(value, _root);
				if (ret == u_nullptr)
					return end();
				return iterator(ret, _min(), _max());
			}
			
			ft::pair<iterator, bool> insert(const value_type & value) {
				node_pointer new_node = this->_insert_into(value);
				if (!new_node) {
					return ft::make_pair(this->find(value), false);
				}
				return ft::make_pair(iterator(new_node, this->_min(), this->_max()), true);
			}

			iterator insert(iterator hint, const value_type & value) {
				node_pointer pos = hint.node();
				while (1) {
					if (!pos || *(pos->value) == value)
						break;
					if (!_comp((pos->value->first), value.first))
						pos = pos->left;
					else
						pos = pos->right;
				}
				if (pos)
					return (iterator(pos, _min(), _max()));
				node_pointer new_node = _insert_into(value);
				return (iterator(new_node, _min(), _max()));
			}
			
			template <class InputIt> void insert(typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type first, InputIt last) {
				while (first != last)
				{
					_insert_into(*first);
					first++;
				}
			}

			void erase(iterator it) {erase(*it);}

			size_t erase(const value_type & value) {
				node_pointer ret = search(value, _root);
				if (ret != u_nullptr)
					_erase_node(ret);
				return (ret != u_nullptr);
			}

			iterator erase(iterator first, iterator last) {
				ft::stack<const value_type> todel;
				while(first != last && first != end())
				{
					todel.push(*first);
					first++;
				}
				while (todel.size() != 0) 
				{
					erase(todel.top());
					todel.pop();
				}
				return (last);
			}

			size_t size() const {
				return (_size);
			}
			
			size_t max_size() const {
				size_t div = sizeof(node_pointer) * 4 + sizeof(value_type);
				div = (div / 8) * 8;
				return (std::numeric_limits<size_t>::max() / div);
			}
			
			bool empty() const {
				return (_size == 0);
			}

			value_compare value_comp() const {
				return (this->_comp);
			}
			
			void clear() {
				this->clear_tree();
			}

			iterator lower_bound(const value_type & value) {
				iterator last = this->end();
				for (iterator first = this->begin(); first != last; ++first) {
					if (!this->_comp(*(first), value)) {
						return (first);
					}
				}
				return (last);
			}

			const_iterator lower_bound(const value_type & value) const{
				const_iterator last = this->cend();
				for (const_iterator first = this->cbegin(); first != last; ++first) {
					if (!this->_comp(*(first), value)) {
						return (first);
					}
				}
				return (last);
			}

			const_iterator clower_bound(const value_type & value) const{
				const_iterator last = this->cend();
				for (const_iterator first = this->cbegin(); first != last; ++first) {
					if (!this->_comp(*(first), value)) {
						return (first);
					}
				}
				return (last);
			}

			iterator upper_bound(const value_type & value) {
				iterator last = this->end();
				for (iterator first = this->begin(); first != last; ++first){
					if (this->_comp(value, *(first))) {
						return (first);
					}
				}
				return (last);
			}

			const_iterator upper_bound(const value_type & value) const {
				const_iterator last = this->cend();
				for (const_iterator first = this->cbegin(); first != last; ++first) {
					if (this->_comp(value, *(first))) {
						return (first);
					}
				}
				return (last);
			}

			const_iterator cupper_bound(const value_type & value) const {
				const_iterator last = this->cend();
				for (const_iterator first = this->cbegin(); first != last; ++first) {
					if (this->_comp(value, *(first))) {
						return (first);
					}
				}
				return (last);
			}

			void swap(RBT &other) {
				std::swap(this->_root, other._root);
				std::swap(this->_size, other._size);
				std::swap(this->_nodealloc, other._nodealloc);
				std::swap(this->_valuealloc, other._valuealloc);
				std::swap(this->_comp, other._comp);
			}

			ft::pair<iterator, iterator> equal_range(const value_type & value) {
				return (ft::make_pair(this->lower_bound(value), this->upper_bound(value)));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const value_type & value) const {
				return (ft::make_pair(this->clower_bound(value), this->cupper_bound(value)));
			}

			ft::pair<const_iterator, const_iterator> cequal_range(const value_type & value) const {
				return (ft::make_pair(this->clower_bound(value), this->cupper_bound(value)));
			}
			
			allocator_type get_allocator() const {
				return (this->_valuealloc);
			}

		protected:
			node_pointer _min() {
				if (!this->_root)
					return (u_nullptr);
				return this->_root->min();
			}

			node_pointer _min() const {
				if (!this->_root)
					return (u_nullptr);
				return this->_root->min();
			}
			
			node_pointer _max() {
				if (!this->_root)
					return (u_nullptr);
				return this->_root->max();
			}
			
			node_pointer _max() const {
				if (!this->_root)
					return (u_nullptr);
				return this->_root->max();
			}
			
			void _rotate_right(node_pointer	node) {
				if (!node || !node->left) 
					return;
				node_pointer y = node->left;
				node->left = y->right;
				if (node->left)
					node->left->parent = node;
				if (!node->parent)
					this->_root = y;
				else if (node == node->parent->left)
					node->parent->left = y;
				else
					node->parent->right = y;
				y->parent = node->parent;
				node->parent = y;
				y->right = node;
			}

			void _rotate_left(node_pointer	node) {
				if (!node || !node->right) 
					return;
				node_pointer y = node->right;
				node->right = y->left;
				if (node->right)
					node->right->parent = node;
				if (!node->parent)
					this->_root = y;
				else if (node == node->parent->left)
					node->parent->left = y;
				else
					node->parent->right = y;
				y->parent = node->parent;
				node->parent = y;
				y->left = node;
			}

			node_pointer _insert_into(const value_type & value) {
				if (this->search(value, this->_root))
					return (u_nullptr);
				node_pointer new_node = this->_create_node(value);
				if (!this->_root) {
					this->_root = new_node;
				} else {
					node_pointer current = this->_root;
					while (1) {
						if (this->_comp((current->value->first), (new_node->value->first))) {
							if (!current->right) {
								new_node->parent = current;
								current->right = new_node;
								break;
							} else
								current = current->right;
						} else {
							if (!current->left) {
								new_node->parent = current;
								current->left = new_node;
								break;
							} else {
								current = current->left;
							}
						}
					}
				}
				this->_insert_rebalance(new_node);
				this->_size++;
				return (new_node);
			}
			
			void _insert_rebalance(node_pointer node) {
				node_pointer parent = node->parent;
				if (!parent) {
					node->isblack = true;
					return;
				} else if (parent->isblack) {
					return;
				}
				node_pointer grandparent = u_nullptr;
				node_pointer uncle = u_nullptr;
				if (node && node->parent)
					grandparent = node->parent->parent;
				if (grandparent) {
					if (node->parent == grandparent->left)
						uncle = grandparent->right;
					else
						uncle = grandparent->left;
				}
				if (!parent->isblack && (uncle && !uncle->isblack)) {
					parent->isblack = true;
					uncle->isblack = true;
					grandparent->isblack = false;
					this->_insert_rebalance(grandparent);
				} else if (grandparent && parent == grandparent->left) {
					if (node == parent->right) {
						node = parent;
						this->_rotate_left(parent);
					}
					parent->isblack = true;
					if (grandparent) {
						grandparent->isblack = false;
						this->_rotate_right(grandparent);
					}
				} else {
					if (node == parent->left) {
						node = parent;
						this->_rotate_right(parent);
					}
					parent->isblack = true;
					if (grandparent) {
						grandparent->isblack = false;
						this->_rotate_left(grandparent);
					}
				}
			}

			void _transplant(node_pointer where, node_pointer what) {
				if (!where->parent)
					this->_root = what;
				else if (where == where->parent->left)
					where->parent->left = what;
				else
					where->parent->right = what;
				if (what)
					what->parent = where->parent;
			}

			void _erase_node(node_pointer & node) {
				node_pointer x = u_nullptr, y = node, tmp = u_nullptr;
				bool y_last_color_black = y->isblack;
				if (!node->left && !node->right) {
					tmp = this->_create_node(*(node->value));
					tmp->isblack = true;
					this->_transplant(node, tmp);
					x = tmp;
				} else if (!node->left) {
					x = node->right;
					this->_transplant(node, node->right);
				} else if (!node->right){
					x = node->left;
					this->_transplant(node, node->left);
				} else {
					y = node->prev();
					x = y->left;
					if (!x) {
						tmp = this->_create_node(*(node->value));
						tmp->isblack = true;
						tmp->parent = y;
						y->left = tmp;
						x = tmp;
					}
					y_last_color_black = y->isblack;
					if (y->parent != node) {
						this->_transplant(y, x);
						y->left = node->left;
						if (y->left)
							y->left->parent = y;
					}
					this->_transplant(node, y);
					y->isblack = node->isblack;
					y->right = node->right;
					if (y->right)
						y->right->parent = y;
				}
				this->_delete_node(node);
				this->_size--;
				if (y_last_color_black)
					this->_erase_rebalance(x);
				if (tmp) {
					this->_transplant(tmp, NULL);
					this->_delete_node(tmp);
				}
			}
			
			void _erase_rebalance(node_pointer node) {
				node_pointer sibling;
				while (node != this->_root && node->isblack) {
					if (node == node->parent->left) {
						sibling = node->parent->right;
						if (!sibling->isblack) {
							sibling->isblack = true;
							node->parent->isblack = false;
							this->_rotate_left(node->parent);
							sibling = node->parent->right;
						}
						if (sibling && (!sibling->left || sibling->left->isblack) && (!sibling->right || sibling->right->isblack)) {
							sibling->isblack = false;
							node = node->parent;
						} else {
							if (sibling->right->isblack) {
								sibling->left->isblack = true;
								sibling->isblack = false;
								this->_rotate_right(sibling);
								sibling = node->parent->right;
							}
							sibling->isblack = node->parent->isblack;
							node->parent->isblack = true;
							sibling->right->isblack = true;
							this->_rotate_left(node->parent);
							node = this->_root;
						}
					} else {
						sibling = node->parent->left;
						if (!sibling->isblack) {
							sibling->isblack = true;
							node->parent->isblack = false;
							this->_rotate_right(node->parent);
							sibling = node->parent->right;
						}
						if (sibling && (!sibling->right || sibling->right->isblack) && (!sibling->left || sibling->left->isblack)) {
							sibling->isblack = false;
							node = node->parent;
						} else {
							if (sibling->left->isblack) {
								sibling->right->isblack = true;
								sibling->isblack = false;
								this->_rotate_left(sibling);
								sibling = node->parent->left;
							}
							sibling->isblack = node->parent->isblack;
							node->parent->isblack = true;
							sibling->left->isblack = true;
							this->_rotate_right(node->parent);
							node = this->_root;
						}
					}
				}
				node->isblack = true;
			}

			void clear_tree() {
				this->_destroy(this->_root);
				this->_root = u_nullptr;
				this->_size = 0;
			}

			void _destroy(node_pointer node) {
				if (!node)
					return;
				this->_destroy(node->left);
				this->_destroy(node->right);
				this->_delete_node(node);
			}

			node_pointer	_create_node(const value_type & value) {
				node_pointer new_node = this->_nodealloc.allocate(1);
				this->_nodealloc.construct(new_node, RBT_Node<T>());
				new_node->value = this->_valuealloc.allocate(1);
				this->_valuealloc.construct(new_node->value, value);
				return (new_node);
			}

			void _delete_node(node_pointer node) {
				if (!node)
					return;
				this->_valuealloc.destroy(node->value);
				this->_valuealloc.deallocate(node->value, 1);
				this->_nodealloc.destroy(node);
				this->_nodealloc.deallocate(node, 1);
			}

	};
	template<class Content, class Compare, class Alloc> void swap(const  RBT<Content, Compare, Alloc> & lhs, const  RBT<Content, Compare, Alloc> & rhs) {
		lhs.swap(rhs);
	}
}

#endif