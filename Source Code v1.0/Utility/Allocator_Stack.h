#ifndef ALLOCATOR__STACK_H
#define ALLOCATOR__STACK_H

#include <algorithm>

template <typename T, const size_t MAX_SIZE>
class Allocator_Stack
{
	private:
		static constexpr bool FREE		= false;
		static constexpr bool IN_USE	= true;
		
	public:
		typedef			T					value_type;
		typedef			value_type		*	pointer;
		typedef	const	value_type		*	const_pointer;
		typedef			value_type		&	reference;
		typedef	const	value_type		&	const_reference;
		typedef			std::size_t			size_type;
		typedef			std::ptrdiff_t		difference_type;

		//*********************************************************************
		// rebind
		//*********************************************************************
		template<typename U>
		struct rebind
		{
			typedef Allocator_Stack<U, MAX_SIZE>
				other;
		};

		//*********************************************************************
		// Constructor
		//*********************************************************************
		Allocator_Stack()
			: p_first_free(in_use)
		{
			initialise();
		}

		//*********************************************************************
		// Copy constructor
		//*********************************************************************
		Allocator_Stack(const Allocator_Stack &rhs)
			: p_first_free(in_use)
		{
			initialise();
		}

		//*********************************************************************
		// Templated copy constructor
		//*********************************************************************
		template<typename U>
		Allocator_Stack(const Allocator_Stack<U, MAX_SIZE>&rhs)
			: p_first_free(in_use)
		{
			initialise();
		}

		//*********************************************************************
		// Destructor
		//*********************************************************************
		~Allocator_Stack()
		{
		}

		//*********************************************************************
		// address
		//*********************************************************************
		pointer address(reference x) const
		{
			return (&x);
		}

		//*********************************************************************
		// address
		//*********************************************************************
		const_pointer address(const_reference x) const
		{
			return (x);
		}

		//*********************************************************************
		// allocate
		// Allocates from the internal array.
		//*********************************************************************
		pointer allocate(size_type n, const_pointer cp = 0)
		{
			// Pointers to the 'in_use' flags.
			bool *p_first     = p_first_free;
			bool *const p_end = &in_use[MAX_SIZE];

			// 'Find first fit' allocation algorithm, starting from the first free slot.
			// If n == 1 then we already have the free slot address or p_end.
			if (n == 1)
			{
				// No space left?
				if (p_first == p_end)
				{
					throw std::bad_alloc();
				}

				// Mark the slot as 'in use'
				*p_first = IN_USE;
			}
			else
			{
				// Search for a big enough range of free slots.
				p_first = std::search_n(p_first, p_end, static_cast<long>(n), FREE);

				// Not enough space found?
				if (p_first == p_end)
				{
					throw std::bad_alloc();
				}

				// Mark the range as 'in use'
				std::fill(p_first, p_first + n, IN_USE);
			}

			// Update the 'first free' pointer if necessary.
			if (p_first == p_first_free)
			{
				// Find the next free slot or p_end
				p_first_free = std::find(p_first + n, p_end, FREE);
			}

			// Return the memory allocation.
			const size_t offset = std::distance(in_use, p_first) * sizeof(value_type);

			return (reinterpret_cast<pointer>(&p_buffer[offset]));
		}

		//*********************************************************************
		// deallocate
		// Clears the 'in_use' flags for the deallocated items.
		//*********************************************************************
		void deallocate(pointer p, size_type n)
		{
			// Find the start of the range.
			size_t index = std::distance(p_buffer, reinterpret_cast<char *>(p)) / sizeof(value_type);

			bool *p_first = &in_use[index];

			// Mark the range as 'free'.
			if (n == 1)
			{
				*p_first = FREE;
			}
			else
			{
				std::fill(p_first, p_first + n, FREE);
			}

			// Update the 'first free' pointer if necessary.
			if (p_first < p_first_free)
			{
				p_first_free = p_first;
			}
		}

		//*********************************************************************
		// max_size
		// Returns the maximum size that can be allocated in total.
		//*********************************************************************
		size_type max_size() const
		{
			return (MAX_SIZE);
		}

		//*********************************************************************
		// construct
		// Constructs an item.
		//*********************************************************************
		void construct(pointer p, const value_type &x)
		{
			// Placement 'new'
			new (p)value_type(x);
		}

		//*********************************************************************
		// destroy
		// Destroys an item.
		//*********************************************************************
		void destroy(pointer p)
		{
			// Call the destructor.
			p->~value_type();
		}

		private:

		enum
		{
			ALIGNMENT = std::tr1::alignment_of<T>::value - 1
		};

		//*********************************************************************
		// initialise
		// Initialises the internal allocation buffers.
		//*********************************************************************
		void initialise()
		{
			// Ensure alignment.
			p_buffer = reinterpret_cast<char *>((reinterpret_cast<size_t>(&buffer[0]) + ALIGNMENT) & ~ALIGNMENT);

			// Mark all slots as free.
			std::fill(in_use, in_use + MAX_SIZE, FREE);
		}

		// Disabled operator.
		void operator =(const Allocator_Stack &);

		// The allocation buffer. Ensure enough space for correct alignment.
		char buffer[(MAX_SIZE * sizeof(value_type)) + ALIGNMENT + 1];

		// Pointer to the first valid location in the buffer after alignment.
		char *p_buffer;

		// The flags that indicate which slots are in use.
		bool in_use[MAX_SIZE];

		// Pointer to the first free slot.
		bool *p_first_free;
};

//*********************************************************************
// operator ==
// Equality operator.
//*********************************************************************
template<typename T, const size_t MAX_SIZE>
inline bool operator ==(const Allocator_Stack<T, MAX_SIZE> &,
						const Allocator_Stack<T, MAX_SIZE> &)
{
	return (false);
}

//*********************************************************************
// operator !=
// Inequality operator.
//*********************************************************************
template<typename T, const size_t MAX_SIZE>
inline bool operator !=(const Allocator_Stack<T, MAX_SIZE> &, 
						const Allocator_Stack<T, MAX_SIZE> &)
{
	return (true);
}


#endif	// ALLOCATOR__STACK_H
