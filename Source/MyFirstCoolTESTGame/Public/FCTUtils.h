#pragma once

class FCTUtils
{
public:
	template<typename T>
	static T* GetFCTPlayerComponent(APawn* PlayerPawn)
	{
		if(!PlayerPawn) return nullptr;
		const auto ActorComponent = PlayerPawn->GetComponentByClass(T::StaticClass());
		
		return Cast<T>(ActorComponent);
	}
};