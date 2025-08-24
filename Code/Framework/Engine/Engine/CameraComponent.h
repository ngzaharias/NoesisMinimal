#pragma once

#include "Core/Optional.h"
#include "Core/Variant.h"
#include "ECS/Component.h"
#include "Engine/CameraTypes.h"
#include "Math/Math.h"
#include "Math/Vector.h"

namespace eng::camera
{
	/// \brief
	struct ProjectionComponent final : public ecs::Component<ProjectionComponent>
	{
		eng::camera::Projection m_Projection = eng::camera::Perspective();
	};
}