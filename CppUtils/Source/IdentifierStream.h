#pragma once
#include <iosfwd>

template <template <typename, typename> class Identifier, typename TraitT, typename ValueT>
std::ostream& operator<< (std::ostream& o_stream, const Identifier<TraitT, ValueT>& i_identifier)
{
	o_stream << i_identifier.GetValue();
	return o_stream;
}
