#pragma once

namespace utils
{
template<typename Traits, typename ValueT>
Identifier<Traits, ValueT>::Identifier(ValueT&& i_value)
	: m_value(std::move(i_value))
{
	// Nothing to do
}

template<typename Traits, typename ValueT>
Identifier<Traits, ValueT>::Identifier(const ValueT& i_value)
	: m_value(i_value)
{
	// Nothing to do
}

template<typename Traits, typename ValueT>
Identifier<Traits, ValueT>::Identifier(const Identifier<Traits, ValueT>& rhs)
	: m_value(rhs.m_value)
{
	// Nothing to do
}

template<typename Traits, typename ValueT>
Identifier<Traits, ValueT>::Identifier(Identifier<Traits, ValueT>&& rhs)
	: m_value(std::move(rhs.m_value))
{
	// Nothing to do
}

template<typename Traits, typename ValueT>
Identifier<Traits, ValueT>& Identifier<Traits, ValueT>::operator=(const Identifier<Traits, ValueT>& rhs) &
{
	if ( this != &rhs )
	{
		m_value = rhs.m_value;
	}
	return *this;
}

template<typename Traits, typename ValueT>
Identifier<Traits, ValueT>& Identifier<Traits, ValueT>::operator=(Identifier<Traits, ValueT>&& rhs) &
{
	if ( this != &rhs )
	{
		m_value = std::move(rhs.m_value);
	}
	return *this;
}

template<typename Traits, typename ValueT>
const ValueT& Identifier<Traits, ValueT>::GetValue() const&
{
	return m_value;
}

template<typename Traits, typename ValueT>
ValueT Identifier<Traits, ValueT>::GetValue() const&&
{
	return std::move(m_value);
}

// Comparison Operators follows:

template<typename Traits, typename ValueT>
inline bool operator==(const Identifier<Traits, ValueT>& lhs, const Identifier<Traits, ValueT>& rhs)
{
	return lhs.GetValue() == rhs.GetValue();
}

template<typename Traits, typename ValueT>
inline bool operator!=(const Identifier<Traits, ValueT>& lhs, const Identifier<Traits, ValueT>& rhs)
{
	return !( lhs == rhs );
}

template<typename Traits, typename ValueT>
InvalidableIdentifier<Traits, ValueT>::InvalidableIdentifier()
	: Identifier(k_invalidValue)
{
	// Nothing to do
}

template<typename Traits, typename ValueT>
InvalidableIdentifier<Traits, ValueT>::InvalidableIdentifier(ValueT&& i_value)
	: Identifier(std::move(i_value))
{
	// Nothing to do
}

template<typename Traits, typename ValueT>
InvalidableIdentifier<Traits, ValueT>::InvalidableIdentifier(const ValueT& i_value)
	: Identifier(i_value)
{
	// Nothing to do
}

template<typename Traits, typename ValueT>
bool InvalidableIdentifier<Traits, ValueT>::IsValid() const
{
	return GetValue() != k_invalidValue;
}

template<typename Traits, typename ValueT>
inline std::ostream& operator<<(std::ostream& o_stream, const Identifier<Traits, ValueT>& i_identifier)
{
	o_stream << i_identifier.GetValue();
	return o_stream;
}

template<typename Traits, typename ValueT>
inline std::istream& operator>>(std::istream& i_stream, Identifier<Traits, ValueT>& i_identifier)
{
	i_stream >> i_identifier.m_value;
	return i_stream;
}

} //namespace utils


