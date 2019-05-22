#pragma once
#include <type_traits>

#define DEFINE_IDENTIFIER(IdentifierName, IdentifierType) \
class IdentifierName ## Trait {}; \
struct IdentifierName : public utils::Identifier<IdentifierName ## Trait, IdentifierType> \
{ \
	using BaseT = utils::Identifier<IdentifierName ## Trait, IdentifierType>; \
	using BaseT::BaseT; \
}; 

#define DEFINE_IDENTIFIER_WITH_INVALID_VALUE(IdentifierName, IdentifierType, InvalidValue) \
class IdentifierName ## Trait {}; \
struct IdentifierName : public utils::InvalidableIdentifier<IdentifierName ## Trait, IdentifierType> \
{ \
	using BaseT = utils::InvalidableIdentifier<IdentifierName ## Trait, IdentifierType>; \
	using BaseT::BaseT; \
}; \
template<> \
const typename IdentifierName::ValueType \
IdentifierName::k_invalidValue = InvalidValue; 

namespace utils
{
template<typename TraitT, typename ValueT>
class Identifier
{
public:
	explicit Identifier(ValueT&& i_value);
	explicit Identifier(const ValueT& i_value);

	Identifier(const Identifier<TraitT, ValueT>& rhs);
	Identifier<TraitT, ValueT>& operator=(const Identifier<TraitT, ValueT>& rhs)&;

	//move semantics
	explicit Identifier(Identifier<TraitT, ValueT>&& rhs);
	Identifier<TraitT, ValueT>& operator=(Identifier<TraitT, ValueT>&& rhs)&;

	const ValueT& GetValue() const&;
	ValueT GetValue() const&&;

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


template<typename TraitT, typename ValueT>
class InvalidableIdentifier : public Identifier<TraitT, ValueT>
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