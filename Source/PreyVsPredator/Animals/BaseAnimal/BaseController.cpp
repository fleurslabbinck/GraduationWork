#include "BaseController.h"


void ABaseController::SetTimer(const FTimerDelegate& Delegate, float InRate)
{
	GetWorld()->GetTimerManager().SetTimer(m_Timer, Delegate, InRate, false);
}

void ABaseController::ResetTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(m_Timer);
}
