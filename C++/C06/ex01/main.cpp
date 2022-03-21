//
// Created by David Zuntini on 3/16/22.
//

#include "Data.hpp"

/* Reintrepret Cast*/
/* reinterpret_cast converts one pointer to another without changing the address, or converts between pointers and their numerical (integer) values.*/
uintptr_t serialize(Data* ptr)
{
	uintptr_t p = reinterpret_cast<uintptr_t>(ptr);
	return p;
}
Data* deserialize(uintptr_t raw)
{
	Data *d;
	d = reinterpret_cast<Data *>(raw);
	return d;
}

int	main()
{
	Data		*ptr;
	Data		*new_ptr;
	uintptr_t	raw;

	ptr = new Data;
	ptr->data = "Dummy Data!";

	raw = serialize(ptr);
	new_ptr = deserialize(raw);

	std::cout << "Data of ptr: " << ptr->data << std::endl;
	std::cout << "Data of new_ptr: " << new_ptr->data << std::endl;

	delete ptr;
}
