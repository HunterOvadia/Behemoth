#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehemothCharacter.generated.h"

UCLASS(config=Game)
class ABehemothCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ABehemothCharacter();

	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	void MoveForward(const float Value);
	void MoveRight(const float Value);
	void TurnAtRate(const float Rate);
	void LookUpAtRate(const float Rate);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseLookUpRate;
};

