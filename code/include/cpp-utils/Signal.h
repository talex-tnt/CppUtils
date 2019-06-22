#pragma once
#include <memory>
#include <vector>
#include <assert.h>

namespace utils
{

template<typename ... ArgsT>
class Signal
{
public:
	Signal();
	Signal(const Signal&)				= delete;
	Signal& operator=(const Signal&)	= delete;
	Signal(Signal&&)					= default;
	Signal& operator=(Signal&&)			= default;
	~Signal()							= default;

public:
	using CallbackT = std::function<void(ArgsT...)>;

	class Slot
	{
	public:
		Slot(CallbackT i_callback);
		Slot(const Slot&)				= delete;
		Slot& operator=(const Slot&)	= delete;
		Slot(Slot&&)					= default;
		Slot& operator=(Slot&&)			= default;
		~Slot()						    = default;

		void operator()(ArgsT ... i_args);
		bool IsBlocked() const noexcept;
		bool SetBlocked(bool i_isBlocked) noexcept;

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
		Connection(const std::shared_ptr<Slot>& i_slot, std::weak_ptr<DeleteSlotFun> i_deleteSlotFun);
		Connection(const Connection&)				= delete;		//only 1 connection at the time
		Connection& operator=(const Connection&)	= delete;
		Connection(Connection&&)					= default;
		Connection& operator=(Connection&&)			= default;
		~Connection();

		bool IsBlocked() const noexcept;
		bool SetBlocked(bool i_isBlocked) noexcept;
		void Disconnect() noexcept;

	private:
		std::shared_ptr<Slot> m_slot;
		std::weak_ptr<DeleteSlotFun> m_deleteSlotFun;
	};

public:
	Connection Connect(CallbackT i_callback);

	void Emit(ArgsT... i_args);

	std::size_t GetSlotCount() const noexcept;

private:
	using SlotsCollection = std::vector<SlotPtr>;

	void DeleteSlot(const SlotPtr& i_slot);

private:
	SlotsCollection m_slots;
	std::shared_ptr<DeleteSlotFun> m_deleteSlotFun;
};

} //namespace utils 

#include "Signal.inl"