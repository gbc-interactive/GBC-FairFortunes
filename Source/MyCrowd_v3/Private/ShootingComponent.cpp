#include "ShootingComponent.h"
#include "FFLogger.h"

UShootingComponent::UShootingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UShootingComponent::BeginPlay()
{
	Super::BeginPlay();

	m_delayBetweenShots_Gun = 1.0f / fireRate_Gun;
	m_delayBetweenThrows_Grenade = 1.0f / fireRate_Grenade;

	m_currentAmmo_Gun = maxAmmo_Gun;
	m_currentAmmo_Grenade = maxAmmo_Grenade;

	m_canLaunch_Grenade = true;
	m_canShoot_Gun = true;
}


void UShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UShootingComponent::ShootGun()
{
	if(m_canShoot_Gun == false)
	{
		FFLogger::LogMessage(LogMessageSeverity::Debug, "Cannot shoot gun yet");
		return;
	}

	if(m_currentAmmo_Gun <= 0)
	{
		FFLogger::LogMessage(LogMessageSeverity::Debug, "Out of bullets");
		return;
	}

	m_currentAmmo_Gun--;

	//step1: instantiate the projectile provided as the bullet, the projectile is assumed to perform its own movement
	//projectileToSpawn_Grenade
	FFLogger::LogMessage(LogMessageSeverity::Debug, "Shooting gun");


	//step 2: set a timer to delay the next shot
	GetWorld()->GetTimerManager().SetTimer(
		m_gunShotDelayTimer,
		FTimerDelegate::CreateLambda([this]()
			{
				EnableGun();
			}),
		m_delayBetweenShots_Gun,
		false);
}

void UShootingComponent::LaunchGrenade()
{
	if (m_canLaunch_Grenade == false)
	{
		FFLogger::LogMessage(LogMessageSeverity::Debug, "Cannot launch grenade yet");
		return;
	}

	if (m_currentAmmo_Grenade <= 0)
	{
		FFLogger::LogMessage(LogMessageSeverity::Debug, "Out of grenades");
		return;
	}

	m_currentAmmo_Grenade--;

	//step1: instantiate the projectile provided as the grenade, the projectile is assumed to perform its own movement
	//projectileToSpawn_Grenade
	FFLogger::LogMessage(LogMessageSeverity::Debug, "Launching grenade");

	//step 2: set a timer to delay the next grenade launch
	GetWorld()->GetTimerManager().SetTimer(
		m_grenadeDelayTimer, 
		FTimerDelegate::CreateLambda([this]()
		{
			EnableGrenade();
		}),
		m_delayBetweenThrows_Grenade,
		false);
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
}

void UShootingComponent::ReloadFixedAmount_GunAmmo(int amountToReload)
{
}

void UShootingComponent::ReloadFull_GrenadeAmmo()
{
}

void UShootingComponent::ReloadFixedAmount_GrenadeAmmo(int amountToReload)
{
}

