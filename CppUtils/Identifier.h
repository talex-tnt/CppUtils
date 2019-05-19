#pragma once

#define DEFINE_IDENTIFIER(IdentifierName, IdentifierType) \
class IdentifierName ## Trait {}; \
using IdentifierName = utils::Identifier<IdentifierName ## Trait, IdentifierType>; \

namespace utils
{
template<	typename TraitT, 
			typename ValueT, 
			typename = std::enable_if<
				std::is_pointer<ValueT>::value	 == false &&
				std::is_reference<ValueT>::value == false &&
				std::is_void<ValueT>::value		 == false
			>::type
>
class Identifier final
{
public:
	explicit Identifier<TraitT, ValueT>(ValueT&& i_value) : m_value(std::forward<ValueT>(i_value)) { }
	
	// copy semantics
	Identifier<TraitT, ValueT>(const Identifier<TraitT, ValueT>& rhs) 
		: m_value(rhs.m_value) { }

	Identifier<TraitT, ValueT>& operator=(const Identifier<TraitT, ValueT>& rhs) &
	{
		if (this != &rhs)
		{
			m_value = rhs.m_value;
		}
		return *this;
	}

	explicit Identifier<TraitT, ValueT>( Identifier<TraitT, ValueT>&& rhs)
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

	~Identifier<TraitT, ValueT>() = default;

	const ValueT& GetValue() const { return m_value; }

private:
	ValueT m_value;
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