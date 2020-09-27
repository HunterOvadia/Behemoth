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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	void MoveForward(const float Value);
	void MoveRight(const float Value);
	void TurnAtRate(const float Rate);
	void LookUpAtRate(const float Rate);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	class UCameraComponent* FollowCamera;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseLookUpRate;
};

