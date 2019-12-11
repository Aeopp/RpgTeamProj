// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RPGCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/DamageType.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "RInGameHUD.h"
#include "RInGamePlayerController.h"
#include "Weapon.h"
#include "AnimInstanceBase.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

ARPGCharacter::ARPGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Weapon = CreateDefaultSubobject<AWeapon>(TEXT("Weapon"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage>AttackAnimMontage(
		TEXT("/Game/PlayerAnim/Standing_Melee_Attack_Horizontal_Anim_mixamo_com_Montage.Standing_Melee_Attack_Horizontal_Anim_mixamo_com_Montage"));
	if (AttackAnimMontage.Succeeded())
	{
		AttackMontage = AttackAnimMontage.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>StopAttackAnimMontage(
		TEXT("/Game/PlayerAnim/Standing_Disarm_Over_Shoulder_Anim_mixamo_com1_Montage.Standing_Disarm_Over_Shoulder_Anim_mixamo_com1_Montage"));
	if (StopAttackAnimMontage.Succeeded())
	{
		StopAttackMontage = StopAttackAnimMontage.Object;
	}

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARPGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ARPGCharacter::Attack_AnimPlay);
	PlayerInputComponent->BindAction("Running", IE_Pressed, this, &ARPGCharacter::Running);
	PlayerInputComponent->BindAction("Running", IE_Released, this, &ARPGCharacter::StopRunning);
	PlayerInputComponent->BindAction("ToggleMenuInGame", IE_Pressed, this, &ARPGCharacter::ToggleMenuInGame);
	PlayerInputComponent->BindAction("ToggleCharacterStateMenu", IE_Pressed, this, &ARPGCharacter::ToggleCharacterStateMenu);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARPGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPGCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ARPGCharacter::OnResetVR);
	//PlayerInputComponent->BindAxis("TurnRate", this, &ARPGCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &ARPGCharacter::LookUpAtRate);
	//PlayerInputComponent->BindTouch(IE_Pressed, this, &ARPGCharacter::TouchStarted);
	//PlayerInputComponent->BindTouch(IE_Released, this, &ARPGCharacter::TouchStopped);
}

void ARPGCharacter::Attack_AnimPlay()
{
	// 인벤 빈슬롯을 장착 시도할시 Weapon 검사안하면 터져서 코드 추가함
	
	if (!IsValid(Weapon))return;

	if (UGameplayStatics::GetPlayerController(this, 0)->IsInputKeyDown(EKeys::LeftShift))
	{
		GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}

	FDetachmentTransformRules DetachRules = { EDetachmentRule::KeepRelative,EDetachmentRule::KeepRelative,EDetachmentRule::KeepRelative,true };
	FAttachmentTransformRules AttachRules = { EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,true };
	Weapon->DetachFromActor(DetachRules);
	Weapon->AttachToComponent(UGameplayStatics::GetPlayerCharacter(this, 0)->GetMesh(), AttachRules, TEXT("Weapon"));
	Weapon->SetActorLocation(UGameplayStatics::GetPlayerCharacter(this, 0)->GetMesh()->GetSocketLocation(TEXT("Weapon")));
	Weapon->SetActorLocation(Weapon->GetMesh()->GetSocketLocation(TEXT("hand")));

	if (IsValid(Anim) && IsValid(AttackMontage))
	{
		Anim->PlayMontage(AttackMontage, 2.0f);
	}

	Attacking = true;
	StopAttack = false;
	temp = 0.0f;
}

void ARPGCharacter::Attack(AActor* Actor)
{
	if (!IsValid(Weapon))return;

	FHitResult HitActor;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType = { EObjectTypeQuery::ObjectTypeQuery3 };
	TArray<AActor*> Ignore = { this };
	FVector Start = GetActorLocation();
	FVector End = ((UKismetMathLibrary::GetForwardVector(GetActorRotation()) * 200.f) + Start);

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(this, Start, End, 20.0f, ObjectType, false, Ignore, EDrawDebugTrace::Persistent, HitActor, true))
	{
		if (HitActor.Actor.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("%f"), GetDamage());
			UGameplayStatics::ApplyDamage(HitActor.GetActor(), GetDamage(), this->GetController(), Weapon, nullptr);
		}
	}

	UE_LOG(LogTemp, Error, TEXT("%f"), GetDamage());
	UGameplayStatics::ApplyDamage(Actor, GetDamage(), this->GetController(), Weapon, nullptr);
}

