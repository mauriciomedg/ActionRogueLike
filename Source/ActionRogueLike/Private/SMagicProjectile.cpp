// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

//#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"
//#include "Particles/ParticleSystemComponent.h"
//#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//
	//// That is replaced by the profile preset "Projectile" created in the editor
	////SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	////SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	////SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	///////
	//
	//SphereComp->SetCollisionProfileName("Projectile");
	//RootComponent = SphereComp;
	//
	//EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	//EffectComp->SetupAttachment(SphereComp);
	//
	//MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

}

void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	

	//SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnCompHit);
}

//void ASMagicProjectile::OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	URadialForceComponent* ActionComp = Cast<URadialForceComponent>(OtherActor->GetComponentByClass(URadialForceComponent::StaticClass()));
//
//	if (ActionComp != nullptr)
//	{
//		ActionComp->FireImpulse();
//	}
//	//RadialForceComp->FireImpulse();
//}
void ASMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	
	if (OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));

		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-DamageAmount);

			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

