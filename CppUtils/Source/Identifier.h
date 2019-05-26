#pragma once
#include <iosfwd>

#define DEFINE_IDENTIFIER(IdentifierName, IdentifierType) \
struct IdentifierName : public utils::Identifier<IdentifierType> \
{ \
	using BaseT = utils::Identifier<IdentifierType>; \
	using BaseT::BaseT; \
}; 

#define DEFINE_IDENTIFIER_WITH_INVALID_VALUE(IdentifierName, IdentifierType, InvalidValue) \
struct IdentifierName : public utils::InvalidableIdentifier<IdentifierType> \
{ \
	using BaseT = utils::InvalidableIdentifier<IdentifierType>; \
	using BaseT::BaseT; \
}; \
template<> \
const typename IdentifierName::ValueType \
IdentifierName::BaseT::k_invalidValue = InvalidValue; 

namespace utils
{

template<typename ValueT>
struct CmpIdentifier;

template<typename ValueT>
class Identifier
{
public:
	explicit Identifier(ValueT&& i_value);
	explicit Identifier(const ValueT& i_value);

	Identifier(const Identifier<ValueT>& rhs);
	Identifier<ValueT>& operator=(const Identifier<ValueT>& rhs)&;

	//move semantics
	explicit Identifier(Identifier<ValueT>&& rhs);
	Identifier<ValueT>& operator=(Identifier<ValueT>&& rhs)&;

	const ValueT& GetValue() const&;
	ValueT GetValue() const&&;

	template<typename ValueT>
	friend std::ostream& operator<<(std::ostream& o_stream, const Identifier<ValueT>& i_identifier);

	template<typename ValueT>
	friend std::istream& operator>>(std::istream& i_stream, Identifier<ValueT>& i_identifier);

	using ValueType = ValueT;

	struct LessCmp
	{
		bool operator()(const Identifier<ValueT>& lhs, const Identifier<ValueT>& rhs) const;
	};

	struct Hasher
	{
		std::size_t operator()(const Identifier<ValueT>& lhs) const;
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


template<typename ValueT>
class InvalidableIdentifier : public Identifier<ValueT>
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