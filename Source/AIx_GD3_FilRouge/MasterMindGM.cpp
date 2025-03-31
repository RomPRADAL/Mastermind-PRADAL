// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterMindGM.h"

// Sets default values
AMasterMindGM::AMasterMindGM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMasterMindGM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterMindGM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FLinearColor AMasterMindGM::GetColor(uint8 ColorNumber)
{
	if(ColorNumber < Colors.Num())
	{
		return Colors[ColorNumber];
	}

	return FLinearColor::Black;
	
}


void AMasterMindGM::CreateSolution()
{
	Solution.SetNum(4);
	for(uint8 i = 0; i < 4; i++)
	{
		Solution[i] = FMath::RandRange(0,5);
	}
}

bool AMasterMindGM::CheckAnswer(TArray<uint8> Answer)
{
	// On a Solution et Answer, faut les comparer

	TArray<int> TempRightPlace[4];
	bool result = true;
	//Nbr reponses bien placés
	uint8 GoodPlaces = 0;
	uint8 BadPlaces = 0;
	//On retient quels entrée sont utilisables encore
	TArray<bool> SolutionsAllowed {true, true, true, true};
	TArray<bool> AnswersAllowed {true, true, true, true};
	
		for(uint8 i = 0; i < 4; i++)
		{
			if(Solution[i] == Answer[i])
			{
				GoodPlaces++;
				SolutionsAllowed[i] = false;
				AnswersAllowed[i] = false;
			}
			else
			{
				result = false;
			}
		}

	for(uint8 i = 0; i < 4; i++)
	{
		if(AnswersAllowed[i])
		{
			for(uint8 j = 0; j < 4; j++)
			{
				if(SolutionsAllowed[j] && Answer[i] == Solution[j])
				{
					BadPlaces++;
					SolutionsAllowed[j] = false;
					break;
				}
			}
		}
	}
	//ShowResultToPlayer(GoodPlaces, BadPlaces);
	return result;
	}

// Au final je m'en sers pas
TArray<int> AMasterMindGM::CheckWhoIsInRightPlace(TArray<uint8> ParamAnswer, TArray<uint8> ParamSolution)
{
	TArray<int> RetRightPlace;
	for(int i = 0; i < 4; i++)
	{
		if(ParamAnswer[i] == Solution[i])
		{
			RetRightPlace[i] = 1;
		}
		else
		{
			RetRightPlace[i] = 0;
		}
	}
	
	return RetRightPlace;
}

void AMasterMindGM::ShowResultToPlayer(uint8 ParamGoodPlaces, uint8 ParamBadPlaces)
{
	GEngine->AddOnScreenDebugMessage(-5, 5.f, FColor::Yellow, FString::Printf(TEXT("Good place : %d"), ParamGoodPlaces));
	GEngine->AddOnScreenDebugMessage(-6, 5.f, FColor::Yellow, FString::Printf(TEXT("Bad place : %d"), ParamBadPlaces));
}


