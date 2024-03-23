// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralUserWidget.h"	
#include "Blueprint/WidgetTree.h"
#include "../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"

void UGeneralUserWidget::SetWidgetOwner(AActor* InWidgetOwner)
{
	WidgetOwner = InWidgetOwner;

	TArray<UWidget*> OutWidgets;
	WidgetTree->GetAllWidgets(OutWidgets);

	for (int i = 0; i < OutWidgets.Num(); i++)
	{
		UGeneralUserWidget* CurrentGeneralUserWidget = Cast<UGeneralUserWidget>(OutWidgets[i]);
		if (CurrentGeneralUserWidget)
		{
			CurrentGeneralUserWidget->SetWidgetOwner(InWidgetOwner);
		}
	}
}

void UGeneralUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureAlways(GetWorld()))
	{
		WS_GlobalEvents = GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();
	}
}
