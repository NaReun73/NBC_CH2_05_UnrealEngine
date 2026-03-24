
#include "MyActor.h"
#include "Engine/Engine.h"

AMyActor::AMyActor()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Start"));
	SetActorLocation(FVector(0, 50, 0));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Red, TEXT("Cube"));
		GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Blue, FString::Printf(TEXT("Cube Location : %s"), *GetActorLocation().ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Blue, FString::Printf(TEXT("Cube Rotation : %s"), *GetActorRotation().ToString()));
	}

	fail = 0;
	movecount = 0;
	turncount = 0;

	for (int i = 0; i < 10; i++)
	{
		RandomAction();
	}
}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyActor::Move(const FVector& direction)
{
	bool Event = TriggerEvent();

	if (Event)
	{
		movecount++;
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = CurrentLocation + direction;
		SetActorLocation(NewLocation);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Green, FString::Printf(TEXT("Move : %s"), *direction.ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Green, FString::Printf(TEXT("MoveCount : %d , Cube Location : %s"), movecount, *GetActorLocation().ToString()));
		}
	}
	else
	{
		fail++;
	}
}

void AMyActor::Turn(const FRotator& rotation)
{
	bool event = TriggerEvent();
	if (event)
	{
		turncount++;
		FRotator CurrentRotation = GetActorRotation();
		FRotator NewRotation = CurrentRotation + rotation;
		SetActorRotation(NewRotation);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Orange, FString::Printf(TEXT("Turn : %s"), *rotation.ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Orange, FString::Printf(TEXT("TurnCount : %d , Cube Rotation : %s"), turncount, *GetActorRotation().ToString()));
		}
	}
	else
	{
		fail++;
	}
}

void AMyActor::RandomAction()
{
	int32 RandomValue = FMath::RandRange(1, 100); // 1 ~ 100의 난수 생성
	
	if (RandomValue < 50)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Yellow, TEXT("Move"));
		}
		FVector RandomVector(FMath::RandRange(-50, 50), FMath::RandRange(-50, 50), FMath::RandRange(-50, 50));
		Move(RandomVector);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Yellow, TEXT("Turn"));
		}
		FRotator RandomRotator(FMath::RandRange(-10, 10), FMath::RandRange(-10, 10), FMath::RandRange(-10, 10));
		Turn(RandomRotator);
	}
}

bool AMyActor::TriggerEvent()
{
	bool Event;
	int EventNum = FMath::RandRange(0, 1);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Magenta, TEXT("Event!!!"));

	if (EventNum == 0)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Blue, TEXT("Good"));
		Event = true;
	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Red, TEXT("Bad"));
		Event = false;
	}

	return Event;
}

/*
TArray<FVector> AMyActor::PrintFVectorArray()
{
	TArray<FVector> VectorArray;

	for (int i = 0; i < 10; i++)
	{
		FVector RandomVector(FMath::RandRange(-50.0f, 50.0f), FMath::RandRange(-50.0f, 50.0f), FMath::RandRange(-50.0f, 50.0f));
		//RandomVector.X = FMath::RandRange(-50.0f, 50.0f);
		//RandomVector.Y = FMath::RandRange(-50.0f, 50.0f);
		//RandomVector.Z = FMath::RandRange(-50.0f, 50.0f);
		VectorArray.Add(RandomVector);
	}

	for (int32 i = 0; i < VectorArray.Num(); i++)
	{
		const FVector& Vec = VectorArray[i];
		UE_LOG(LogTemp, Warning, TEXT("Vector %d: X = %f, Y = %f, Z = %f"), i, Vec.X, Vec.Y, Vec.Z);
	}

	return VectorArray;
}

TArray<FRotator> AMyActor::PrintFRotatorArray()
{
	TArray<FRotator> RotatorArray;

	for (int i = 0; i < 10; i++)
	{
		FRotator RandomRotator(FMath::FRand() * 360.f, FMath::FRand() * 360.f, FMath::FRand() * 360.f);
		//RandomRotator.Pitch = FMath::RandRange(-50.0f, 50.0f);
		//RandomRotator.Yaw = FMath::RandRange(-50.0f, 50.0f);
		//RandomRotator.Roll = FMath::RandRange(-50.0f, 50.0f);
		RotatorArray.Add(RandomRotator);
	}

	for (int32 i = 0; i < RotatorArray.Num(); i++)
	{
		const FRotator& Rotator = RotatorArray[i];
		UE_LOG(LogTemp, Warning, TEXT("Rotator %d: Pitch = %f, Yaw = %f, Roll = %f"), i, Rotator.Pitch, Rotator.Yaw, Rotator.Roll);
	}

	return RotatorArray;
}*/