/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini.42nice.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:56:48 by dzuntini          #+#    #+#             */
/*   Updated: 2022/09/27 14:51:03 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
#include "utils.hpp"
#include "rbt.hpp"
#include "rbt_ite.hpp"

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	/*Map Container en Key = Value , pas d'ordre precis dedans meme si possible de trier et chaque cle est associe a une valeur */
	class map
	{
		public:
			typedef Key     													key_type;
			typedef T       													mapped_type;
			typedef ft::pair<key_type, mapped_type> 							value_type;
			typedef Compare     												key_compare;
			typedef Alloc  														allocator_type;

			typedef typename allocator_type::reference   						reference;
			typedef typename allocator_type::const_reference 					const_reference;
			typedef typename allocator_type::pointer     						pointer;
			typedef typename allocator_type::const_pointer 						const_pointer;
			
			typedef typename ft::RBT<value_type,key_compare>::iterator 						iterator;
			typedef typename ft::RBT<value_type,key_compare>::const_iterator 				const_iterator;
			typedef typename ft::reverse_iterator<iterator>    								reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator> 							const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type 				difference_type;

			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, Alloc>;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				
				public:
					bool operator() (const value_type& x, const value_type& y) const { return (comp(x.first, y.first)); }
			};

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _comp(comp), _rbt() {}

			template <class InputIterator>
				map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
				: _alloc(alloc), _comp(comp), _rbt()
				{
					bool is_valid;
					if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
						throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
					this->_rbt.insert(first, last);
				}
			map(const map& x) : _alloc(x._alloc), _comp(x._comp), _rbt()
				{this->_rbt.insert(x.begin(), x.end());}
				
			~map() { this->clear(); }

			map& operator= (const map& x)
			{
				if (&x == this)
					return (*this);
				this->clear();
				this->insert(x.begin(), x.end());
				return (*this);
			}
			
			iterator begin() { return _rbt.begin(); }
			const_iterator begin() const { return _rbt.cbegin(); }
			iterator end() { return _rbt.end(); }
			const_iterator end() const	{ return _rbt.cend(); }

			reverse_iterator rbegin() { return _rbt.rbegin(); }
			const_reverse_iterator rbegin() const { return _rbt.rcbegin(); }
			reverse_iterator rend()	{ return _rbt.rend(); }
			const_reverse_iterator rend() const	{ return _rbt.rcend(); }

			bool empty() const { return (this->_rbt.empty()); }
			size_t size() const	{ return (this->_rbt.size()); }
			size_t max_size() const { return (_rbt.max_size()); }

			mapped_type& operator[] (const key_type& k)
			{
				iterator tmp = this->find(k);

				if (tmp == this->end())
					this->insert(ft::make_pair(k, mapped_type()));
				tmp = this->find(k);
				return ((*tmp).second);
			} 

			ft::pair<iterator,bool> insert (const value_type& val) { return (this->_rbt.insert(val)); }

			iterator insert (iterator position, const value_type& val)
			{
				return (_rbt.insert(position, val));
			}

			template <class InputIterator>
				void insert (InputIterator first, InputIterator last)
			{
				this->_rbt.insert(first, last);
			}
			
			void erase (iterator position)	{ this->_rbt.erase(position); }
			size_t erase (const key_type& k){return (this->_rbt.erase(ft::make_pair(k, mapped_type())));}
			iterator erase (iterator first, iterator last) {return (this->_rbt.erase(first, last));}
			
			void swap (map& x) { _rbt.swap(x._rbt); }

			void clear() { this->_rbt.clear(); }

			key_compare key_comp() const { return (key_compare()); }
			value_compare value_comp() const { return (value_compare(key_compare())); }

			iterator find (const key_type& k) { return (_rbt.find(ft::make_pair(k, mapped_type()))); }
			const_iterator find (const key_type& k) const { return (_rbt.find(ft::make_pair(k, mapped_type()))); }

			size_t count (const key_type& k) const
			{
				const_iterator beg = this->begin();
				const_iterator end = this->end();

				while (beg != end)
					if ((*(beg++)).first == k)
						return (1);
				return (0);
			}

			iterator lower_bound (const key_type& k)
			{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (_comp((*beg).first, k) == false)
						break;
					beg++;
				}
				return (beg);
			}

			const_iterator lower_bound (const key_type& k) const { return (const_iterator(this->lower_bound(k))); }

			iterator upper_bound (const key_type& k)
			{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (_comp(k, (*beg).first))
						break;
					beg++;
				}
				return (beg);
			}

			const_iterator upper_bound (const key_type& k) const { return (const_iterator(this->upper_bound(k))); }
			
			ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
			ft::pair<iterator, iterator> equal_range (const key_type& k) { return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
			
			RBT<value_type, Compare> g_rbt()
			{return(_rbt);}

		private:

			allocator_type                          	_alloc;
			Compare                                 	_comp;
			RBT<value_type, Compare> 	 				_rbt;

		template <typename K1, typename T1, typename C1, typename A1>
			friend bool 
			operator==(const map<K1, T1, C1, A1>&, 
				const map<K1, T1, C1, A1>&);
		
		template <typename K1, typename T1, typename C1, typename A1>
			friend bool 
			operator>(const map<K1, T1, C1, A1>&, 
				const map<K1, T1, C1, A1>&);

	
	friend bool operator==(const map &l, const map &r) {
		const_iterator it = l.begin();
		const_iterator it2 = r.begin();
		while (it != l.end())
			if (*it++ != *it2++)
				return 0;
		return (it2 == r.end());
	}

	friend bool operator!=(const map &l, const map &r) {return !(l == r);}
	friend bool operator<(const map &l, const map &r) {return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());}
	friend bool operator<=(const map &l, const map &r) {return (l < r || l == r);}
	friend bool operator>(const map &l, const map &r) {return ft::lexicographical_compare(r.begin(), r.end(), l.begin(), l.end());}
	friend bool operator>=(const map &l, const map &r) {return (l > r || l == r);}


};	
	/*Swap*/
	template<typename Key, typename Tp,
        typename Cmp, typename Alloc>
     inline void
    swap(map<Key, Tp, Cmp, Alloc>& l_arg, map<Key, Tp, Cmp, Alloc>& r_arg)
    	{l_arg.swap(r_arg); }
}
	
#endif