#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Items/BHItemData.h"
#include "BehemothCharacter.generated.h"

struct FBHItemData;

UCLASS(config=Game)
class ABehemothCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ABehemothCharacter();

	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	class UBHInventoryComponent *GetInventoryComponent() const { return InventoryComponent; }
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	void MoveForward(const float Value);
	void MoveRight(const float Value);
	void TurnAtRate(const float Rate);
	void LookUpAtRate(const float Rate);

	UFUNCTION(BlueprintImplementableEvent)
	void ToggleInventory();
	UFUNCTION(BlueprintImplementableEvent)
    void ToggleCharacterInfo();

	UFUNCTION()
    void OnItemEquipped(const FBHItemData& ItemData);
	UFUNCTION()
	void OnItemUnEquipped(const FBHItemData& ItemData);

	UFUNCTION(BlueprintCallable)
	void RecalculateAttributesForItem(const FBHItemData& ItemData, const bool bIsEquipped) const;
	
	UFUNCTION(BlueprintCallable)
	void UpdateArmorMesh(const FBHItemData& ItemData, const bool bIsEquipped) const;

	UFUNCTION()
	void RegenerateHealthOverTime() const;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerInteract();
	UFUNCTION()
	void Interact();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> PlayerHUDClass;
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	class UUserWidget *PlayerHUD;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	class UCameraComponent* FollowCamera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	class UBHAttributesComponent *AttributesComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UBHInventoryComponent *InventoryComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	class UBHInteractionComponent *InteractionComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	class UStaticMeshComponent *HelmetMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	class UStaticMeshComponent *ChestMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	class UStaticMeshComponent *PrimaryWeaponMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	class UStaticMeshComponent *SecondaryWeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FName HeadSocketName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FName ChestSocketName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FName PrimaryWeaponSocketName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FName SecondaryWeaponSocketName;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TMap<TEnumAsByte<EBHItemType>, UStaticMeshComponent *> ArmorMeshComponentsMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health")
	float HealthRegenAmount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health")
	float HealthRegenRate;

	FTimerHandle HealthRegenTimerHandle;
};

