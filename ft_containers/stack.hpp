/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini.42nice.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:58:30 by dzuntini          #+#    #+#             */
/*   Updated: 2022/06/30 13:26:41 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "./vector.hpp"

namespace ft
{
	template<class T, class Container = ft::vector<T> >
	class stack
	{
		
		public:
		typedef 			T 						value_type;
		typedef 			Container 				container_type;
		typedef typename 	Container::size_type 	size_type;
		typedef 			value_type& 			reference;
		typedef const 		value_type& 			const_reference;
	
		protected:
			container_type _container;
		
		public:	
		
			explicit stack (const container_type& cont = container_type()) : _container(cont){}
		
			stack(const stack& other): _container(other._container) {}
	
			stack& operator=(const stack& other)
			{
				_container = other._container;
				return (*this);
			}
	
			bool empty() const{return (_container.empty());}
			size_type size() const{return (_container.size());}
			value_type& top(){return (_container.back());}
			const value_type& top() const{return (_container.back());}
			void push (const value_type& val){_container.push_back(val);}	
			void pop(){_container.pop_back();}

			template <class A, class ContainerV>
		  		friend bool operator== (const stack<A,ContainerV>& left_arg, const stack<A,ContainerV>& right_arg)
		  			{return(left_arg._container == right_arg._container);}
	
			template <class A, class ContainerV>
		  		friend bool operator!= (const stack<A,ContainerV>& left_arg, const stack<A,ContainerV>& right_arg)
					{return(left_arg._container != right_arg._container);}
			 
			template <class A, class ContainerV>
				  friend bool operator<  (const stack<A,ContainerV>& left_arg, const stack<A,ContainerV>& right_arg)
						{return(left_arg._container < right_arg._container);}
					 
			template <class A, class ContainerV>
				  friend bool operator<= (const stack<A,ContainerV>& left_arg, const stack<A,ContainerV>& right_arg)
						{return(left_arg._container <= right_arg._container);}
				  
			template <class A, class ContainerV>
				  friend bool operator>  (const stack<A,ContainerV>& left_arg, const stack<A,ContainerV>& right_arg)
						{return(left_arg._container > right_arg._container);}
				  
			template <class A, class ContainerV>
				  friend bool operator>= (const stack<A,ContainerV>& left_arg, const stack<A,ContainerV>& right_arg)
						{return(left_arg._container >= right_arg._container);}
	};


	
};

#endif
