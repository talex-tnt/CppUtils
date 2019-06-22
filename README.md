# CppUtils
C++ Utilities: basic utility library in C++

### Identifier
It creates a new domain of identifiers that share the same basic type (e.g. int, string, char):
```c++
DEFINE_IDENTIFIER(PlayerId, std::uint32_t);
DEFINE_IDENTIFIER(PlayerName, std::string);
DEFINE_IDENTIFIER(PlayerLevel, std::uint32_t);
```
these identifiers are meant to be used when designing and implementing new APIs that require/provide information about some specific domain. 

Here's an example:

```c++
class PlayerDef
{
public:
  PlayerId GetId() const { return m_id; }
  const PlayerName& GetName() const& { return m_name; }
// other stuff ...
private:
  PlayerId m_id;
  PlayerName m_name;
}

class PlayerState
{
public:
  PlayerId GetId() const { return m_id; }
  PlayerLevel GetCurrentLevel() const { return m_currentLevel; }
  // ...
private:
  PlayerId m_id;
  PlayerLevel m_currentLevel;
}


const PlayerDef& FindPlayerDef(PlayerId i_id);
const PlayerState& FindPlayerState(PlayerId i_id);


class PlayerWidget
{
public:
  using OnSelectSig = boost::signal<void (PlayerId)>;
  using Connection boost::signals::connection;
  using SlotFunType = OnSelectSig::slot_function_type;
  // ...
  PlayerWidget(PlayerId i_playerId, const PlayerName& i_name, PlayerImageId i_playerImageId);
  Connection DoOnSelected(SlotFunType i_slot);
  // ...
 private:
  PlayerId m_playerId;
  OnSelectSig m_onSelectSignal;
}
