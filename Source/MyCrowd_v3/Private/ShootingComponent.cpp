#include "ShootingComponent.h"
#include "FFLogger.h"
#include "ProjectileSpawnerSubsystem.h"
#include <Kismet/KismetMathLibrary.h>

UShootingComponent::UShootingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UShootingComponent::BeginPlay()
{
	//Super::BeginPlay();

	m_delayBetweenShots_Gun = 1.0f / fireRate_Gun;
	m_delayBetweenThrows_Grenade = 1.0f / fireRate_Grenade;

	m_currentAmmo_Gun = maxAmmo_Gun;
	m_currentAmmo_Grenade = maxAmmo_Grenade;

	m_canLaunch_Grenade = true;
	m_canShoot_Gun = true;

	projectileSpawnPoint = Cast<USceneComponent>(GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), TEXT("projectileSpawnPoint"))[0]);

	//init object pool for gun projectile
	GetWorld()->GetSubsystem<UProjectileSpawnerSubsystem>()->InitializeSubsystem(projectileToSpawn_GunClass, maxAmmo_Gun, projectileToSpawn_GrenadeClass, maxAmmo_Grenade);
}


void UShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_WorldStatic;

	APlayerCameraManager* m_playerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector cameraLocation;
	FRotator cameraRotation;
	m_playerCamera->GetCameraViewPoint(cameraLocation, cameraRotation);
	FHitResult Hit;

	FVector TraceStart = cameraLocation;//projectileSpawnPosition->GetComponentLocation();
	FVector TraceEnd = cameraLocation + UKismetMathLibrary::GetForwardVector(cameraRotation) * 1000.0f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(m_playerCamera);

	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 0, 10.0f);

	DrawDebugLine(GetWorld(), projectileSpawnPoint->GetComponentLocation(), TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 0, 10.0f);


	DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.0f, 10, FColor::Green, false, 0, 10.0f);
}

void UShootingComponent::ShootGun(FVector bulletSpawnLocation)
{
	if(m_canShoot_Gun == false)
	{
		FFLogger::LogMessage(LogMessageSeverity::Debug, "Cannot shoot gun yet");
		return;
	}

	if(m_currentAmmo_Gun <= 0)
	{
		FFLogger::LogMessage(LogMessageSeverity::Debug, "Out of bullets");
		ReloadFull_GunAmmo();
		return;
	}

	m_currentAmmo_Gun--;

	//step 1: find the right direction for the projectile
	APlayerCameraManager* m_playerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	APawn* m_pawn = Cast<APawn>(GetOwner());

	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_WorldStatic;

	FVector cameraLocation;
	FRotator cameraRotation;
	m_playerCamera->GetCameraViewPoint(cameraLocation, cameraRotation);
	FHitResult Hit;

	FVector TraceStart = cameraLocation;//projectileSpawnPosition->GetComponentLocation();
	FVector TraceEnd = cameraLocation + UKismetMathLibrary::GetForwardVector(cameraRotation) * 1000.0f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(m_playerCamera);

	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 0, 10.0f);

	DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.0f, 10, FColor::Green, false, 0, 10.0f);

	//FVector charMeshPosition = m_pawn->FindComponentByClass<USkeletalMeshComponent>()->GetComponentLocation();

	FRotator rotationToSet;// = UKismetMathLibrary::FindLookAtRotation(projectileSpawnPoint->GetComponentLocation(), Hit.ImpactPoint);
	if (Hit.bBlockingHit)
	{
		rotationToSet = UKismetMathLibrary::FindLookAtRotation(projectileSpawnPoint->GetComponentLocation(), Hit.ImpactPoint);
	}
	else
	{
		rotationToSet = UKismetMathLibrary::FindLookAtRotation(projectileSpawnPoint->GetComponentLocation(), TraceEnd);
	}


	//DrawDebugLine(GetWorld(), charMeshPosition, Hit.ImpactPoint, FColor::Red, false, 0, 10.0f);
	//m_pawn->SetActorRotation(FRotator::MakeFromEuler(FVector(0, 0, rotationToSet.Euler().Z)));


	//step2: instantiate the projectile provided as the bullet, the projectile is assumed to perform its own movement
	//projectileToSpawn_Grenade
	FFLogger::LogMessage(LogMessageSeverity::Debug, "Shooting gun"); 
	//GetWorld()->GetSubsystem<UProjectileSpawnerSubsystem>()->SpawnGunProjectile(bulletSpawnLocation, GetOwner()->GetActorRotation());
	GetWorld()->GetSubsystem<UProjectileSpawnerSubsystem>()->SpawnGunProjectile(projectileSpawnPoint->GetComponentLocation(), rotationToSet);

	//step 3: set a timer to delay the next shot
	GetWorld()->GetTimerManager().SetTimer(m_gunShotDelayTimer, this, &UShootingComponent::EnableGun, m_delayBetweenThrows_Grenade);
}

