// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
AOBRCharacter::AOBRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CreateComponents
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	// Attachment
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	// SetProperties
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	SpringArm->TargetArmLength = 350.0f;
	Camera->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 66.0f);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -60.0f), FRotator(0.0f, -90.0f, 0.0f));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_OBOT(TEXT("/Game/StackOBot/Characters/Bot/Mesh/SKM_Bot.SKM_Bot"));
	if (SK_OBOT.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_OBOT.Object);
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IM_OBOT(TEXT("/Game/Input/IM_OBot.IM_OBot"));
	if (IM_OBOT.Succeeded())
	{
		Context = IM_OBOT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MOVERIGHTOBOT(TEXT("/Game/Input/IA_MoveRightOBot.IA_MoveRightOBot"));
	if (IA_MOVERIGHTOBOT.Succeeded())
	{
		MoverightOBotAction = IA_MOVERIGHTOBOT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JUMPOBOT(TEXT("/Game/Input/IA_JumpOBot.IA_JumpOBot"));
	if (IA_JUMPOBOT.Succeeded())
	{
		JumpOBotAction = IA_JUMPOBOT.Object;
	}
}

// Called when the game starts or when spawned
void AOBRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOBRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOBRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(MoverightOBotAction, ETriggerEvent::Triggered, this, &AOBRCharacter::MoveRightOBot);
		EnhancedInputComponent->BindAction(JumpOBotAction, ETriggerEvent::Triggered, this, &AOBRCharacter::JumpOBot);
	}
}

void AOBRCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	APlayerController* PlayerController = Cast<APlayerController>(NewController);

	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (SubSystem != nullptr)
		{
			SubSystem->AddMappingContext(Context, 0);
			UE_LOG(LogTemp, Warning, TEXT("On"));
		}
	}
}

void AOBRCharacter::MoveRightOBot(const FInputActionValue& Value)
{
	AddMovementInput(GetActorRightVector() * 2.0f, Value.Get<float>());
}

void AOBRCharacter::JumpOBot()
{

}
