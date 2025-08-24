#include "EnginePCH.h"
#include "Engine/Application.h"

#include "Core/GameTime.h"
#include "ECS/WorldView.h"
#include "Engine/CameraComponent.h"
#include "Engine/FileHelpers.h"
#include "Engine/RenderSystem.h"
#include "Engine/TransformComponent.h"
#include "Engine/Window.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <optick.h>
#include <random>
#include <time.h>

eng::Application::Application()
	: m_EntityWorld()
	, m_UIManager(m_EntityWorld)
	, m_WindowManager()
{
	srand((unsigned int)time(NULL));
}

eng::Application::~Application()
{
}

void eng::Application::Execute(int argc, char* argv[])
{
	Register();
	Initialise();

	GameTime gameTime;

	double currTime = 0.0;
	double lastTime = 0.0;
	bool isWaitingForProfiler = false;
	while (true)
	{
		PROFILE_TICK("MainThread");

		// profiling
		{
			if (isWaitingForProfiler && !profile::IsActive())
				continue;

			isWaitingForProfiler = false;
		}

		lastTime = currTime;
		currTime = glfwGetTime();

		gameTime.m_DeltaTime = static_cast<float>(currTime - lastTime);
		gameTime.m_TotalTime += gameTime.m_DeltaTime;
		gameTime.m_Frame++;

		{
			PROFILE_CUSTOM("eng::Application::Execute");

			PreUpdate(gameTime);
			Update(gameTime);
			PostUpdate(gameTime);

			if (ShouldClose())
				break;
		}
	}

	Shutdown();
}

void eng::Application::Register()
{
	m_EntityWorld.RegisterComponent<eng::camera::ProjectionComponent>();
	m_EntityWorld.RegisterComponent<eng::TransformComponent>();
	m_EntityWorld.RegisterResource(m_InputManager);
	m_EntityWorld.RegisterResource(m_UIManager);
	m_EntityWorld.RegisterResource(m_WindowManager);
	m_EntityWorld.RegisterSystem<eng::RenderSystem>(m_EntityWorld);
}

void eng::Application::Initialise()
{
	PROFILE_FUNCTION();

	// do first
	m_WindowManager.Initialise();

	m_EntityWorld.Initialise();
	m_UIManager.Initialise(*m_WindowManager.GetWindow(0));
	m_UIManager.CreateWidget(NAME("MainWindow.xaml"));

	{
		const auto& windowManager = m_EntityWorld.ReadResource<eng::WindowManager>();
		m_UIManager.Initialise(*windowManager.GetWindow(0));

		input::Layer layer;
		layer.m_Priority = eng::EInputPriority::GameUI;
		layer.m_Callback.Connect(m_UIManager, &eng::UIManager::ProcessInput);
		m_InputManager.AppendLayer(NAME("Noesis"), layer);
	}
}

void eng::Application::PreUpdate(const GameTime& gameTime)
{
	// do first
	m_WindowManager.PreUpdate(gameTime);

	auto inputWorld = m_EntityWorld.GetWorldView<eng::InputManager::World>();
	m_InputManager.Update(inputWorld);
}

void eng::Application::Update(const GameTime& gameTime)
{
	PROFILE_FUNCTION();

	m_EntityWorld.Update(gameTime);
	m_UIManager.Update(gameTime);
}

void eng::Application::PostUpdate(const GameTime& gameTime)
{
	// do last
	m_WindowManager.PostUpdate(gameTime);
}

void eng::Application::Shutdown()
{
	PROFILE_FUNCTION();

	m_EntityWorld.Shutdown();
	m_UIManager.Shutdown();
	// do last
	m_WindowManager.Shutdown();
}

bool eng::Application::ShouldClose()
{
	const eng::Window* window = m_WindowManager.GetWindow(0);
	return window && window->ShouldClose();
}
