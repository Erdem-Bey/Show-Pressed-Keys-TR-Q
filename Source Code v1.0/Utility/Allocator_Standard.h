#ifndef ALLOCATOR__STANDARD_H
#define ALLOCATOR__STANDARD_H

#include <utility>
#include <memory>

template<class _Ty>
class Allocator_Standard
{
	public:
		static_assert(!std::is_const<_Ty>::value,
					  "The C++ Standard forbids containers of const elements "
					  "because allocator<const T> is ill-formed.");
		//std::allocator<char> abc;
		typedef			_Ty					value_type;

		typedef			value_type		*	pointer;
		typedef	const	value_type		*	const_pointer;

		typedef			value_type		&	reference;
		typedef	const	value_type		&	const_reference;

		typedef			size_t				size_type;
		typedef			std::ptrdiff_t		difference_type;

		typedef			std::true_type		propagate_on_container_move_assignment;
		typedef			std::true_type		is_always_equal;

		template<class _Other>
		class rebind
		{	// convert this type to allocator<_Other>
			public:
				typedef Allocator_Stack<_Other> other;
		};

		pointer address(reference _Val) const _NOEXCEPT
		{	// return address of mutable _Val
			return (_STD addressof(_Val));
		}

		const_pointer address(const_reference _Val) const _NOEXCEPT
		{	// return address of non-mutable _Val
			return (_STD addressof(_Val));
		}

		Allocator_Stack() _THROW0()
		{	// construct default allocator (do nothing)
		}

		Allocator_Stack(const Allocator_Stack<_Ty>&) _THROW0()
		{	// construct by copying (do nothing)
		}

		template<class _Other>
		Allocator_Stack(const Allocator_Stack<_Other>&) _THROW0()
		{	// construct from a related allocator (do nothing)
		}

		template<class _Other>
		Allocator_Stack<_Ty>& operator=(const Allocator_Stack<_Other>&)
		{	// assign from a related allocator (do nothing)
			return (*this);
		}

		void deallocate(pointer _Ptr, size_type _Count)
		{	// deallocate object at _Ptr
			std::_Deallocate(_Ptr, _Count);
		}

		_DECLSPEC_ALLOCATOR pointer allocate(size_type _Count)
		{	// allocate array of _Count elements
			return (std::_Allocate(_Count, (pointer)0));
		}

		_DECLSPEC_ALLOCATOR pointer allocate(size_type _Count, const void *)
		{	// allocate array of _Count elements, ignore hint
			return (allocate(_Count));
		}

		template<class _Objty, class... _Types>
		void construct(_Objty *_Ptr, _Types&&... _Args)
		{	// construct _Objty(_Types...) at _Ptr
			::new ((void *)_Ptr) _Objty(_STD forward<_Types>(_Args)...);
		}

		template<class _Uty>
		void destroy(_Uty *_Ptr)
		{	// destroy object at _Ptr
			_Ptr->~_Uty();
		}

		size_t max_size() const _NOEXCEPT
		{	// estimate maximum array size
			return ((size_t)(-1) / sizeof (_Ty));
		}
};

#endif	// ALLOCATOR__STANDARD_H