void UShootingComponent::LaunchGrenade()
{
	if (m_canLaunch_Grenade == false)
	{
		FFLogger::LogMessage(LogMessageSeverity::Debug, "Cannot launch grenade yet");
		return;
	}

	if (m_currentAmmo_Grenade <= 0)
        //AProjectileBase* spawnedBullet = GetWorld()->GetSubsystem<USpawnPoolSubsystem>()->SpawnFromPool(projectileToSpawn_Gun, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
	{
		FFLogger::LogMessage(LogMessageSeverity::Debug, "Out of grenades");
		return;
	}

	m_currentAmmo_Grenade--;

	//step1: instantiate the projectile provided as the grenade, the projectile is assumed to perform its own movement
	//projectileToSpawn_Grenade
	FFLogger::LogMessage(LogMessageSeverity::Debug, "Launching grenade");

	//step 2: set a timer to delay the next grenade launch

	GetWorld()->GetTimerManager().SetTimer(m_grenadeDelayTimer, this, &UShootingComponent::EnableGrenade, m_delayBetweenThrows_Grenade);

}

void UShootingComponent::EnableGun()
{
	m_canShoot_Gun = true;
}

void UShootingComponent::EnableGrenade()
{
	m_canLaunch_Grenade = true;
}

void UShootingComponent::ReloadFull_GunAmmo()
{
	GetWorld()->GetTimerManager().SetTimer(
		m_gunReloadTimer,
		FTimerDelegate::CreateLambda([this]()
		{
			FFLogger::LogMessage(LogMessageSeverity::Debug, "Reloading gun");
			m_currentAmmo_Gun = maxAmmo_Gun;
		}),
		reloadTime_Gun,
		false
	);
}

void UShootingComponent::ReloadFixedAmount_GunAmmo(int amountToReload)
{
	GetWorld()->GetTimerManager().SetTimer(
		m_gunReloadTimer,
		FTimerDelegate::CreateLambda([this, amountToReload]()
			{
				FFLogger::LogMessage(LogMessageSeverity::Debug, "Reloading gun by " + FString::FromInt(amountToReload));
				m_currentAmmo_Gun += amountToReload;
				m_currentAmmo_Gun = FMath::Clamp(m_currentAmmo_Gun, 0, maxAmmo_Grenade);
			}),
		reloadTime_Gun,
		false
	);
}

void UShootingComponent::ReloadFull_GrenadeAmmo()
{
	GetWorld()->GetTimerManager().SetTimer(
		m_grenadeReloadTimer,
		FTimerDelegate::CreateLambda([this]()
		{
			m_currentAmmo_Grenade = maxAmmo_Grenade;
		}),
		reloadTime_Grenade,
		false
	);
}

void UShootingComponent::ReloadFullAmmo_AllWeapons()
{
	GetWorld()->GetTimerManager().SetTimer(
		m_gunReloadTimer,
		FTimerDelegate::CreateLambda([this]()
			{
				m_currentAmmo_Grenade = maxAmmo_Grenade;
				m_currentAmmo_Gun = maxAmmo_Gun;
			}),
		reloadTime_Gun,
		false
	);
}

void UShootingComponent::ReloadFixedAmount_GrenadeAmmo(int amountToReload)
{
	GetWorld()->GetTimerManager().SetTimer(
		m_grenadeReloadTimer,
		FTimerDelegate::CreateLambda([this, amountToReload]()
			{
				m_currentAmmo_Grenade += amountToReload;
				m_currentAmmo_Grenade = FMath::Clamp(m_currentAmmo_Grenade, 0, maxAmmo_Grenade);
			}),
		reloadTime_Grenade,
		false
	);
}

