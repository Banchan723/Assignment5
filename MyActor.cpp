#include "MyActor.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"  // RandRange사용을 위해 필요하다고함

AMyActor::AMyActor()
// 기본 생성자인 AMyActor
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentPosition = FVector(0.0f, 0.0f, 0.0f);  // 스폰 시작점을 (0,0)으로 초기화
	TotalDistanceMoved = 0.0f;
	TotalEventsTriggered = 0;
}


void AMyActor::BeginPlay()
// BeginPlay() : 게임 시작 시 호출됨
{
	Super::BeginPlay();

	Move();
	// 액터가 스폰될 때 Move함수 시작함.

}

void AMyActor::Tick(float DeltaTime)
// 안씀
{
	Super::Tick(DeltaTime);
}


int32 AMyActor::Step()
// 헤더파일에 Step()정의
{
	return FMath::RandRange(0, 1);  
	// RandRange를 사용해 0이나 1중에서 랜덤으로 반환
	// X좌표 또는 Y좌표가 한번에 2이상 이동X
}

// 거리 계산 함수
float AMyActor::CalculateDistance(const FVector& PreviousPos, const FVector& CurrentPos)
// const Fvector& PreviousPos는 이전 좌표를 말하고
// const Fvector& CurrentPos는 현재 좌표를 말함
// 둘다 FVector로 3D 벡터를 나타냄 (X, Y, Z 세 축의 값)
{
	return FVector::Dist(PreviousPos, CurrentPos);  
	// Dist는 언리얼 엔진 FVector 클래스에 내장된 정적 함수다.
	// Dist로 두 점 사이의 유클리드 거리를 계산할 수 있다.
	// ex) Distance = sqrt((X2 - X1)^2 + (Y2 - Y1)^2 + (Z2 - Z1)^2)
	// 이렇게 3D공간을 계산하지만 여기선s Z좌표를 안쓰기때문에 2D거리만 계산함
	// ex) Distance = sqrt((X2 - X1)^2 + (Y2 - Y1)^2)
	// 계산한 값을 float값으로 CalcualteDistance함수로 아래 코드에서 사용될 것이다.


}

bool AMyActor::TriggerEvent()
// 50% 확률로 랜덤 이벤트 발생 여부를 반환

{
	return FMath::RandBool(); 
	// 50% 확률로 true or false 반환

}

// 이동 함수 (10회 이동)
void AMyActor::Move()
{// 헤더파일에 Move정의
	FVector PreviousPosition = CurrentPosition;
	// 이전 좌표를 저장할려고 PreviousPosition변수에 현재 위치를 복사.

	for (int i = 0; i < 10; ++i) 
		// 아래 코드를 10번 실행하게 반복
		// 한번 실행될때마다 액터가 새로운 좌표로 이동
	{
		
		int32 StepX = Step();
		int32 StepY = Step();
		// X랑 Y좌표에 대한 랜덤이동값을 계산
		// step()함수는 위에정의에서 RandRange(0, 1)로 0이나 1을 랜덤으로 반환하기때문에
		// 한 번 루프를 돌동안 최대 1씩 증가하거나 그대로 있음
		// step()함수때문에 2씩은 증가가 불가능


		CurrentPosition.X += StepX;
		CurrentPosition.Y += StepY;
		// 위에서 stepX랑 stepY가 랜덤으로 1이나 0이 저장된값을 currentPosition.X랑
		// .Y에 더한다.
		// 그래서 액터가 새로운 위치로 이동함

	
		float DistanceMoved = CalculateDistance(PreviousPosition, CurrentPosition);
		TotalDistanceMoved += DistanceMoved;
		// 이동 거리 계산 및 출력
		// CalculateDistance함수로 이전 위치인 PreviousPosition이랑
		// 현재 위치 사이인 CurrentPosition의 거리를 계산
		// 그래서 총 이동한 거리를 TotalDistanceMoved에 저장.


		UE_LOG(LogTemp, Warning, TEXT("Step %d: X = %f, Y = %f, Distance Moved = %f"), i + 1, CurrentPosition.X, CurrentPosition.Y, DistanceMoved);
		// 현재 좌표와 이동 거리 로그 출력
		// ex) LogTemp: Warning: Step 1: X = 0.000000, Y = 1.000000, Distance Moved = 1.000000
	

		bool bEventOccurred = TriggerEvent();
		// triggerEvent()함수로 50%확률 이벤트 발생을 결정함
		if (bEventOccurred) 
			// 이벤트가 발생할 경우
		{
			TotalEventsTriggered++;
			// 이벤트 발생 횟수를 카운트

			UE_LOG(LogTemp, Warning, TEXT("Event Occurred at Step %d"), i + 1);
			//이벤트 발생했다는 로그 출력
			//ex) LogTemp: Warning: Event Occurred at Step 4

		}
		PreviousPosition = CurrentPosition;
		// 이전 좌표를 PreviousPosition으로 업데이트 해서 for문을 반복할때마다 기억할 수있게 
		// 이동한 좌표인 CurrentPosition을 PreviousPosition인 현재 위치로 만들어줌
	}

	UE_LOG(LogTemp, Warning, TEXT("Total Distance Moved: %f"), TotalDistanceMoved);
	// 총 이동 거리출력하기
	// ex) LogTemp: Warning: Total Distance Moved: 7.414214


	UE_LOG(LogTemp, Warning, TEXT("Total Events Triggered: %d"), TotalEventsTriggered);
	// 총 이벤트 발생 횟수 출력하기
	//ex) LogTemp: Warning: Total Events Triggered: 4

}
