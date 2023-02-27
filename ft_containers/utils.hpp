/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini.42nice.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:46:25 by dzuntini          #+#    #+#             */
/*   Updated: 2022/09/26 16:35:49 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>

static class nullptr_t //True Null Ptr Gotten from Rchallie Github
{
    public:
       
        template<class T>
        operator T*() const { return (0); }

       
        template<class C, class T>
        operator T C::*() const { return (0); }

    private:
        void operator&() const;

} u_nullptr = {};

namespace ft
{
    template <typename T>
        std::string to_string(T n)
        {
            std::ostringstream ss;
            ss << n;
            return (ss.str());
        }
    
   
    template <class Arg1, class Arg2, class Result>
        struct binary_function
        {
            typedef Arg1 first_argument_type;          
            typedef Arg2 second_argument_type;      
            typedef Result result_type;
        };
    
   
    template <class T>
        struct less : binary_function<T, T, bool>
        {
            bool operator() (const T& x, const T& y) const { return (x < y); }
        };

   
    template <class T1, class T2>
        struct pair
        {
            public :                              
                typedef T1 first_type;            
                typedef T2 second_type;
                first_type first;
                second_type second;       
                
                pair(): first(first_type()), second(second_type()) {}

               
                template<class F, class S>
                    pair (const pair<F, S> &cpy) : first(cpy.first), second(cpy.second) {}

               
                pair (const first_type& a, const second_type& b): first(a), second(b) {}

               
                pair& operator= (const pair& pr)
                {
                    this->first = pr.first;
                    this->second = pr.second;
                    return (*this);
                }
        };
    
   
    template <class T1, class T2>
        bool operator== (const ft::pair<T1,T2> &left_argument, const ft::pair<T1,T2> &right_argument)
        {return (left_argument.first == right_argument.first && left_argument.second == right_argument.second);}

   
    template <class T1, class T2>
        bool operator!= (const ft::pair<T1,T2>& left_argument, const ft::pair<T1,T2>& right_argument)
        {return !(left_argument == right_argument);}
    
   
    template <class T1, class T2>
        bool operator<  (const ft::pair<T1,T2>& left_argument, const ft::pair<T1,T2>& right_argument)
        {return (left_argument.first < right_argument.first || (!(right_argument.first < left_argument.first) && left_argument.second < right_argument.second));}

   
    template <class T1, class T2>
        bool operator<= (const ft::pair<T1,T2>& left_argument, const ft::pair<T1,T2>& right_argument)
        {return !(right_argument < left_argument);}

   
    template <class T1, class T2>
        bool operator>  (const ft::pair<T1,T2>& left_argument, const ft::pair<T1,T2>& right_argument)
        {return (right_argument < left_argument);}

   
    template <class T1, class T2>
        bool operator>= (const ft::pair<T1,T2>& left_argument, const ft::pair<T1,T2>& right_argument)
        {return !(left_argument < right_argument);}
    
   
    template <class T1, class T2>
        ft::pair<T1,T2> make_pair(T1 x, T2 y)
        { return (ft::pair<T1, T2>(x, y));}
    
   
    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

   

   /* Whole Integral check , to Checks whether T is an integral type. Provides the member constant value which is equal to true, if 
   T is the type bool, char, char16_t, char32_t, wchar_t, short, int, long, long long, 
   or any implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants. 
   Otherwise, value is equal to false. */
    template <bool is_integral, typename T>
        struct is_integral_res {
            typedef T type;
            static const bool value = is_integral;
                                };

   
    template <typename> struct is_integral_type : public is_integral_res<false, bool> {};
	template <> struct is_integral_type<bool> : public is_integral_res<true, bool> {};

   	template <> struct is_integral_type<char> : public is_integral_res<true, char> {};
	template <> struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};
    template <> struct is_integral_type<short int> : public is_integral_res<true, short int> {};
    template <> struct is_integral_type<int> : public is_integral_res<true, int> {};
    template <> struct is_integral_type<long int> : public is_integral_res<true, long int> {};
	template <> struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};
	template <> struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};
    template <> struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};
	template <> struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};
	template <> struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
    template <> struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};
	template <typename T> struct is_integral : public is_integral_type<T> { };
    
	/*Iterator Tag*/
	class random_access_iterator_tag {};
    class bidirectional_iterator_tag {};
    class forward_iterator_tag {};
    class input_iterator_tag {};
    class output_iterator_tag {};


	/*If T is valid iterator type*/
	template <bool is_valid, typename T> struct valid_iterator_tag_res { typedef T type; const static bool value = is_valid; };
    template <typename T> struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> { };
	template <> struct is_input_iterator_tagged<ft::random_access_iterator_tag>: public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { }; 
    template <> struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>: public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };
	template <> struct is_input_iterator_tagged<ft::forward_iterator_tag>: public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };
 	template <> struct is_input_iterator_tagged<ft::input_iterator_tag>: public valid_iterator_tag_res<true, ft::input_iterator_tag> { };
	template <typename T> struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> { };
    template <> struct is_ft_iterator_tagged<ft::random_access_iterator_tag>: public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };
	template <> struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>: public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };
    template <> struct is_ft_iterator_tagged<ft::forward_iterator_tag>: public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };
	template <> struct is_ft_iterator_tagged<ft::input_iterator_tag>: public valid_iterator_tag_res<true, ft::input_iterator_tag> { };
	template <> struct is_ft_iterator_tagged<ft::output_iterator_tag>: public valid_iterator_tag_res<true, ft::output_iterator_tag> { };

   
    template <typename T>
    class InvalidIteratorException : public std::exception
    {
        private:
            std::string _msg;
        
        public :
            InvalidIteratorException () throw() { _msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); }
            InvalidIteratorException (const InvalidIteratorException&) throw() {}
            InvalidIteratorException& operator= (const InvalidIteratorException&) throw() {}
            virtual ~InvalidIteratorException() throw() {}
            virtual const char* what() const throw() { return (_msg.c_str()); }
    };

	/*For normal iterator*/
    template <class Iterator> struct iterator_traits
    {
        public:
            typedef typename Iterator::difference_type       difference_type;      
            typedef typename Iterator::value_type            value_type;   
            typedef typename Iterator::pointer               pointer;  
            typedef typename Iterator::reference             reference; 
            typedef typename Iterator::iterator_category     iterator_category;
    };
    
   /*For pointed iterator*/
    template <class T> struct iterator_traits<T*>
    {
        public:
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };
    
   /*for const iterator*/
    template <class T> class iterator_traits<const T*>
    {
        public:
        typedef ptrdiff_t                       difference_type;     
        typedef const T                         value_type;  
        typedef const T*                        pointer; 
        typedef const T&                        reference; 
        typedef ft::random_access_iterator_tag  iterator_category;
    };

   
    template<class InputIterator>
        typename ft::iterator_traits<InputIterator>::difference_type
            distance (InputIterator first, InputIterator last)
        {
            typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
            while (first != last)
            {
                first++;
                rtn++;
            }
            return (rtn);
        }

	
	/*Iterator Class for check and test mostly*/
    template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
        class iterator
        {
            public:
               
                typedef T           value_type;  
                typedef Distance    difference_type;
                typedef Pointer     pointer;
                typedef Reference   reference;
                typedef Category    iterator_category;
        };

    template <class T>
        class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
        {  
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer               pointer;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference             reference;
            
            private:
                pointer _elem;
        };

	/*Class reverse iterator another type of iterator*/
    template <class Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator    iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category 	iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type      	value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iterator>::pointer     		pointer;
            typedef typename ft::iterator_traits<Iterator>::reference   reference;
            
           
            reverse_iterator() : _elem(){}
            explicit reverse_iterator (iterator_type it): _elem(it) {}

           
            template <class Iter>
                reverse_iterator (const reverse_iterator<Iter>& rev_it) : _elem(rev_it.base()){}

            virtual ~reverse_iterator() {}

           
            iterator_type base() const
            { return (_elem); }

           
            reference operator*() const
            {
                iterator_type tmp = _elem;
                return (*(--tmp));
            }

           
            reverse_iterator operator+ (difference_type n) const  
                {return (reverse_iterator(_elem - n)); }

           
            reverse_iterator& operator++()
            {
                --_elem;
                return (*this);
            }

           
            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }

           
            reverse_iterator& operator+= (difference_type n)
            {
                _elem -= n;
                return (*this);
            }

           
            reverse_iterator operator- (difference_type n) const 
            {return (reverse_iterator(_elem + n)); }

           
            reverse_iterator& operator--()
            {
                ++_elem;
                return (*this);
            }

           
            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                --(*this);
                return (tmp);
            }

           
            reverse_iterator& operator-= (difference_type n)
            {
                _elem += n;
                return (*this);
            }

           
            pointer operator->() const { return &(operator*()); }    
            reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

        private:
            iterator_type     _elem;
    };

   
    template <class Iterator>
        bool operator== (const reverse_iterator<Iterator>& left_argument, const reverse_iterator<Iterator>& right_argument) 
		{ return (left_argument.base() == right_argument.base()); }

   
    template <class Iterator_L, class Iterator_R>
        bool operator== (const reverse_iterator<Iterator_L>& left_argument, const reverse_iterator<Iterator_R>& right_argument) 
		{ return (left_argument.base() == right_argument.base()); }

   
    template <class Iterator>
        bool operator!= (const reverse_iterator<Iterator>& left_argument, const reverse_iterator<Iterator>& right_argument) 
        { return (left_argument.base() != right_argument.base()); }

   
    template <class Iterator_L, class Iterator_R>
        bool operator!= (const reverse_iterator<Iterator_L>& left_argument, const reverse_iterator<Iterator_R>& right_argument) 
        { return (left_argument.base() != right_argument.base()); }

   
    template <class Iterator>
        bool operator<  (const reverse_iterator<Iterator>& left_argument, const reverse_iterator<Iterator>& right_argument) 
        { return (left_argument.base() > right_argument.base()); }

   
    template <class Iterator_L, class Iterator_R>
        bool operator< (const reverse_iterator<Iterator_L>& left_argument, const reverse_iterator<Iterator_R>& right_argument) 
        { return (left_argument.base() > right_argument.base()); }

   
    template <class Iterator>
        bool operator<= (const reverse_iterator<Iterator>& left_argument, const reverse_iterator<Iterator>& right_argument) 
        { return (left_argument.base() >= right_argument.base()); }

   
    template <class Iterator_L, class Iterator_R>
        bool operator<= (const reverse_iterator<Iterator_L>& left_argument, const reverse_iterator<Iterator_R>& right_argument) 
        { return (left_argument.base() >= right_argument.base()); }

   
    template <class Iterator>
        bool operator> (const reverse_iterator<Iterator>& left_argument, const reverse_iterator<Iterator>& right_argument) 
        { return (left_argument.base() < right_argument.bash()); }

   
    template <class Iterator_L, class Iterator_R>
        bool operator> (const reverse_iterator<Iterator_L>& left_argument, const reverse_iterator<Iterator_R>& right_argument) 
        { return (left_argument.base() < right_argument.base()); }
   
    template <class Iterator>
        bool operator>= (const reverse_iterator<Iterator>& left_argument, const reverse_iterator<Iterator>& right_argument) 
        { return (left_argument.base() <= right_argument.base()); }

   
    template <class Iterator_L, class Iterator_R>
        bool operator>= (const reverse_iterator<Iterator_L>& left_argument, const reverse_iterator<Iterator_R>& right_argument) 
         { return (left_argument.base() <= right_argument.base()); }

   
    template <class Iterator>
        reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) 
        { return (rev_it + n); }

   
    template <class Iterator>
        typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& left_argument, const reverse_iterator<Iterator>& right_argument) 
        { return (left_argument.base() - right_argument.base()); }

   
    template <class Iterator_L, class Iterator_R>
        bool operator-(const reverse_iterator<Iterator_L>& left_argument, const reverse_iterator<Iterator_R>& right_argument) 
        { return (left_argument.base() - right_argument.base()); }

   

   
    template <class InputIterator1, class InputIterator2>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || *first2 < *first1) return false;
                else if (*first1 < *first2) return true;
                ++first1;
                ++first2;
            }
            return (first2 != last2);
        }

   
    template <class InputIterator1, class InputIterator2, class Compare>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || comp(*first2, *first1)) return false;
                else if (comp(*first1, *first2)) return true;
                ++first1;
                ++first2;
            }
            return (first2 != last2);
        }
    
    template <typename T>
    struct RBT_Node
    {
        public :

            T*          value;
            RBT_Node*   parent;
            RBT_Node*   left;
            RBT_Node*   right;
            bool        isblack;

           
            explicit RBT_Node (T *val = 0) : value(val),  parent(u_nullptr), left(u_nullptr), right(u_nullptr), isblack(false){}
           
            RBT_Node (const RBT_Node& nd)
            : value(nd.value), parent(nd.parent), left(nd.left), right(nd.right), isblack(nd.isblack){}

            virtual ~RBT_Node() {}

           
            RBT_Node &operator=(const RBT_Node& nd)
            {
                if (nd == *this)
                    return (*this);
                
                this->value = nd.value;
                this->parent = nd.parent;
                this->left = nd.left;
                this->right = nd.right;
                this->isblack = nd.isblack;
                
                return (*this);
            }
            
            bool operator==(const RBT_Node& nd)
            {
                if (value == nd.value)
                    return (true);
                return (false);
            }


            RBT_Node* min() {
                if(!left)
                    return (this);
                return (left->min());
                
            }

            RBT_Node* max() {
                if(!right)
                    return (this);
                return (right->max());
                
            }

            RBT_Node* next() {
				if (right)
					return (right->min());
				if (parent && this == parent->left)
					return (parent);
				RBT_Node* next = this;
				while (next && next->parent && next == next->parent->right)
					next = next->parent;
				if (next) {
					return (next->parent);
				}
				return u_nullptr;
			}

             RBT_Node* prev() {
				if (left)
					return (left->max());
				if (parent && this == parent->right)
					return (parent);
				RBT_Node* prev = this;
				while (prev && prev->parent && prev == prev->parent->left)
					prev = prev->parent;
				if (prev) {
					return (prev->parent);
				}
				return u_nullptr;
			}
    };
}

# endif