#pragma once

namespace utils
{

template<typename TraitT, typename ValueT>
Identifier<TraitT, ValueT>::Identifier(ValueT&& i_value) 
	: m_value(std::forward<ValueT>(i_value))
{
	// Nothing to do
}

template<typename TraitT, typename ValueT>
Identifier<TraitT, ValueT>::Identifier(const Identifier<TraitT, ValueT>& rhs) 
	: m_value(rhs.m_value)
{
	// Nothing to do
}

template<typename TraitT, typename ValueT>
Identifier<TraitT, ValueT>::Identifier(Identifier<TraitT, ValueT>&& rhs) 
	: m_value(std::move(rhs.m_value))
{
	// Nothing to do
}

template<typename TraitT, typename ValueT>
Identifier<TraitT, ValueT>& utils::Identifier<TraitT, ValueT>::operator=(const Identifier<TraitT, ValueT>& rhs) &
{
	if ( this != &rhs )
	{
		m_value = rhs.m_value;
	}
	return *this;
}

template<typename TraitT, typename ValueT>
Identifier<TraitT, ValueT>& utils::Identifier<TraitT, ValueT>::operator=(Identifier<TraitT, ValueT>&& rhs) &
{
	if ( this != &rhs )
	{
		m_value = std::move(rhs.m_value);
	}
	return *this;
}

template<typename TraitT, typename ValueT>
const ValueT& utils::Identifier<TraitT, ValueT>::GetValue() const&
{
	return m_value;
}

// Comparison Operators follows:

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

} //namespace utils