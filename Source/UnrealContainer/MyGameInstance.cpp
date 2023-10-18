// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h"

FString MakeRandomName() 
{
	TCHAR FirstChar[] = TEXT("김이최박");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은원연");

	TArray<TCHAR> RandomArray;
	RandomArray.SetNum(3);

	RandomArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandomArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandomArray[2] = LastChar[FMath::RandRange(0, 3)];

	return RandomArray.GetData();

}

void UMyGameInstance::Init()
{
	Super::Init();

	const int32 ArrayNum = 10;

	TArray<int32> Int32Array;

	for (int i = 1; i <= ArrayNum; ++i)
	{
		Int32Array.Add(i);

		// or
		// Int32Array.Emplace(i);

	}

	// remove even number

	Int32Array.RemoveAll(
		// using lamda

		[](int32 Val)
		{
			return Val % 2 == 0;
		}
	);

	Int32Array += { 2, 4, 6, 8, 10 };
	// Original C++ style (using memcpy)

	TArray<int32> Int32ArrayCompare;

	int32 CArray[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	Int32ArrayCompare.AddUninitialized(10);

	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);

	ensure(Int32Array == Int32ArrayCompare);

	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensure(55 == SumByAlgo);

	TSet<int32> Int32Set;
	for (int32 i = 1; i <= ArrayNum; ++i) {
		Int32Set.Add(i);
	}

	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);

	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);


	// make 300 student;

	const int32 StudentNum = 300;

	for (int32 i = 1; i <= StudentNum; ++i)
	{
		StudentData.Emplace(FStudentData(MakeRandomName(), i));

	}


	TArray<FString> AllStudentsNames;

	Algo::Transform(StudentData, AllStudentsNames,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);

	UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수: %d"), AllStudentsNames.Num());


	TSet<FString> AllUniqueNames;

	Algo::Transform(StudentData, AllUniqueNames,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);


	UE_LOG(LogTemp, Log, TEXT("중복 없는 모든 학생 이름의 수: %d"), AllUniqueNames.Num());


	Algo::Transform(StudentData, StudentsMap,
		[](const FStudentData& Val)
		{
			return TPair<int32, FString>(Val.Order, Val.Name);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드수 : %d"), StudentsMap.Num());

	TMap<FString, int32> StudentsMapByUniqueName;
	
	Algo::Transform(StudentData, StudentsMapByUniqueName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 맵의 레코드수 : %d"), StudentsMapByUniqueName.Num());

	TMultiMap<FString, int32> StudentsMapByName;

	Algo::Transform(StudentData, StudentsMapByName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 멀티 맵의 레코드수 : %d"), StudentsMapByName.Num());


	const FString TargetName(TEXT("이혜은"));
	TArray<int32> AllOrders;

	StudentsMapByName.MultiFind(TargetName, AllOrders);
	UE_LOG(LogTemp, Log, TEXT("이름이 %s인 학생 수 %d"), *TargetName ,AllOrders.Num());


	TSet<FStudentData> StudentSet;

	for (int32 i = 1; i <= StudentNum; ++i)
	{
		StudentSet.Emplace(FStudentData(MakeRandomName(), i));

	}

	



}
