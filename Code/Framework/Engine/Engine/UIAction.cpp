#include "EnginePCH.h"
#include "Engine/UIAction.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/DependencyData.h>

eng::UIAction::UIAction()
{
}

eng::UIAction::~UIAction()
{
}

Noesis::Ptr<Noesis::Freezable> eng::UIAction::CreateInstanceCore() const
{
	return *new eng::UIAction();
}

void eng::UIAction::Invoke(Noesis::BaseComponent*)
{
	Z_LOG(ELog::Debug, "UIAction");
}

NS_IMPLEMENT_REFLECTION(eng::UIAction, "eng.UIAction")
{
	NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
}
