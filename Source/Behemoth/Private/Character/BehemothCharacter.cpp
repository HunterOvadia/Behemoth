#include "Character/BehemothCharacter.h"

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BHAttributesComponent.h"
#include "Components/BHInventoryComponent.h"
#include "Components/BHInteractionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Behemoth/Behemoth.h"



ABehemothCharacter::ABehemothCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	HealthRegenAmount = 10.0f;
	HealthRegenRate = 3.0f;


	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;

	/* ===== CUSTOM COMPONENTS ===== */
	AttributesComponent = CreateDefaultSubobject<UBHAttributesComponent>(TEXT("AttributesComponent"));
	InventoryComponent = CreateDefaultSubobject<UBHInventoryComponent>(TEXT("InventoryComponent"));
	InteractionComponent = CreateDefaultSubobject<UBHInteractionComponent>(TEXT("InteractionComponent"));

	/* ===== EQUIPMENT ===== */
	HeadSocketName = "HeadSocket"; 
	ChestSocketName = "ChestSocket"; 
	PrimaryWeaponSocketName = "PrimaryWeaponSocket"; 
	SecondaryWeaponSocketName = "SecondaryWeaponSocket";
	
	HelmetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HelmetMesh"));
	HelmetMesh->SetupAttachment(GetMesh(), HeadSocketName);
	
	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestMesh"));
    ChestMesh->SetupAttachment(GetMesh(), ChestSocketName);
	
	PrimaryWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PrimaryWeaponMesh"));
	PrimaryWeaponMesh->SetupAttachment(GetMesh(), PrimaryWeaponSocketName);
	
	SecondaryWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondaryWeaponMesh"));
	SecondaryWeaponMesh->SetupAttachment(GetMesh(), SecondaryWeaponSocketName);

	ArmorMeshComponentsMap =
	{
		{ Head, HelmetMesh },
		{ Chest, ChestMesh },
		{ PrimaryWeapon, PrimaryWeaponMesh }
	};
}

void ABehemothCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Inventory", IE_Released, this, &ABehemothCharacter::ToggleInventory);
	PlayerInputComponent->BindAction("CharacterInfo", IE_Released, this, &ABehemothCharacter::ToggleCharacterInfo);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ABehemothCharacter::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABehemothCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABehemothCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABehemothCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABehemothCharacter::LookUpAtRate);
}

void ABehemothCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(IsValid(PlayerHUDClass))
	{
		PlayerHUD = CreateWidget<UUserWidget>(GetGameInstance(), PlayerHUDClass);
		if(IsValid(PlayerHUD))
		{
			PlayerHUD->AddToViewport();
		}
	}

	UWorld *World = GetWorld();
	if(World != nullptr)
	{
		World->GetTimerManager().SetTimer(HealthRegenTimerHandle, this, &ABehemothCharacter::RegenerateHealthOverTime, HealthRegenRate, true);
		if(IsValid(InventoryComponent))
		{
			InventoryComponent->OnItemEquipped.AddDynamic(this, &ABehemothCharacter::OnItemEquipped);
			InventoryComponent->OnItemUnEquipped.AddDynamic(this, &ABehemothCharacter::OnItemUnEquipped);
		}
	}
}


float ABehemothCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if(IsValid(AttributesComponent))
	{
		AttributesComponent->ModifyAttributeCurrent(Health, -DamageTaken);
	}

	return DamageTaken;
}

void ABehemothCharacter::TurnAtRate(const float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABehemothCharacter::LookUpAtRate(const float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABehemothCharacter::OnItemEquipped(const FBHItemData& ItemData)
{
	UpdateArmorMesh(ItemData, true);
	RecalculateAttributesForItem(ItemData, true);
}

void ABehemothCharacter::OnItemUnEquipped(const FBHItemData& ItemData)
{
	UpdateArmorMesh(ItemData, false);
	RecalculateAttributesForItem(ItemData, false);
}

void ABehemothCharacter::RecalculateAttributesForItem(const FBHItemData& ItemData, const bool bIsEquipped) const
{
	if(IsValid(AttributesComponent))
	{
		for(const auto& Attribute : ItemData.Attributes)
        {
	        const float ModificationAmount = (bIsEquipped ? Attribute.Value : -Attribute.Value);
        	AttributesComponent->ModifyAttributeMax(Attribute.Key, ModificationAmount);
        }
	}
}


void ABehemothCharacter::UpdateArmorMesh(const FBHItemData& ItemData, const bool bIsEquipped) const
{
	UStaticMeshComponent *ComponentToUpdate = nullptr;
	if(ArmorMeshComponentsMap.Find(ItemData.Type))
	{
		ComponentToUpdate = ArmorMeshComponentsMap[ItemData.Type];
	}

	if(IsValid(ComponentToUpdate))
	{
		ComponentToUpdate->SetStaticMesh(bIsEquipped ? ItemData.ItemMesh : nullptr);
	}
}

void ABehemothCharacter::RegenerateHealthOverTime() const
{
	if(IsValid(AttributesComponent))
	{
		if(AttributesComponent->GetAttributeCurrent(Health) < AttributesComponent->GetAttributeMax(Health))
		{
			AttributesComponent->ModifyAttributeCurrent(Health, HealthRegenAmount);
		}
	}
}

void ABehemothCharacter::Interact()
{
	if(IsValid(InteractionComponent))
	{
		const TScriptInterface<IBHInteractableInterface> CurrentInteractable = InteractionComponent->GetCurrentInteractable();
		if(CurrentInteractable != nullptr)
		{
			if(IBHInteractableInterface::Execute_CanInteract(CurrentInteractable.GetObject()))
			{
				IBHInteractableInterface::Execute_OnInteract(CurrentInteractable.GetObject(), this);
			}
		}
	}
}

void ABehemothCharacter::MoveForward(const float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		AddMovementInput(Direction, Value);
	}
}

void ABehemothCharacter::MoveRight(const float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(Direction, Value);
	}
}
