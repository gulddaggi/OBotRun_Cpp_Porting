// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRCharacter.h"
#include "OBRAnimInstance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "OBRMainGameMode.h"

// Sets default values
AOBRCharacter::AOBRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	// Attachment
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	Effect->SetupAttachment(GetRootComponent());

	// Set Properties
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	SpringArm->TargetArmLength = 350.0f;
	Camera->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 66.0f);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -60.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// Init Values
	EnableJump = true;
	EnableTurn = false;
	JumpDelay = 2.5f;
	GetCharacterMovement()->JumpZVelocity = 900.0f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->GroundFriction = 15.0f;
	Effect->bAutoActivate = false;

	RunningScore = 10;
	IsDead = false;
	MainGameMode = nullptr;
}

// Called when the game starts or when spawned
void AOBRCharacter::BeginPlay()
{
	Super::BeginPlay();

	MoveForward();
	GetWorld()->GetTimerManager().SetTimer(MoveForwardTimerHandle, this, &AOBRCharacter::MoveForward, 0.01f, true);
	GetWorld()->GetTimerManager().SetTimer(AddScoreHandle, this, &AOBRCharacter::AddScore, 0.1f, true);

	MainGameMode = Cast<AOBRMainGameMode>(GetWorld()->GetAuthGameMode());
	
}

// Called every frame
void AOBRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsDead) GetCharacterMovement()->MaxWalkSpeed += (5.0f * GetWorld()->DeltaTimeSeconds);
	if (GetActorLocation().Z <= -100.0f) Dead();
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
		if (SubSystem != nullptr) SubSystem->AddMappingContext(Context, 0);
	}
}

void AOBRCharacter::MoveRightOBot(const FInputActionValue& Value)
{
	if (EnableTurn)
	{
		Turn(Value.Get<float>());
	}
	else
	{
		AddMovementInput(GetActorRightVector() * 2.0f, Value.Get<float>());
	}
}

void AOBRCharacter::JumpOBot()
{
	if (EnableJump)
	{
		Jump();
		EnableJump = false;
		GetWorld()->GetTimerManager().SetTimer(JumpTimerHandle, this, &AOBRCharacter::SetEnableJump, JumpDelay, false);
	}
}

void AOBRCharacter::MoveForward()
{
	AddMovementInput(GetActorForwardVector() * 2);
}

void AOBRCharacter::SetEnableJump()
{
	EnableJump = true;
}

void AOBRCharacter::SetEnableTurn()
{
	EnableTurn = true;
}

void AOBRCharacter::Turn(float AxisValue)
{
	EnableTurn = false;
	FRotator TargetRotator = GetControlRotation() + FRotator(0.0f, (90.0f * AxisValue), 0.0f);
	GetController()->SetControlRotation(TargetRotator);
	
}

void AOBRCharacter::AddScore()
{
	if (!IsDead) MainGameMode->AddScore(RunningScore);
}

void AOBRCharacter::Dead()
{
	if (!IsDead)
	{
		IsDead = true;
		Effect->Activate();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
		GetMesh()->SetVisibility(false);
		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		GetWorld()->GetTimerManager().SetTimer(GameOverTimerHandle, MainGameMode, &AOBRMainGameMode::GameOver, 2.0f, false);
	}
}