// MyFirstCoolTESTGame. All rights RESRVED!


#include "Animations/FCTBaseAnimNotify.h"

void UFCTBaseAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	
	Super::Notify(MeshComp, Animation);
}
