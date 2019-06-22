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
	Signal() = default;

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
			assert( "Slot Disconnected");
			if (IsConnected())
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
		bool IsConnected() const noexcept
		{
			return m_callback != nullptr;
		}
		void Disconnect() noexcept
		{
			m_callback = nullptr;
		}

	private:
		CallbackT m_callback;
		bool m_isBlocked;
	};

	class Connection  //ScopedConnection
	{
	public:
		Connection(const std::shared_ptr<Slot>& i_slot) 
			: m_slot(i_slot)

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
			m_slot->Disconnect();
		}

	private:
		std::shared_ptr<Slot> m_slot;
	};

public:
	Connection Connect(CallbackT i_callback)
	{
		std::shared_ptr<Slot> slot = std::make_shared<Slot>(i_callback);
		m_slots.emplace_back(slot);
		return Connection(slot);
	}

	void Emit(ArgT... i_args)
	{
		for ( std::shared_ptr<Slot>& slot : m_slots)
		{
			if (slot->IsConnected() && !slot->IsBlocked())
			{
				(*slot)(std::forward<ArgT>(i_args)...);
			}
		}
	}
private:
	using SlotPtr = std::shared_ptr<Slot>;
	using SlotsCollection = std::vector<SlotPtr>;
	SlotsCollection m_slots;
};

}