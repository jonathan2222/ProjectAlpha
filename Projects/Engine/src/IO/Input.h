#ifndef PA_INPUT_H
#define PA_INPUT_H

#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

class Display;
namespace pa
{
	class Input
	{
	public:
		using Key = sf::Keyboard::Key;
		using MB = sf::Mouse::Button;

		enum State
		{
			Pressed = true,
			Released = false
		};

		/*
			Get the instance of Input.
		*/
		static Input& get();

		/*
			Initialize the class.
		*/
		void init(Display& display);

		/*
			Check for events. This should be called once each frame.
		*/
		void update();

		/*
			Return true if the key was in the same state as requested.
			Arguments:
				state: The state to request compare.
				key: The key to check.
		*/
		bool isKey(const State& state, const Key& key) const;

		/*
			Return true if the mouse button was in the same state as requested.
			Arguments:
				state: The state to request compare.
				button: The mouse button to check.
		*/
		bool isMB(const State& state, const MB& button) const;

		/*
			Get the change in mouse wheel delat.
			Usually returns -1 if scrolled down and 1 if up.
		*/
		float getMouseWheelDelta() const;

		/*
			Check if the mouse moved.
		*/
		bool hasMouseMoved() const;

		/*
			Get the mouse position.
		*/
		sf::Vector2i getMousePosition() const;

	private:
		void resetVars();
		void updateWindow(const sf::Event& e);
		void updateKeys(const sf::Event& e);
		void updateMouse(const sf::Event& e);

		std::unordered_map<sf::Keyboard::Key, State> keyboardMap;
		std::unordered_map<sf::Mouse::Button, State> mouseMap;

		// Mouse
		float mouseWheelDelta;
		sf::Vector2i mousePos;
		bool mouseMoved;

		Display* display;
	};
}

#endif