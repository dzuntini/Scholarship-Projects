/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini.42nice.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:52:46 by dzuntini          #+#    #+#             */
/*   Updated: 2022/09/22 18:12:44 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <algorithm>
# include <cstddef>
# include "./Iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		private:
				
		public:
				/*For const_stuff the pointer/ref is const , the element that is pointed at is not*/

				typedef T															value_type;
				typedef Alloc 														allocator_type;
				typedef typename allocator_type::reference 							reference;
				typedef typename allocator_type::const_reference 					const_reference;
				typedef typename allocator_type::pointer							pointer;
				typedef typename allocator_type::const_pointer						const_pointer; 
				
				typedef ft::rai<value_type>               							iterator;
				typedef ft::rai<const value_type>           						const_iterator;
				typedef ft::reverse_iterator<iterator>            					reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>      					const_reverse_iterator;
				typedef typename ft::iterator_traits<iterator>::difference_type    	difference_type; 
				typedef typename allocator_type::size_type          				size_type;
			
			/*Explicit convertor mean it will only take thoses types of parameters*/
			/*Empty Container*/			
			explicit vector (const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_start(u_nullptr),
				_end(u_nullptr),
				_end_capacity(u_nullptr)
			{}

			/*Construct Vector with N elements , and fill them all with same value*/
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc), _start(u_nullptr), _end(u_nullptr), _end_capacity(u_nullptr)
			{
				_start = _alloc.allocate( n );
				_end_capacity = _start + n;
				_end = _start;
				while (n--)
				{
					_alloc.construct(_end, val);
					_end++;
				}
			}

			/*Construct a vector using two iterator to fill it with elements by incrementing the iterator*/
			template <class InputIterator>
					vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
					: _alloc(alloc)
			{
				bool is_valid;
				if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
				
				difference_type n = ft::distance(first, last);
				_start = _alloc.allocate( n );
				_end_capacity = _start + n;
				_end = _start;
				while (n--)
				{
					_alloc.construct(_end, *first++);
					_end++;
				}
			}
			
			/*Copy*/
			vector (const vector& x)
			:
				_alloc(x._alloc),
				_start(u_nullptr),
				_end(u_nullptr),
				_end_capacity(u_nullptr)
			{
				this->insert(this->begin(), x.begin(), x.end());
			}
			
			/*Destructor , also deallocating (or freeing) items contained*/
			~vector()
			{
				this->clear();
				_alloc.deallocate(_start, this->capacity());
			}
						
			/*Deep copy from x to this , erase old content*/
			vector &operator=(const vector& x)
			{
				if (x == *this)
					return (*this);
				this->clear();
				this->insert(this->end(), x.begin(), x.end());
				return (*this);
			}

			// Iterators:

			/*Return the iterator to the first element.*/
			iterator begin() { return (_start); };

			/*Return a const iterator to the first element*/
			const_iterator begin() const { return (_start); }

			/*Return the iteration to the last element , also if empty , begin = last so ...*/
			iterator end()
			{
				if (this->empty())
					return (this->begin());
				return (_end);
			}

			/*Const*/
			const_iterator end() const
			{
				if (this->empty())
					return (this->begin());
				return (_end);
			}

			/*Reverse iterator so if i point to 6th element and i++ then i will point to 5 ,So it begin at the end*/
			reverse_iterator rbegin() { return (reverse_iterator(this->end())); }

			const_reverse_iterator rbegin() const { return (reverse_iterator(this->end())); }

			/*reversed end so begin :)*/
			reverse_iterator rend() { return (reverse_iterator(this->begin())); }

			const_reverse_iterator rend() const { return (reverse_iterator(this->begin())); }

			// Capacity:
			
			/*Return number of element in the vector*/
			size_type   size(void) const { return (this->_end - this->_start); }

			/*Max size the vector could contain , depend on system*/
			size_type   max_size(void) const { return allocator_type().max_size(); }

			/*Resize vector , erase if going smaller , add val if going bigger*/
			void        resize (size_type n, value_type val = value_type())
			{
				if (n > this->max_size())
					throw (std::length_error("vector::resize"));
				else if (n < this->size())
				{
					while (this->size() > n)
					{
						--_end;
						_alloc.destroy(_end);
					}
				}
				else
					this->insert(this->end(), n - this->size(), val);
			}

			/*Return Size of Alloc*/
			size_type   capacity (void) const { return (this->_end_capacity - this->_start); }

			/*Is Vector Empty*/
			bool        empty (void) const { return (size() == 0 ? true : false); }

			/*If size < n then vector size become N (with increase in alloc)*/
			void        reserve (size_type n)
			{
				if (n > this->max_size())
					throw (std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));
				else if (n > this->capacity())
				{
					pointer prev_start = _start;
					pointer prev_end = _end;
					size_type prev_size = this->size();
					size_type prev_capacity = this->capacity();
					
					_start = _alloc.allocate( n );
					_end_capacity = _start + n;
					_end = _start;
					while (prev_start != prev_end)
					{
						_alloc.construct(_end, *prev_start);
						_end++;
						prev_start++;
					}
					_alloc.deallocate(prev_start - prev_size, prev_capacity);
				}
			}

			reference operator[] (size_type n) { return (*(_start + n)); }

			const_reference operator[] (size_type n) const { return (*(_start + n)); }
			
			/*Ref to element at N position*/
			reference at (size_type n)
			{
				checkRange(n);
				return ((*this)[n]);
			}

			const_reference at (size_type n) const
			{
				checkRange(n);
				return ((*this)[n]);
			}

			/*Reference to first element*/
			reference front () { return (*_start); }

			const_reference front () const { return (*_start); }
			
			/*Reference to last element of container*/
			reference back () { return (*(_end - 1)); }

			const_reference back () const { return (*(_end - 1)); }

			// Modifiers:

			/*Change a range of the vector with the value*/ 
			template <class InputIterator>
				void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
				{
					bool is_valid;
					if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value))
						throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
					this->clear();
					size_type dist = ft::distance(first, last);
					if (size_type(_end_capacity - _start) >= dist)
					{
						for(; &(*first) != &(*last); first++, _end++)
							_alloc.construct(_end, *first);
					}
					else
					{
						pointer new_start = pointer();
						pointer new_end = pointer();
						pointer new_end_capacity = pointer();

						new_start = _alloc.allocate(dist);
						new_end = new_start;
						new_end_capacity = new_start + dist;

						for(; &(*first) != &(*last); first++, new_end++)
							_alloc.construct(new_end, *first);
						
						_alloc.deallocate(_start, this->capacity());

						_start = new_start;
						_end = new_end;
						_end_capacity = new_end_capacity;
					}
				}
			
			/*Clear vector and fill it with Val , N times*/
			void assign (size_type n, const value_type& val)
			{
				this->clear();
				if (n == 0)
					return ;
				if (size_type(_end_capacity - _start) >= n)
				{
					while (n)
					{
						_alloc.construct(_end++ , val);
						n--;
					}
				}
				else
				{
					_alloc.deallocate(_start, this->capacity());
					_start = _alloc.allocate( n );
					_end = _start;
					_end_capacity = _start + n;
					while (n)
					{
						_alloc.construct(_end++, val);
						n--;
					}
				}
			}

			/*Add element at end of vector*/
			void push_back (const value_type& val)
			{                
				if (_end == _end_capacity)
				{
					int next_capacity = (this->size() > 0) ? (int)(this->size() * 2) : 1;
					this->reserve(next_capacity);
				}
				_alloc.construct(_end, val);
				_end++;
			}

			/*Delete last element of vector*/
			void pop_back()
			{
				_alloc.destroy(&this->back());
				_end--;
			}

			/*Add element into position in vector .Elements at thoses positions are reallocated after the new ones*/
			iterator insert (iterator position, const value_type& val)
			{
				size_type pos_len = &(*position) - _start;
				if (size_type(_end_capacity - _end) >= this->size() + 1)
				{
					for (size_type i = 0; i < pos_len; i++)
						_alloc.construct(_end - i, *(_end - i - 1));
					_end++;
					_alloc.construct(&(*position), val);
				}
				else
				{
					pointer new_start = pointer();
					pointer new_end = pointer();
					pointer new_end_capacity = pointer();

					int next_capacity = (this->size() * 2 > 0) ? this->size() * 2 : 1; 
					new_start = _alloc.allocate( next_capacity );
					new_end = new_start + this->size() + 1;
					new_end_capacity = new_start + next_capacity;

					for (size_type i = 0; i < pos_len; i++)
						_alloc.construct(new_start + i, *(_start + i));
					_alloc.construct(new_start + pos_len, val);
					for (size_type j = 0; j < this->size() - pos_len; j++)
						_alloc.construct(new_end - j - 1, *(_end - j - 1));

					for (size_type l = 0; l < this->size(); l++)
						_alloc.destroy(_start + l);
					if (_start)
						_alloc.deallocate(_start, this->capacity());
					
					_start = new_start;
					_end = new_end;
					_end_capacity = new_end_capacity;
				}
				return (iterator(_start + pos_len));
			}

			/*Add N time a val at a certain position into vector .Elements after that position are reallocated after the new ones*/
			void insert (iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				if (n > this->max_size())
					throw (std::length_error("vector::insert (fill)"));
				size_type pos_len = &(*position) - _start;
				if (size_type(_end_capacity - _end) >= n)
				{
					for (size_type i = 0; i < this->size() - pos_len; i++)
						_alloc.construct(_end - i + (n - 1), *(_end - i - 1));
					_end += n;
					while (n)
					{
						_alloc.construct(&(*position) + (n - 1), val);
						n--;
					}
				}
				else
				{
					pointer new_start = pointer();
					pointer new_end = pointer();
					pointer new_end_capacity = pointer();
					
					int next_capacity = (this->capacity() > 0) ? (int)(this->size() * 2) : 1;
					new_start = _alloc.allocate(next_capacity);
					new_end_capacity = new_start + next_capacity;

					if (size_type(new_end_capacity - new_start) < this->size() + n)
					{
						if (new_start)
							_alloc.deallocate(new_start, new_start - new_end_capacity);
						next_capacity = this->size() + n;
						new_start = _alloc.allocate(next_capacity);
						new_end = new_start + this->size() + n;
						new_end_capacity = new_start + next_capacity;
					}

					new_end = new_start + this->size() + n;

					for (int i = 0; i < (&(*position) - _start); i++)
						_alloc.construct(new_start + i, *(_start + i));
					for (size_type k = 0; k < n; k++)
						_alloc.construct(new_start + pos_len + k, val);
					for (size_type j = 0; j < (this->size() - pos_len); j++)
						_alloc.construct(new_end - j - 1, *(_end - j - 1));

					for (size_type u = 0; u < this->size(); u++)
						_alloc.destroy(_start + u);
					_alloc.deallocate(_start, this->capacity());

					_start = new_start;
					_end = new_end;
					_end_capacity = new_end_capacity;
				}
			}

			/*Add Range of element into vector .Elements at thoses positions are reallocated after the new ones*/
			template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			{
				bool is_valid;
				if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
				
				size_type dist = ft::distance(first, last);
				if (size_type(_end_capacity - _end) >= dist)
				{
					for(size_type i = 0; i < this->size() - (&(*position) - _start); i++)
						_alloc.construct(_end - i + (dist - 1), *(_end - i - 1));
					_end += dist;
					for (; &(*first) != &(*last); first++, position++)
						_alloc.construct(&(*position), *first);
				}
				else
				{
					pointer new_start = pointer();
					pointer new_end = pointer();
					pointer new_end_capacity = pointer();

					new_start = _alloc.allocate( this->size() * 2 );
					new_end = new_start + this->size() + dist;
					new_end_capacity = new_start + ( this->size() * 2 );

					if (size_type(new_end_capacity - new_start) < this->size() + dist)
					{
						if (new_start)
							_alloc.deallocate(new_start, new_end_capacity - new_start);
						new_start = _alloc.allocate (this->size() + dist);
						new_end = new_start + this->size() + dist;
						new_end_capacity = new_end;
					}

					for (int i = 0; i < &(*position) - _start; i++)
						_alloc.construct(new_start + i, *(_start + i));
					for (int j = 0; &(*first) != &(*last); first++, j++)
						_alloc.construct(new_start + (&(*position) - _start) + j, *first);
					for (size_type k = 0; k < this->size() - (&(*position) - _start); k++)
						_alloc.construct(new_start + (&(*position) - _start) + dist + k, *(_start + (&(*position) - _start) + k));

					for (size_type l = 0; l < this->size(); l++)
						_alloc.destroy(_start + l);
					_alloc.deallocate(_start, this->capacity());

					_start = new_start;
					_end = new_end;
					_end_capacity = new_end_capacity;
				}
			}

			/*Remove element at position from the vector .*/
			iterator erase (iterator position)
			{
				pointer p_pos = &(*position);
				_alloc.destroy(&(*position));
				if (&(*position) + 1 == _end)
					_alloc.destroy(&(*position));
				else
				{
					for (int i = 0; i < _end - &(*position) - 1; i++)
					{
						_alloc.construct(&(*position) + i, *(&(*position) + i + 1));
						_alloc.destroy(&(*position) + i + 1);
					}
				}
				_end -= 1;
				return (iterator(p_pos));
			}

			/*Delete range of element from vector Ex from 1 to 10*/
			iterator erase (iterator first, iterator last)
			{
				pointer p_first = &(*first);
				while(&(*first) != &(*last)) 
				{
					_alloc.destroy(&(*first));
					first++;
				}
				for (int i = 0; i < _end - &(*last); i++)
				{
					_alloc.construct(p_first + i, *(&(*last) + i));
					_alloc.destroy(&(*last) + i);
				}
				_end -= (&(*last) - p_first);
				return (iterator(p_first));
			}

			/*Swap elements from another vector*/
			void swap (vector& x)
			{
				pointer save_start = x._start;
				pointer save_end = x._end;
				pointer save_end_capacity = x._end_capacity;
				allocator_type save_alloc = x._alloc;

				x._start = this->_start;
				x._end = this->_end;
				x._end_capacity = this->_end_capacity;
				x._alloc = this->_alloc;

				this->_start = save_start;
				this->_end = save_end;
				this->_end_capacity = save_end_capacity;
				this->_alloc = save_alloc;
			}
			
			/*Destroy all elements from container*/
			void clear()
			{
				size_type save_size = this->size();
				for (size_type i = 0; i < save_size; i++)
				{
					_end--;
					_alloc.destroy(_end);
				}
			}

		private:
			allocator_type  _alloc;
			pointer         _start;
			pointer         _end;
			pointer         _end_capacity;

			/*Check if N is not out of size limit*/
			void checkRange(const size_type& n) const
			{
				if (n >= this->size())
					throw (std::out_of_range("vector::checkRange: n (which is "
							+ ft::to_string(n) + ") >= this->size() (which is "
							+ ft::to_string(this->size()) + ")"));
			}
	};

	// Non-member function overloads
	
	
	/*Return true if they are equal, false otherwise.*/
	template <class T, class Alloc>
		bool operator== (const ft::vector<T, Alloc>& left_argument, const ft::vector<T, Alloc>& right_argument)
		{
			if (left_argument.size() != right_argument.size())
				return (false);
			typename ft::vector<T>::const_iterator first1 = left_argument.begin();
			typename ft::vector<T>::const_iterator first2 = right_argument.begin();
			while (first1 != left_argument.end())
			{
				
				if (first2 == right_argument.end() || *first1 != *first2)
					return (false);
				++first1;
				++first2;
			}
			return (true);
		}

	/*Return true if they are different, false otherwise.*/
	template <class T, class Alloc>
		bool operator!= (const vector<T, Alloc>& left_argument, const vector<T, Alloc>& right_argument)
		{
			return (!(left_argument == right_argument));
		}
	
	/*Return true if left_argument is lexicographicalement less, false otherwise.*/
	template <class T, class Alloc>
		bool operator<  (const vector<T, Alloc>& left_argument, const vector<T, Alloc>& right_argument)
		{
			return (ft::lexicographical_compare(left_argument.begin(), left_argument.end(), right_argument.begin(), right_argument.end()));
		}

	
	/*Return true if left_argument is lexicographicalement less or equal, false otherwise.*/
	template <class T, class Alloc>
		bool operator<= (const vector<T, Alloc>& left_argument, const vector<T, Alloc>& right_argument)
		{
			return (!(right_argument < left_argument));
		}

	/* Return true if left_argument is lexicographicalement superior, false otherwise.*/
	template <class T, class Alloc>
		bool operator>  (const vector<T, Alloc>& left_argument, const vector<T, Alloc>& right_argument)
		{
			return (right_argument < left_argument);
		}

	
	/* Return true if left_argument is lexicographicalement superior or equal, false otherwise.*/
	template <class T, class Alloc>
		bool operator>= (const vector<T, Alloc>& left_argument, const vector<T, Alloc>& right_argument)
		{
			return (!(left_argument < right_argument));
		}
	
	/*Swap*/
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>&y)
		{	x.swap(y);}
}
#endif