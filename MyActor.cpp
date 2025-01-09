#include "MyActor.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"  // RandRange����� ���� �ʿ��ϴٰ���

AMyActor::AMyActor()
// �⺻ �������� AMyActor
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentPosition = FVector(0.0f, 0.0f, 0.0f);  // ���� �������� (0,0)���� �ʱ�ȭ
	TotalDistanceMoved = 0.0f;
	TotalEventsTriggered = 0;
}


void AMyActor::BeginPlay()
// BeginPlay() : ���� ���� �� ȣ���
{
	Super::BeginPlay();

	Move();
	// ���Ͱ� ������ �� Move�Լ� ������.

}

void AMyActor::Tick(float DeltaTime)
// �Ⱦ�
{
	Super::Tick(DeltaTime);
}


int32 AMyActor::Step()
// ������Ͽ� Step()����
{
	return FMath::RandRange(0, 1);  
	// RandRange�� ����� 0�̳� 1�߿��� �������� ��ȯ
	// X��ǥ �Ǵ� Y��ǥ�� �ѹ��� 2�̻� �̵�X
}

// �Ÿ� ��� �Լ�
float AMyActor::CalculateDistance(const FVector& PreviousPos, const FVector& CurrentPos)
// const Fvector& PreviousPos�� ���� ��ǥ�� ���ϰ�
// const Fvector& CurrentPos�� ���� ��ǥ�� ����
// �Ѵ� FVector�� 3D ���͸� ��Ÿ�� (X, Y, Z �� ���� ��)
{
	return FVector::Dist(PreviousPos, CurrentPos);  
	// Dist�� �𸮾� ���� FVector Ŭ������ ����� ���� �Լ���.
	// Dist�� �� �� ������ ��Ŭ���� �Ÿ��� ����� �� �ִ�.
	// ex) Distance = sqrt((X2 - X1)^2 + (Y2 - Y1)^2 + (Z2 - Z1)^2)
	// �̷��� 3D������ ��������� ���⼱s Z��ǥ�� �Ⱦ��⶧���� 2D�Ÿ��� �����
	// ex) Distance = sqrt((X2 - X1)^2 + (Y2 - Y1)^2)
	// ����� ���� float������ CalcualteDistance�Լ��� �Ʒ� �ڵ忡�� ���� ���̴�.


}

bool AMyActor::TriggerEvent()
// 50% Ȯ���� ���� �̺�Ʈ �߻� ���θ� ��ȯ

{
	return FMath::RandBool(); 
	// 50% Ȯ���� true or false ��ȯ

}

// �̵� �Լ� (10ȸ �̵�)
void AMyActor::Move()
{// ������Ͽ� Move����
	FVector PreviousPosition = CurrentPosition;
	// ���� ��ǥ�� �����ҷ��� PreviousPosition������ ���� ��ġ�� ����.

	for (int i = 0; i < 10; ++i) 
		// �Ʒ� �ڵ带 10�� �����ϰ� �ݺ�
		// �ѹ� ����ɶ����� ���Ͱ� ���ο� ��ǥ�� �̵�
	{
		
		int32 StepX = Step();
		int32 StepY = Step();
		// X�� Y��ǥ�� ���� �����̵����� ���
		// step()�Լ��� �������ǿ��� RandRange(0, 1)�� 0�̳� 1�� �������� ��ȯ�ϱ⶧����
		// �� �� ������ ������ �ִ� 1�� �����ϰų� �״�� ����
		// step()�Լ������� 2���� ������ �Ұ���


		CurrentPosition.X += StepX;
		CurrentPosition.Y += StepY;
		// ������ stepX�� stepY�� �������� 1�̳� 0�� ����Ȱ��� currentPosition.X��
		// .Y�� ���Ѵ�.
		// �׷��� ���Ͱ� ���ο� ��ġ�� �̵���

	
		float DistanceMoved = CalculateDistance(PreviousPosition, CurrentPosition);
		TotalDistanceMoved += DistanceMoved;
		// �̵� �Ÿ� ��� �� ���
		// CalculateDistance�Լ��� ���� ��ġ�� PreviousPosition�̶�
		// ���� ��ġ ������ CurrentPosition�� �Ÿ��� ���
		// �׷��� �� �̵��� �Ÿ��� TotalDistanceMoved�� ����.


		UE_LOG(LogTemp, Warning, TEXT("Step %d: X = %f, Y = %f, Distance Moved = %f"), i + 1, CurrentPosition.X, CurrentPosition.Y, DistanceMoved);
		// ���� ��ǥ�� �̵� �Ÿ� �α� ���
		// ex) LogTemp: Warning: Step 1: X = 0.000000, Y = 1.000000, Distance Moved = 1.000000
	

		bool bEventOccurred = TriggerEvent();
		// triggerEvent()�Լ��� 50%Ȯ�� �̺�Ʈ �߻��� ������
		if (bEventOccurred) 
			// �̺�Ʈ�� �߻��� ���
		{
			TotalEventsTriggered++;
			// �̺�Ʈ �߻� Ƚ���� ī��Ʈ

			UE_LOG(LogTemp, Warning, TEXT("Event Occurred at Step %d"), i + 1);
			//�̺�Ʈ �߻��ߴٴ� �α� ���
			//ex) LogTemp: Warning: Event Occurred at Step 4

		}
		PreviousPosition = CurrentPosition;
		// ���� ��ǥ�� PreviousPosition���� ������Ʈ �ؼ� for���� �ݺ��Ҷ����� ����� ���ְ� 
		// �̵��� ��ǥ�� CurrentPosition�� PreviousPosition�� ���� ��ġ�� �������
	}

	UE_LOG(LogTemp, Warning, TEXT("Total Distance Moved: %f"), TotalDistanceMoved);
	// �� �̵� �Ÿ�����ϱ�
	// ex) LogTemp: Warning: Total Distance Moved: 7.414214


	UE_LOG(LogTemp, Warning, TEXT("Total Events Triggered: %d"), TotalEventsTriggered);
	// �� �̺�Ʈ �߻� Ƚ�� ����ϱ�
	//ex) LogTemp: Warning: Total Events Triggered: 4

}
