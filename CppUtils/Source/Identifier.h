#pragma once
#include <iosfwd>

#define DEFINE_IDENTIFIER(IdentifierName, IdentifierType) \
class IdentifierName ## Traits {}; \
struct IdentifierName : public utils::Identifier<IdentifierName ## Traits, IdentifierType> \
{ \
	using BaseT = utils::Identifier<IdentifierName ## Traits, IdentifierType>; \
	using BaseT::BaseT; \
}; 

#define DEFINE_IDENTIFIER_WITH_INVALID_VALUE(IdentifierName, IdentifierType, InvalidValue) \
class IdentifierName ## Traits {}; \
struct IdentifierName : public utils::InvalidableIdentifier<IdentifierName ## Traits, IdentifierType> \
{ \
	using BaseT = utils::InvalidableIdentifier<IdentifierName ## Traits, IdentifierType>; \
	using BaseT::BaseT; \
}; \
template<> \
const typename IdentifierName::ValueType \
IdentifierName::BaseT::k_invalidValue = InvalidValue; 

namespace utils
{

template<typename Traits, typename ValueT>
struct CmpIdentifier;

template<typename Traits, typename ValueT>
class Identifier
{
public:
	explicit Identifier(ValueT&& i_value);
	explicit Identifier(const ValueT& i_value);

	Identifier(const Identifier<Traits, ValueT>& rhs);
	Identifier<Traits, ValueT>& operator=(const Identifier<Traits, ValueT>& rhs)&;

	//move semantics
	explicit Identifier(Identifier<Traits, ValueT>&& rhs);
	Identifier<Traits, ValueT>& operator=(Identifier<Traits, ValueT>&& rhs)&;

	const ValueT& GetValue() const&;
	ValueT GetValue() const&&;

	template<typename Traits, typename ValueT>
	friend std::ostream& operator<<(std::ostream& o_stream, const Identifier<Traits, ValueT>& i_identifier);

	template<typename Traits, typename ValueT>
	friend std::istream& operator>>(std::istream& i_stream, Identifier<Traits, ValueT>& i_identifier);

	using ValueType = ValueT;

	struct LessCmp
	{
		bool operator()(const Identifier<Traits, ValueT>& lhs, const Identifier<Traits, ValueT>& rhs) const;
	};

	struct Hasher
	{
		std::size_t operator()(const Identifier<Traits, ValueT>& lhs) const;
	};

protected:	// This class is meant NOT to be deleted polymorphically
	~Identifier() = default;

private:
	/*const*/ ValueT m_value;

	static_assert(
		!std::is_reference<ValueT>::value,
		"ValueT cannot be a reference" );
	static_assert(
		!std::is_pointer<ValueT>::value,
		"ValueT cannot be a pointer" );
	static_assert(
		!std::is_void<ValueT>::value,
		"ValueT cannot be void" );
};


template<typename Traits, typename ValueT>
class InvalidableIdentifier : public Identifier<Traits, ValueT>
{
public:
	using ValueType = ValueT;
	InvalidableIdentifier();
	explicit InvalidableIdentifier(ValueT&& i_value);
	explicit InvalidableIdentifier(const ValueT& i_value);
	bool IsValid() const;
	static const ValueT k_invalidValue;
};

} //namespace utils

#include "Identifier.inl"