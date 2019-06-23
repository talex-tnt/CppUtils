#pragma once

namespace utils
{

// Signal ////////////////////////////////////////////////////////////////

template<typename ... ArgsT>
inline utils::Signal<ArgsT...>::Signal()
	: m_deleteSlotFun(std::make_shared<DeleteSlotFun>(
		std::bind(&Signal::DeleteSlot, this, std::placeholders::_1)))
	, m_isSlotConnectedFun(std::make_shared<IsSlotConnectedFun>(
		std::bind(&Signal::IsSlotConnected, this, std::placeholders::_1)))
	, m_threadId(std::this_thread::get_id())
{ }

template<typename ... ArgsT>
inline typename utils::Signal<ArgsT...>::Connection
utils::Signal<ArgsT...>::Connect(CallbackT i_callback)
{
	assert(m_threadId == std::this_thread::get_id());
	std::shared_ptr<Slot> slot = std::make_shared<Slot>(i_callback);
	m_slots.emplace_back(slot);
	return Connection(slot, m_deleteSlotFun, m_isSlotConnectedFun, m_threadId);
}

template<typename ... ArgsT>
template<typename _Fx, typename ... _Types>
inline typename utils::Signal<ArgsT...>::Connection
utils::Signal<ArgsT...>::ConnectB(_Fx&& i_fun, _Types&&... i_args)
{
	assert(m_threadId == std::this_thread::get_id());
	std::shared_ptr<Slot> slot = std::make_shared<Slot>(
		std::bind(std::forward<_Fx>(i_fun), std::forward<_Types>(i_args)...)
	);
	m_slots.emplace_back(slot);
	return Connection(slot, m_deleteSlotFun, m_isSlotConnectedFun, m_threadId);
}

template<typename ... ArgsT>
inline void utils::Signal<ArgsT...>::Emit(ArgsT... i_args)
{
	assert(m_threadId == std::this_thread::get_id());
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
	assert(m_threadId == std::this_thread::get_id());

	SlotsCollection::const_iterator end = m_slots.cend();
	SlotsCollection::const_iterator it = std::find(m_slots.cbegin(), end, i_slot);
	assert(it != end);
	if ( it != end )
	{
		m_slots.erase(it);
	}
}

template<typename ... ArgsT>
bool utils::Signal<ArgsT...>::IsSlotConnected(const SlotPtr& i_slot) const
{
	assert(m_threadId == std::this_thread::get_id());
	SlotsCollection::const_iterator end = m_slots.cend();
	SlotsCollection::const_iterator it = std::find(m_slots.cbegin(), end, i_slot);
	return ( it != end );
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
inline void utils::Signal<ArgsT...>::Slot::SetBlocked(bool i_isBlocked) noexcept
{
	m_isBlocked = i_isBlocked;
}

// Connection //////////////////////////////////////////////////////////////////////////

template<typename  ... ArgsT>
inline utils::Signal<ArgsT...>::Connection::Connection(
	const std::shared_ptr<Slot>& i_slot, 
	const std::weak_ptr<DeleteSlotFun>& i_deleteSlotFun,
	const std::weak_ptr<IsSlotConnectedFun>& i_isSlotConnectedFun,
	const std::thread::id i_threadId)
	: m_slot(i_slot), m_deleteSlotFun(i_deleteSlotFun), m_isSlotConnectedFun(i_isSlotConnectedFun), m_threadId(i_threadId)
{ }

template<typename ... ArgsT>
inline utils::Signal<ArgsT...>::Connection::~Connection()
{
	assert(m_threadId == std::this_thread::get_id());
	Disconnect();
}

template<typename ... ArgsT>
inline bool utils::Signal<ArgsT...>::Connection::IsBlocked() const noexcept
{
	assert(m_threadId == std::this_thread::get_id());
	return m_slot->IsBlocked();
}

template<typename ... ArgsT>
inline void utils::Signal<ArgsT...>::Connection::SetBlocked(bool i_isBlocked) noexcept
{
	assert(m_threadId == std::this_thread::get_id());
	m_slot->SetBlocked(i_isBlocked);
}

template<typename ... ArgsT>
inline void utils::Signal<ArgsT...>::Connection::Disconnect() noexcept
{
	assert(m_threadId == std::this_thread::get_id());
	if ( m_slot )
	{
		if ( std::shared_ptr<DeleteSlotFun> slotDeleter = m_deleteSlotFun.lock() )
		{
			( *slotDeleter )( m_slot );
			m_slot = nullptr;
		}
	}
}

template<typename ... ArgsT>
inline bool utils::Signal<ArgsT...>::Connection::IsConnected() const
{
	assert(m_threadId == std::this_thread::get_id());
	if ( m_slot )
	{
		if ( std::shared_ptr<IsSlotConnectedFun> isSlotConnectedFun = m_isSlotConnectedFun.lock() )
		{
			return ( *isSlotConnectedFun )( m_slot );
		}
	}
	return false;
}

} //namespace utils