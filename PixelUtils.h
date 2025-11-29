#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "GlaxFunctionLibrary.generated.h"

/** Serializable structure for holding color data from a render target */
USTRUCT(BlueprintType)
struct FRTColorData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "RTData")
	TArray<FColor> Colors;

	UPROPERTY(BlueprintReadWrite, Category = "RTData")
	FIntPoint Size = FIntPoint::ZeroValue;
};

/** Blueprint-accessible functions for converting between Render Targets, Textures, and CPU color arrays */
UCLASS()
class UGlaxFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Read pixels from a render target into a serializable color array */
	UFUNCTION(BlueprintCallable, Category = "Glax|RenderTarget", meta = (WorldContext = "WorldContextObject"))
	static FRTColorData RenderTargetToColorArray(UObject* WorldContextObject, UTextureRenderTarget2D* RenderTarget);

	/** Create a transient Texture2D from a color array */
	UFUNCTION(BlueprintCallable, Category = "Glax|RenderTarget")
	static UTexture2D* ColorArrayToTexture2D(FRTColorData Data);

	/** Fill a render target from a color array. Returns true on success */
	UFUNCTION(BlueprintCallable, Category = "Glax|RenderTarget", meta = (WorldContext = "WorldContextObject"))
	static bool ColorArrayToRenderTarget(UObject* WorldContextObject, FRTColorData Data, UTextureRenderTarget2D* Target);
};
