// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	HandSocketName = "Muzzle_01";
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChange.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot(GetControlRotation());
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{

	FRotator ControlRot(GetControlRotation());
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	//X = Forward (Red)
	//Y = Right (Green)
	//Z = Up (Blue)

	FVector RightVector(FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y));
	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttackMagicProjectile);
	PlayerInputComponent->BindAction("PrimaryAttackBlackHole", IE_Pressed, this, &ASCharacter::PrimaryAttackBlackHole);
	PlayerInputComponent->BindAction("PrimaryAttackTeleport", IE_Pressed, this, &ASCharacter::PrimaryAttackTeleport);
}

void ASCharacter::PrimaryAttackMagicProjectile()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttackMagicP_TimeEnlapsed, 0.2);

	// This is declared when the character die
	// GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void ASCharacter::PrimaryAttackBlackHole()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttackBlackHole_TimeEnlapsed, 0.2);

	// This is declared when the character die
	// GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void ASCharacter::PrimaryAttackTeleport()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttackTeleport_TimeEnlapsed, 0.2);

	// This is declared when the character die
	// GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void ASCharacter::PrimaryAttack_TimeEnlapsed(TSubclassOf<AActor> ProjectileClass)
{
	if (ensure(ProjectileClass)) // ensureAlways() that triggers everytime. In package game this is removed.
	{
		// get socket (marked added in the bones of the skeleton mesh)
		FVector HandLocation = GetMesh()->GetSocketLocation(HandSocketName);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParams.Instigator = this;

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

		FVector EyeLocation;
		FRotator EyeRotation;

		// get info from camera view 
		FMinimalViewInfo ViewInfo;
		CameraComp->GetCameraView(0.0f, ViewInfo);
		EyeLocation = ViewInfo.Location;
		EyeRotation = ViewInfo.Rotation;
		//

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		// Ray trace from that view
		FVector End(EyeLocation + (EyeRotation.Vector() * 5000.0f));
		//FVector End = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);

		FHitResult Hit;

		if (GetWorld()->SweepSingleByObjectType(Hit, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape, Params))
		{
			End = Hit.ImpactPoint;
		}

		FRotator ProjRotation = FRotationMatrix::MakeFromX(End - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);

		//if (bBlocking)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Block Other Actor %s, line trace from camera, at game time %f"), *GetNameSafe(Hit.GetActor()), GetWorld()->TimeSeconds);
		//
		//	// Spawn from here for precision
		//	FRotator NewRotation = (Hit.Location - HandLocation).Rotation();
		//	SpawnTM = FTransform(NewRotation, HandLocation);
		//
		//}
		
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwingComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}

	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PlayerCtr = Cast<APlayerController>(GetController());

		DisableInput(PlayerCtr);
	}
}

void ASCharacter::PrimaryAttackMagicP_TimeEnlapsed()
{
	PrimaryAttack_TimeEnlapsed(ProjectileMagicClass);
}

void ASCharacter::PrimaryAttackBlackHole_TimeEnlapsed()
{
	PrimaryAttack_TimeEnlapsed(ProjectileBlackHoleClass);
}

void ASCharacter::PrimaryAttackTeleport_TimeEnlapsed()
{
	PrimaryAttack_TimeEnlapsed(ProjectileTeleport);
}

void ASCharacter::HealSelf(float Amount /* - 100 */)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}

