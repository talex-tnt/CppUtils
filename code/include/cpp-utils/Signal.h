#pragma once
#include <memory>
#include <vector>
#include <assert.h>

namespace utils
{

template<typename ... ArgT>
class Signal
{
public:
	Signal(const Signal&) = delete;
	Signal& operator=(const Signal&) = delete;

	Signal(Signal&&) = default;
	Signal& operator=(Signal&&) = default;

	~Signal() = default;


public:
	using CallbackT = std::function<void(ArgT...)>;

	class Slot
	{
	public:
		Slot(CallbackT i_callback) 
			: m_callback(i_callback)
			, m_isBlocked(false)
		{ }

		Slot(const Slot&) = delete;
		Slot& operator=(const Slot&) = delete;

		Slot(Slot&&) = default;
		Slot& operator=(Slot&&) = default;
		
		~Slot() = default;

		void operator()(ArgT ... i_args)
		{
			assert(m_callback != nullptr);
			if ( m_callback != nullptr )
			{
				m_callback(std::forward<ArgT>(i_args)...);
			}
		}
		bool IsBlocked() const noexcept 
		{ 
			return m_isBlocked; 
		}
		bool SetBlocked(bool i_isBlocked) noexcept
		{ 
			m_isBlocked = i_isBlocked; 
		}

	private:
		CallbackT m_callback;
		bool m_isBlocked;
	};
private:
	using SlotPtr = std::shared_ptr<Slot>;
	using DeleteSlotFun = std::function<void(const SlotPtr&)>;
	
public:
	class Connection  //ScopedConnection
	{
	public:
		Connection(const std::shared_ptr<Slot>& i_slot, std::weak_ptr<DeleteSlotFun> i_deleteSlotFun)
			: m_slot(i_slot), m_deleteSlotFun(i_deleteSlotFun)
		{ }

		Connection(const Connection&) = delete;		//only 1 connection at the time
		Connection& operator=(const Connection&) = delete;

		Connection(Connection&&) = default;
		Connection& operator=(Connection&&) = default;

		~Connection() 
		{
			Disconnect();
		}

		bool IsBlocked() const noexcept
		{
			return m_slot->IsBlocked();
		}
		bool SetBlocked(bool i_isBlocked) noexcept
		{
			m_slot->SetBlocked(i_isBlocked);
		}
		void Disconnect() noexcept
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

	private:
		std::shared_ptr<Slot> m_slot;
		std::weak_ptr<DeleteSlotFun> m_deleteSlotFun;
	};

public:
	Connection Connect(CallbackT i_callback)
	{
		std::shared_ptr<Slot> slot = std::make_shared<Slot>(i_callback);
		m_slots.emplace_back(slot);
		return Connection(slot, m_deleteSlotFun);
	}

	void Emit(ArgT... i_args)
	{
		for ( std::shared_ptr<Slot>& slot : m_slots)
		{
			if (!slot->IsBlocked())
			{
				(*slot)(std::forward<ArgT>(i_args)...);
			}
		}
	}

	std::size_t GetSlotCount() const noexcept
	{
		return m_slots.size();
	}

private:
	using SlotsCollection = std::vector<SlotPtr>;

	void DeleteSlot(const SlotPtr& i_slot)
	{
		SlotsCollection::const_iterator end = m_slots.cend();
		SlotsCollection::const_iterator it = std::find(m_slots.cbegin(), end, i_slot);
		assert(it != end);
		if (it != end)
		{
			m_slots.erase(it);
		}
	}

public:
	Signal() 
		: m_deleteSlotFun(std::make_shared<DeleteSlotFun>(
			std::bind(&Signal::DeleteSlot, this, std::placeholders::_1)))
	{  };

private:
	SlotsCollection m_slots;
	std::shared_ptr<DeleteSlotFun> m_deleteSlotFun;
};

}