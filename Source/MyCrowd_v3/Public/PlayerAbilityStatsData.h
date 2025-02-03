#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerAbilityStatsData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerWeaponStats {
    GENERATED_BODY()

    /* Ammo capacity for the player's gun. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "Gun Maximum Ammo"))
    int MaxAmmo_Gun = 10;

    /* Fire Rate for the player's gun, expressed in shots per second. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "Gun Fire Rate"))
    float fireRate_Gun = 2.0f;

    /* Time required for the gun to reload, expressed in seconds. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "Gun Reload Duration"))
    float reloadTime_Gun = 3.0f;

    /* Ammo capacity for the player's grenade pouch. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "Grenade Maximum Ammo"))
    int MaxAmmo_Grenade = 5;

    /* How often the player can throw a grenade, expressed in grenades per second. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "Grenade Fire Rate"))
    float fireRate_Grenade = 0.5f;

    /* Time required for the grenade pouch to reload, expressed in seconds. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "Grenade Reload Duration"))
    float reloadTime_Grenade = 5.0f;
};

USTRUCT(BlueprintType)
struct FPlayerMovementStats {
    GENERATED_BODY()

    /* The walk speed of the player, expressed in units per second. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "Walk Speed"))
    float walkSpeed = 400.0f;

    /* The sprint speed of the player, expressed in units per second. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "Sprint Speed"))
    float sprintSpeed = 600.0f;

    /* The speed of movement during ADS, expressed as a percentage of normal movement speed. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "ADS Movement Speed", ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
    float MovementSpeedMultiplierADS = 70.0f;

    /* Full stamina duration for the player, expressed in seconds. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "Stamina Duration"))
    float sprintStaminaDuration = 5.0f;

    /* Time required for the player's stamina to fully recover from empty, expressed in seconds. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "Stamina Full Recharge Cooldown"))
    float staminaRechargeCooldown = 2.5f;
};

USTRUCT(BlueprintType)
struct FPlayerInteractionStats {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Player Interact Range"))
    float interactionRange = 2.5f;

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Interact Detection Channel"))
    TEnumAsByte<ECollisionChannel> interactionRaycastChannel = ECC_Pawn;
};

USTRUCT(BlueprintType)
struct FProjectileSpawnerSystemData {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Gun Object Pool Size"))
    int gunProjectilePoolSize = 25;

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Gun Projectile"))
    TSubclassOf<class AProjectileBase> projectileToSpawn_Gun;

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Grenade Object Pool Size"))
    int grenadeProjectilePoolSize = 10;

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Grenade Projectile"))
    TSubclassOf<class AProjectileBase> projectileToSpawn_Grenade;
};

USTRUCT(BlueprintType)
struct FCameraData {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Normal Look sensitivity"))
    FVector2D lookSensitivity{ 1.5f, 1.0f };

    UPROPERTY(EditAnywhere, meta = (DisplayName = "ADS Look Sensitivity"))
    FVector2D ADSLookSensitivity{ 1.5f, 1.0f };

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Camera interpolation stopping tolerance"))
    float stoppingTolerance = 0.1f;

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Camera Rotation Speed"))
    float cameraRotationSpeed = 1.5f;

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Invert Y Axis"))
    bool invertYAxis = false;

    /* How much to reduce the FOV by when ADS-ing, as percentage. */
    UPROPERTY(EditAnywhere, meta = (DisplayName = "ADS-time FOV Reduction"))
    float fovReductionPercent = 30.0f;
};

UCLASS(BlueprintType)
class MYCROWD_V3_API UPlayerAbilityStatsData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    FPlayerWeaponStats weaponStats;

    UPROPERTY(EditAnywhere)
    FPlayerMovementStats movementStats;

    UPROPERTY(EditAnywhere)
    FPlayerInteractionStats interactionStats;

    UPROPERTY(EditAnywhere)
    FProjectileSpawnerSystemData projectileSpawnerSystemData;

    UPROPERTY(EditAnywhere)
    FCameraData cameraData;
};
