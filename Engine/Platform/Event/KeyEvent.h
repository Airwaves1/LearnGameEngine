#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "Event/Event.h"

namespace Airwave
{
class KeyEvent : public Event
	{
	public:
	   inline int GetKeycode() const { return m_Keycode;}

	   EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	protected:
		KeyEvent(int keycode)
			: m_Keycode(keycode){}
		int m_Keycode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int keyRepeated)
			:KeyEvent(keycode), m_KeyRepeated(keyRepeated) {}
		inline int GetRepeated() const { return m_KeyRepeated; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:\n KeyCode : " << m_Keycode << " KeyRepeated: " << m_KeyRepeated;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int m_KeyRepeated;
	};
	   
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode) {}
		EVENT_CLASS_TYPE(KeyReleased)

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:\n KeyCode : " << m_Keycode;
			return ss.str();
		}
	
	protected:
	
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			:KeyEvent(keycode) {}
		EVENT_CLASS_TYPE(KeyTyped)

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent:\n KeyCode : " << m_Keycode;
			return ss.str();
		}

	protected:

	};
}


#endif // !KEY_EVENT_H