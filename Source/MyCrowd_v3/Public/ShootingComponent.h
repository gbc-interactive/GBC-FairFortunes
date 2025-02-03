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

	FTimerHandle m_gunReloadTimer;
	FTimerHandle m_grenadeReloadTimer;
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
	float reloadTime_Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float reloadTime_Grenade;

private:
	inline void EnableGun() { m_canShoot_Gun = true; }
	inline void EnableGrenade() { m_canLaunch_Grenade = true; }

protected:
	virtual void BeginPlay() override;

public:
	UShootingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void ShootGun(FVector bulletSpawnLocation);

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void LaunchGrenade();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadFull_GunAmmo();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadFixedAmount_GunAmmo(int amountToReload);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadFull_GrenadeAmmo();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void ReloadFullAmmo_AllWeapons();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadFixedAmount_GrenadeAmmo(int amountToReload);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	inline int GetCurrentAmmo_Gun() { return m_currentAmmo_Gun; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	inline int GetCurrentAmmo_Grenade() { return m_currentAmmo_Grenade; }
};
