#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

class InputManager
{
public:
	//Singleton class
	static InputManager* instance();

	inline bool getKey(unsigned int keyCode) const { return m_keys[keyCode]; }
	inline double getMouseX() const { return m_mouseX; }
	inline double getMouseY() const { return m_mouseY; }
	inline double getScrollX() const { return m_scrollX; }
	inline double getScrollY() const { return m_scrollY; }

	inline void setKey(unsigned int keyCode, bool value) { m_keys[keyCode] = value; }
	inline void setMouseX(double newX) { m_mouseX = newX; }
	inline void setMouseY(double newY) { m_mouseY = newY; }
	inline void setScrollX(double newX) { m_scrollX = newX; }
	inline void setScrollY(double newY) { m_scrollY = newY; }
private:
	//Singleton class
	InputManager(){};
	InputManager(InputManager const&){};
	InputManager& operator=(InputManager const&){};
	static InputManager* m_instance;

	//All keys
	bool m_keys[1024];

	//Mouse coordinates
	double m_mouseX = 0.0, m_mouseY = 0.0;

	//Scroll wheel offsets
	double m_scrollX = 0.0, m_scrollY = 0.0;
};

#endif