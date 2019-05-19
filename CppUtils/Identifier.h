#pragma once
#include <type_traits>

#define DEFINE_IDENTIFIER(IdentifierName, IdentifierType) \
class IdentifierName ## Trait {}; \
using IdentifierName = utils::Identifier<IdentifierName ## Trait, IdentifierType>; \

namespace utils
{

template<typename TraitT, typename ValueT>
class Identifier final
{
	static_assert( 
		!std::is_reference<ValueT>::value,
		"ValueT cannot be a reference" );
	static_assert(
		!std::is_pointer<ValueT>::value,
		"ValueT cannot be a pointer" );
	static_assert(
		!std::is_void<ValueT>::value,
		"ValueT cannot be void" );

public:
	explicit Identifier(ValueT&& i_value) 
		: m_value(std::forward<ValueT>(i_value)) { }
	
	// copy semantics
	Identifier(const Identifier<TraitT, ValueT>& rhs) 
		: m_value(rhs.m_value) { }

	Identifier<TraitT, ValueT>& operator=(const Identifier<TraitT, ValueT>& rhs) &
	{
		if (this != &rhs)
		{
			m_value = rhs.m_value;
		}
		return *this;
	}

	explicit Identifier( Identifier<TraitT, ValueT>&& rhs)
		: m_value(std::move(rhs.m_value))
	{ }

	//move semantics
	Identifier<TraitT, ValueT>& operator=(Identifier<TraitT, ValueT>&& rhs) &
	{
		if ( this != &rhs )
		{
			m_value = std::move(rhs.m_value);
		}
		return *this;
	}

	~Identifier() = default;

	const ValueT& GetValue() const { return m_value; }

private:
	const ValueT m_value;
};

template<typename TraitT, typename ValueT>
inline bool operator==(const Identifier<TraitT, ValueT>& lhs, const Identifier<TraitT, ValueT>& rhs)
{
	return lhs.GetValue() == rhs.GetValue();
}

template<typename TraitT, typename ValueT>
inline bool operator!=(const Identifier<TraitT, ValueT>& lhs, const Identifier<TraitT, ValueT>& rhs)
{
	return !( lhs == rhs );
}

}