#pragma once
#include <memory>
#include <vector>
#include <thread>

namespace utils
{
class ISlot;
class Connection;

template<typename ... ArgsT>
class Signal
{
public:
	Signal();
	Signal(Signal&&)					= default;
	Signal& operator=(Signal&&)			= default;
	~Signal()							= default;

	Signal(const Signal&)				= delete;
	Signal& operator=(const Signal&)	= delete;

	using Connection = Connection;

public:
	using CallbackT = std::function<void(ArgsT...)>;
	Connection Connect(CallbackT i_callback);
	
	template<typename _Fx, typename ... _Types>
	Connection ConnectB(_Fx&& i_fun, _Types&&... i_args); // std::bind(i_fun, i_args)

	void Emit(ArgsT... i_args);
	std::size_t GetSlotCount() const noexcept;

private:
	using ISlotPtr = std::shared_ptr<ISlot>;

	void DeleteSlot(const ISlotPtr& i_slot);
	bool IsSlotConnected(const ISlotPtr& i_slot) const;

private:
	class Slot;
	using SlotPtr = std::shared_ptr<Slot>;
	using SlotsCollection = std::vector<SlotPtr>;
	SlotsCollection m_slots;

	using DeleteSlotFun = std::function<void(const ISlotPtr&)>;
	std::shared_ptr<DeleteSlotFun> m_deleteSlotFun;

	const std::thread::id m_threadId;
};

//////////////////////////////////////////////////////////////////////////
//							Connection
//////////////////////////////////////////////////////////////////////////
class Connection  //ScopedConnection
{
	//friend class Signal;
private:
	using SlotPtr = std::shared_ptr<ISlot>;
	using DeleteSlotFun = std::function<void(const SlotPtr&)>;

public:
	Connection(
		std::weak_ptr<ISlot> i_slot,
		std::weak_ptr<DeleteSlotFun> i_deleteSlotFun,
		std::thread::id i_threadId);
public:
	Connection();
	Connection(Connection&&);
	Connection& operator=(Connection&&);
	~Connection();

	Connection(const Connection&) = delete;		//only 1 connection at the time
	Connection& operator=(const Connection&) = delete;

	bool IsBlocked() const noexcept;
	void SetBlocked(bool i_isBlocked) noexcept;

	bool IsConnected() const;
	void Disconnect();

private:
	std::weak_ptr<ISlot> m_slot;
	std::weak_ptr<DeleteSlotFun> m_deleteSlotFun;
	std::thread::id m_threadId;
};

} //namespace utils 

#include "Signal.inl"