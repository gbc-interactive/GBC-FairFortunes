#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYCROWD_V3_API UShootingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	
	bool m_canShoot_Gun;
	bool m_canLaunch_Grenade;

	int m_currentAmmo_Gun;
	int m_currentAmmo_Grenade;

	float m_delayBetweenShots_Gun;
	float m_delayBetweenThrows_Grenade;

	FTimerHandle m_gunShotDelayTimer;
	FTimerHandle m_grenadeDelayTimer;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int maxAmmo_Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int maxAmmo_Grenade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float fireRate_Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float fireRate_Grenade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AProjectileBase> projectileToSpawn_Gun;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AProjectileBase> projectileToSpawn_Grenade;

private:
	void EnableGun();
	void EnableGrenade();

protected:
	virtual void BeginPlay() override;

public:
	UShootingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void ShootGun();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void LaunchGrenade();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadFull_GunAmmo();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadFixedAmount_GunAmmo(int amountToReload);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadFull_GrenadeAmmo();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadFixedAmount_GrenadeAmmo(int amountToReload);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	inline int GetCurrentAmmo_Gun() { return m_currentAmmo_Gun; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	inline int GetCurrentAmmo_Grenade() { return m_currentAmmo_Grenade; }
};
