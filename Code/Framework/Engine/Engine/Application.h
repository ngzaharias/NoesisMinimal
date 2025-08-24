#pragma once

#include "ECS/EntityWorld.h"
#include "Engine/InputManager.h"
#include "Engine/UIManager.h"
#include "Engine/WindowManager.h"

class GameTime;

namespace eng
{
	class IWindow;
}

namespace eng
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Execute(int argc, char* argv[]);

	protected:
		virtual void Register();

		virtual void Initialise();
		virtual void Shutdown();

		virtual void PreUpdate(const GameTime& gameTime);
		virtual void Update(const GameTime& gameTime);
		virtual void PostUpdate(const GameTime& gameTime);

		virtual bool ShouldClose();

	protected:
		ecs::EntityWorld m_EntityWorld;
		eng::InputManager m_InputManager;
		eng::UIManager m_UIManager;
		eng::WindowManager m_WindowManager;
	};
}