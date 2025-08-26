#pragma once

#include <NsApp/TriggerAction.h>
#include <NsGui/DependencyObject.h>

namespace eng
{
	class UIAction final : public NoesisApp::TriggerActionT<Noesis::DependencyObject>
	{
	public:
		UIAction();
		~UIAction() override;

	protected:
		Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;

		void Invoke(Noesis::BaseComponent* parameter) override;

	protected:
		NS_DECLARE_REFLECTION(eng::UIAction, NoesisApp::TriggerActionT<Noesis::DependencyObject>)
	};
}