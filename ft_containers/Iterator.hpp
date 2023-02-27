/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini.42nice.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:52:35 by dzuntini          #+#    #+#             */
/*   Updated: 2022/06/30 11:35:30 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>
# include "./utils.hpp"


/*Going for Random access iterator RAI below cause Map need bidirectional but random is a valid bidirectional , also Vector need RAI and Stack cant use it but is using vector so.... */

namespace   ft
{
	template <typename T>
		class rai : ft::iterator<ft::random_access_iterator_tag, T>
		{
			public:
				typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
                typedef T*           																	pointer;
                typedef T&           																	reference;
				
				
				rai(void) : _elem(u_nullptr) {}
				rai(pointer elem) : _elem(elem) {}
				rai(const rai& op) : _elem(op._elem) {}
                virtual ~rai() {}


				rai &operator=(const rai& op)
				{
					if (this == &op)
						return (*this);
					this->_elem = op._elem;
					return (*this);
				}

                /*Return element pointed*/
				pointer base() const { 
                    return (this->_elem); 
                }
                
                /*Return Reference to element*/                
				reference operator*(void) const { 
                    return (*_elem); 
                }

                /*Return Pointer to element*/
				pointer operator->(void) { 
                    return &(this->operator*()); 
                }

				/*When you do a ++i
                 Pre Increment to next element in memory return a pointer*/
				rai& operator++(void)
				{
					_elem++;
					return (*this);
				}

				/*When you do a i++ Also change to int cause cant overloard two function with same name and parameter but only return change ^Weird
                 Post Increment to next element in memory , return a copy of iterator*/
				rai operator++(int)
				{
					rai retourn(*this);
					operator++();
					return (retourn);
				}

                /*When you do a --i
                 Pre Decrement to next element in memory return a pointer*/
				rai& operator--(void)
				{
					_elem--;
					return (*this);
				}

				/*When you do a i--
                 Post Decrement to next element in memory , return a copy of iterator*/
				rai operator--(int)
				{
					rai retourn(*this);
					operator--();
					return (retourn);
				}

				/* for a "str[i + x]" kind of situation*/
				rai operator+(difference_type x) const { 
                    return (_elem + x); 
                }

                /* for a "str[i - x]" kind of situation*/
				rai operator-(difference_type x) const { 
                    return (_elem - x); 
                }

				/* i += x*/
				rai& operator+=(difference_type x)
				{
					_elem += x;
					return (*this);
				}

                /* i -= x*/
				rai& operator-=(difference_type x)
				{
					_elem -= x;
					return (*this);
				}

				/*When you need a specific place as a iterator so instead of str[i], it is str[6] for example
                So begin + x basically */
				reference operator[](difference_type x) {
                    return (*(operator+(x))); 
                }

				 operator rai<const T> () const { 
					return (rai<const T>(this->_elem));
				 }

                private:
					/* Element pointed by the iterator. */
					pointer _elem;
				
		};

	/*Check if both operator are equal*/
	template <typename T>
	    typename ft::rai<T>::difference_type
	    operator==(const ft::rai<T> left_Iterator, const ft::rai<T> right_Iterator)
	    {
		    return (left_Iterator.base() == right_Iterator.base());
	    }

	/* Same as above but if one or both are const */
	template<typename T_L, typename T_R>
	    typename ft::rai<T_L>::difference_type
	    operator==(const ft::rai<T_L> left_Iterator, const ft::rai<T_R> right_Iterator)
	    {   
		    return (left_Iterator.base() == right_Iterator.base());
	    }

	/*Opposite of above  for both function . Different */
	template <typename T>
	    typename ft::rai<T>::difference_type
	    operator!=(const ft::rai<T> left_Iterator, const ft::rai<T> right_Iterator)
	    {
	    	return (left_Iterator.base() != right_Iterator.base());
	    }

	template<typename T_L, typename T_R>
	    typename ft::rai<T_L>::difference_type
	    operator!=(const ft::rai<T_L> left_Iterator, const ft::rai<T_R> right_Iterator)
	    {
	    	return (left_Iterator.base() != right_Iterator.base());
	    }

	
	/*Compare if left is lower than right in memory*/
	template <typename T>
	    typename ft::rai<T>::difference_type
	    operator<(const ft::rai<T> left_Iterator, const ft::rai<T> right_Iterator)
	    {
	    	return (left_Iterator.base() < right_Iterator.base());
	    }

	/*Const*/
	template<typename T_L, typename T_R>
	    typename ft::rai<T_L>::difference_type
	    operator<(const ft::rai<T_L> left_Iterator, const ft::rai<T_R> right_Iterator)
	    {
	    	return (left_Iterator.base() < right_Iterator.base());
	    }

	/*Compare if left is upper than right in memory*/
	template <typename T>
	    typename ft::rai<T>::difference_type
	    operator>(const ft::rai<T> left_Iterator, const ft::rai<T> right_Iterator)
	    {return (left_Iterator.base() > right_Iterator.base());}

	/*Const*/
	template<typename T_L, typename T_R>
	    typename ft::rai<T_L>::difference_type
	    operator>(const ft::rai<T_L> left_Iterator, const ft::rai<T_R> right_Iterator)
	    {return (left_Iterator.base() > right_Iterator.base());}

    /*Lower or equal in memory*/
	template <typename T>
	    typename ft::rai<T>::difference_type
	    operator<=(const ft::rai<T> left_Iterator, const ft::rai<T> right_Iterator)
	    {return (left_Iterator.base() <= right_Iterator.base());}

	/*Const*/
	template<typename T_L, typename T_R>
	    typename ft::rai<T_L>::difference_type
	    operator<=(const ft::rai<T_L> left_Iterator, const ft::rai<T_R> right_Iterator)
	    {return (left_Iterator.base() <= right_Iterator.base());}

    /*Upper or equal yaddy yaddy yade	*/
	template <typename T>
	    typename ft::rai<T>::difference_type
	    operator>=(const ft::rai<T> left_Iterator, const ft::rai<T> right_Iterator)
	    {
	    	return (left_Iterator.base() >= right_Iterator.base());
	    }

	template<typename T_L, typename T_R>
	    typename ft::rai<T_L>::difference_type
	    operator>=(const ft::rai<T_L> left_Iterator,  const ft::rai<T_R> right_Iterator)
	    {
	    	return (left_Iterator.base() >= right_Iterator.base());
	    }

    /* Didnot understood that one , Copying from source code */
	template<typename T>
	    ft::rai<T> operator+(typename ft::rai<T>::difference_type x, typename ft::rai<T>& rai)
	    	{
	    		return (&(*rai) + x);
	    	}
    /*Difference between two iterator adress*/
	template <typename T>
	    typename ft::rai<T>::difference_type
	    operator-(const ft::rai<T> left_Iterator, const ft::rai<T> right_Iterator)
	    {
	    	return (left_Iterator.base() - right_Iterator.base());
	    }

	/* Const */
	template<typename T_L, typename T_R>
	    typename ft::rai<T_L>::difference_type
	    operator-(const ft::rai<T_L> left_Iterator, const ft::rai<T_R> right_Iterator)
	    {
	    	return (left_Iterator.base() - right_Iterator.base());
	    }
}


#endif