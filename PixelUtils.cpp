#include "PixelUtils.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"
#include "RenderUtils.h"
#include "CanvasTypes.h"
#include "Engine/Canvas.h"
#include "Kismet/KismetRenderingLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogPixelUtils, Log, All);

FPixelColorData UPixelUtils::RenderTargetToColorArray(UObject* WorldContextObject, UTextureRenderTarget2D* RenderTarget)
{
    FPixelColorData Out;

    if (!RenderTarget)
    {
        UE_LOG(LogPixelUtils, Error, TEXT("RenderTargetToColorArray: RenderTarget is null"));
        return Out;
    }

    FTextureRenderTargetResource* RTResource = RenderTarget->GameThread_GetRenderTargetResource();
    if (!RTResource)
    {
        UE_LOG(LogPixelUtils, Error, TEXT("RenderTargetToColorArray: Failed to get render target resource"));
        return Out;
    }

    TArray<FColor> Pixels;
    if (!RTResource->ReadPixels(Pixels))
    {
        UE_LOG(LogPixelUtils, Error, TEXT("RenderTargetToColorArray: ReadPixels failed"));
        return Out;
    }

    Out.Colors = MoveTemp(Pixels);
    Out.Size = FIntPoint(RenderTarget->SizeX, RenderTarget->SizeY);
    return Out;
}

UTexture2D* UPixelUtils::ColorArrayToTexture2D(FPixelColorData Data)
{
    if (Data.Size.X <= 0 || Data.Size.Y <= 0)
    {
        UE_LOG(LogPixelUtils, Error, TEXT("ColorArrayToTexture2D: Invalid size"));
        return nullptr;
    }
    if (Data.Colors.Num() != Data.Size.X * Data.Size.Y)
    {
        UE_LOG(LogPixelUtils, Error, TEXT("ColorArrayToTexture2D: Color array length does not match dimensions"));
        return nullptr;
    }

    UTexture2D* Texture = UTexture2D::CreateTransient(Data.Size.X, Data.Size.Y, PF_B8G8R8A8);
    if (!Texture)
    {
        UE_LOG(LogPixelUtils, Error, TEXT("ColorArrayToTexture2D: Failed to create transient texture"));
        return nullptr;
    }

    Texture->CompressionSettings = TC_Default;
    Texture->SRGB = false;

    Texture->AddToRoot();
    Texture->UpdateResource();

    FTexture2DMipMap& Mip = Texture->GetPlatformData()->Mips[0];
    void* MipData = Mip.BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(MipData, Data.Colors.GetData(), Data.Colors.Num() * sizeof(FColor));
    Mip.BulkData.Unlock();

    Texture->UpdateResource();
    Texture->RemoveFromRoot();

    return Texture;
}

bool UPixelUtils::ColorArrayToRenderTarget(UObject* WorldContextObject, FPixelColorData Data, UTextureRenderTarget2D* Target)
{
    if (!Target)
    {
        UE_LOG(LogPixelUtils, Error, TEXT("ColorArrayToRenderTarget: Target is null"));
        return false;
    }

    if (Data.Size.X != Target->SizeX || Data.Size.Y != Target->SizeY)
    {
        UE_LOG(LogPixelUtils, Warning, TEXT("ColorArrayToRenderTarget: Data size and target size differ (will attempt to draw scaled)"));
    }

    UTexture2D* SrcTex = ColorArrayToTexture2D(Data);
    if (!SrcTex) return false;

    UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    if (!World)
    {
        UE_LOG(LogPixelUtils, Error, TEXT("ColorArrayToRenderTarget: Invalid WorldContextObject"));
        return false;
    }

    UCanvas* Canvas = nullptr;
    FVector2D Size;
    FDrawToRenderTargetContext Context;
    UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(WorldContextObject, Target, Canvas, Size, Context);
    if (!Canvas)
    {
        UE_LOG(LogPixelUtils, Error, TEXT("ColorArrayToRenderTarget: Failed to begin drawing to render target"));
        UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(WorldContextObject, Context);
        return false;
    }

    Canvas->K2_DrawTexture(SrcTex, FVector2D(0, 0), Size, FVector2D(0, 0));

    UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(WorldContextObject, Context);

    return true;
}