float ARPGCharacter::GetDamage()
{
	float Buff = 0;
	float Debuff = 0;

	return ((Stat.Attack + Weapon->AttackPower) * 0.1f * Stat.Str * (1.0f + Buff) + (Stat.Attack + Weapon->AttackPower)) / (1.0f + Debuff);
}

void ARPGCharacter::SetWeapon(AWeapon* NewWeapon)
{
	Weapon = NewWeapon;
}

void ARPGCharacter::Running()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}

void ARPGCharacter::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
}

void ARPGCharacter::Stop()
{
	StopAttack = true;
	Anim->PlayMontage(StopAttackMontage);
}

void ARPGCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		if (Anim->Montage_IsPlaying(AttackMontage))
		{
			bUseControllerRotationYaw = true;
			FollowCamera->bUsePawnControlRotation = true;
		}
		else
		{
			bUseControllerRotationYaw = false;
			FollowCamera->bUsePawnControlRotation = false;
			AddMovementInput(Direction, Value);
		}
	}
}

void ARPGCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		if (Anim->Montage_IsPlaying(AttackMontage))
		{
			bUseControllerRotationYaw = true;
			FollowCamera->bUsePawnControlRotation = true;
		}
		else
		{
			bUseControllerRotationYaw = false;
			FollowCamera->bUsePawnControlRotation = false;
			AddMovementInput(Direction, Value);
		}
	}
}

//void ARPGCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
//{
//		Jump();
//}
//
//void ARPGCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
//{
//		StopJumping();
//}
//void ARPGCharacter::TurnAtRate(float Rate)
//{
//	// calculate delta for this frame from the rate information
//	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
//}
//
//void ARPGCharacter::LookUpAtRate(float Rate)
//{
//	// calculate delta for this frame from the rate information
//	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
//}
//void ARPGCharacter::OnResetVR()
//{
//	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
//}

void ARPGCharacter::ToggleMenuInGame() {
	ARInGamePlayerController* CurrentPC = Cast<ARInGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CurrentPC) {
		ARInGameHUD* CurrentHUD = Cast<ARInGameHUD>(CurrentPC->GetHUD());
		if (CurrentHUD) {
			if (bMenuInGame) {
				CurrentHUD->RemoveWidget(MenuInGame);
			}
			else {
				if (!MenuInGame) {
					MenuInGame = CurrentHUD->AddWidget(CurrentHUD->MainMenuWidgetClass);
				}
				else {
					CurrentHUD->AttachWidget(MenuInGame);
				}
			}
			bMenuInGame = !bMenuInGame;
		}
	}
}

void ARPGCharacter::ToggleCharacterStateMenu() {
	ARInGamePlayerController* CurrentPC = Cast<ARInGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CurrentPC) {
		ARInGameHUD* CurrentHUD = Cast<ARInGameHUD>(CurrentPC->GetHUD());
		if (CurrentHUD) {
			if (bCharacterStateMenu) {
				CurrentHUD->RemoveWidget(CharacterStateMenu);
			}
			else {
				if (!CharacterStateMenu) {
					CharacterStateMenu = CurrentHUD->AddWidget(CurrentHUD->CharacterStateWidgetClass);
				}
				else {
					CurrentHUD->AttachWidget(CharacterStateMenu);
				}
			}
			bCharacterStateMenu = !bCharacterStateMenu;
		}
	}
}

void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &ARPGCharacter::RecieveAnyDamage);
	Anim = Cast<UAnimInstanceBase>(GetMesh()->GetAnimInstance());
	//Anim->OnAttackCheck.AddDynamic(this, &ARPGCharacter::Attack);
	UGameplayStatics::GetPlayerController(this, 0)->bEnableClickEvents = true;
}

void ARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Attacking == true)
	{
		temp += DeltaTime;
		if (temp >= 10.0f)
		{
			Attacking = false;
			Stop();
			if (UGameplayStatics::GetPlayerController(this, 0)->IsInputKeyDown(EKeys::LeftShift))
			{
				GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
			}
			else
			{
				GetCharacterMovement()->MaxWalkSpeed = 800.0f;
			}
			temp = 0.0f;
		}
	}
	if (StopAttack)
	{
		temp += DeltaTime;
		if (temp >= 0.2f)
		{
			StopAttack = false;
			temp = 0.0f;
		}
	}
}

void ARPGCharacter::Death()
{
	UGameplayStatics::SetPlayerControllerID(UGameplayStatics::GetPlayerController(this, 0), 1);
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARPGCharacter::RecieveAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Stat.Hp -= Damage;

	UE_LOG(LogTemp, Error, TEXT("Damage : %f"), Damage);

	if (Stat.Hp <= 0)
	{
		Death();
	}
}
