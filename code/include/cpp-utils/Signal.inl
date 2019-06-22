#pragma once

namespace utils
{

// Signal ////////////////////////////////////////////////////////////////

template<typename ... ArgsT>
inline utils::Signal<ArgsT...>::Signal()
	: m_deleteSlotFun(std::make_shared<DeleteSlotFun>(
		std::bind(&Signal::DeleteSlot, this, std::placeholders::_1)))
{ }

template<typename ... ArgsT>
inline typename utils::Signal<ArgsT...>::Connection
utils::Signal<ArgsT...>::Connect(CallbackT i_callback)
{
	std::shared_ptr<Slot> slot = std::make_shared<Slot>(i_callback);
	m_slots.emplace_back(slot);
	return Connection(slot, m_deleteSlotFun);
}

template<typename ... ArgsT>
inline void utils::Signal<ArgsT...>::Emit(ArgsT... i_args)
{
	for ( std::shared_ptr<Slot>& slot : m_slots )
	{
		if ( !slot->IsBlocked() )
		{
			( *slot )( std::forward<ArgsT>(i_args)... );
		}
	}
}

template<typename ... ArgsT>
void utils::Signal<ArgsT...>::DeleteSlot(const SlotPtr& i_slot)
{
	SlotsCollection::const_iterator end = m_slots.cend();
	SlotsCollection::const_iterator it = std::find(m_slots.cbegin(), end, i_slot);
	assert(it != end);
	if ( it != end )
	{
		m_slots.erase(it);
	}
}

template<typename ... ArgsT>
inline std::size_t utils::Signal<ArgsT...>::GetSlotCount() const noexcept
{
	return m_slots.size();
}

// Slot //////////////////////////////////////////////////////////////////////////

template<typename ... ArgsT>
inline utils::Signal<ArgsT...>::Slot::Slot(CallbackT i_callback) 
	: m_callback(i_callback), m_isBlocked(false)
{ }

template<typename ... ArgsT>
inline void utils::Signal<ArgsT...>::Slot::operator()(ArgsT ... i_args)
{
	assert(m_callback != nullptr);
	if ( m_callback != nullptr )
	{
		m_callback(std::forward<ArgsT>(i_args)...);
	}
}

template<typename ... ArgsT>
inline bool utils::Signal<ArgsT...>::Slot::IsBlocked() const noexcept
{
	return m_isBlocked;
}

template<typename ... ArgsT>
inline bool utils::Signal<ArgsT...>::Slot::SetBlocked(bool i_isBlocked) noexcept
{
	m_isBlocked = i_isBlocked;
}

// Connection //////////////////////////////////////////////////////////////////////////

template<typename  ... ArgsT>
inline utils::Signal<ArgsT...>::Connection::Connection(
	const std::shared_ptr<Slot>& i_slot, std::weak_ptr<DeleteSlotFun> i_deleteSlotFun) 
	: m_slot(i_slot), m_deleteSlotFun(i_deleteSlotFun)
{ }

template<typename ... ArgsT>
inline utils::Signal<ArgsT...>::Connection::~Connection()
{
	Disconnect();
}

template<typename ... ArgsT>
inline bool utils::Signal<ArgsT...>::Connection::IsBlocked() const noexcept
{
	return m_slot->IsBlocked();
}

template<typename ... ArgsT>
inline bool utils::Signal<ArgsT...>::Connection::SetBlocked(bool i_isBlocked) noexcept
{
	m_slot->SetBlocked(i_isBlocked);
}

template<typename ... ArgsT>
inline void utils::Signal<ArgsT...>::Connection::Disconnect() noexcept
{
	if ( m_slot )
	{
		if ( std::shared_ptr<DeleteSlotFun> slotDeleter = m_deleteSlotFun.lock() )
		{
			( *slotDeleter )( m_slot );
			m_slot = nullptr;
		}
	}
}

} //namespace utils