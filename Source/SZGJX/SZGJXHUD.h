// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SZGJXHUD.generated.h"

UCLASS()
class ASZGJXHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASZGJXHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

