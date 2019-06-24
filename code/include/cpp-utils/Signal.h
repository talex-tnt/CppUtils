#pragma once
#include <memory>
#include <vector>
#include <assert.h>
#include <thread>

namespace utils
{

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

private:
	class Slot;
	using SlotPtr		= std::shared_ptr<Slot>;
	using DeleteSlotFun = std::function<void(const SlotPtr&)>;
	using IsSlotConnectedFun = std::function<bool(const SlotPtr&)>;

public:
	using CallbackT = std::function<void(ArgsT...)>;
	class Connection;
	Connection Connect(CallbackT i_callback);
	
	template<typename _Fx, typename ... _Types>
	Connection ConnectB(_Fx&& i_fun, _Types&&... i_args); // std::bind(i_fun, i_args)

	void Emit(ArgsT... i_args);
	std::size_t GetSlotCount() const noexcept;

private:
	using SlotsCollection = std::vector<SlotPtr>;
	void DeleteSlot(const SlotPtr& i_slot);
	bool IsSlotConnected(const SlotPtr& i_slot) const;

private:
	SlotsCollection m_slots;
	std::shared_ptr<DeleteSlotFun> m_deleteSlotFun;
	std::shared_ptr<IsSlotConnectedFun> m_isSlotConnectedFun;
	const std::thread::id m_threadId;
};

//////////////////////////////////////////////////////////////////////////
//								Slot
//////////////////////////////////////////////////////////////////////////
template<typename ... ArgsT>
class Signal<ArgsT...>::Slot
{
public:
	Slot(CallbackT i_callback);
	Slot(Slot&&)					= default;
	Slot& operator=(Slot&&)			= default;
	~Slot()							= default;

	Slot(const Slot&)				= delete;
	Slot& operator=(const Slot&)	= delete;

	void operator()(ArgsT ... i_args);
	bool IsBlocked() const noexcept;
	void SetBlocked(bool i_isBlocked) noexcept;

private:
	CallbackT m_callback;
	bool m_isBlocked;
};

//////////////////////////////////////////////////////////////////////////
//							Connection
//////////////////////////////////////////////////////////////////////////
template<typename ... ArgsT>
class Signal<ArgsT...>::Connection  //ScopedConnection
{
	friend class Signal;
private:
	Connection(
		const std::shared_ptr<Slot>& i_slot, 
		const std::weak_ptr<DeleteSlotFun>& i_deleteSlotFun,
		const std::weak_ptr<IsSlotConnectedFun>& i_isSlotConnectedFun,
		std::thread::id i_threadId);
public:
	Connection();
	Connection(Connection&&);
	Connection& operator=(Connection&&);
	~Connection();

	Connection(const Connection&)				= delete;		//only 1 connection at the time
	Connection& operator=(const Connection&)	= delete;

	bool IsBlocked() const noexcept;
	void SetBlocked(bool i_isBlocked) noexcept;
	void Disconnect();
	bool IsConnected() const;

private:
	std::shared_ptr<Slot> m_slot;
	std::weak_ptr<DeleteSlotFun> m_deleteSlotFun;
	std::weak_ptr<IsSlotConnectedFun> m_isSlotConnectedFun;
	std::thread::id m_threadId;
};

} //namespace utils 

#include "Signal.inl"