// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"
#include "Components/GridPanel.h"
#include "Components/ProgressBar.h"
#include "Blueprint/WidgetTree.h"	
#include "Styling/SlateTypes.h"	
#include "Components/GridSlot.h"

//I am not usign it atm but might be useful later
/*void UHealthWidget::CreateInitialHealth(int MaxHealth)
{
	if (ensureAlways(HealthGrid))
	{
		HealthGrid->RowFill.Empty();
		HealthGrid->ColumnFill.Empty(); 
		HealthGrid->ClearChildren(); 
		ProgressBars.Empty();

		HealthGrid->RowFill.Add(1.f);

		for (int i = 0; i < MaxHealth; i++)
		{
			UProgressBar* CurrentProgressBar = WidgetTree->ConstructWidget<UProgressBar>(UProgressBar::StaticClass());

			if (ensureAlways(CurrentProgressBar))
			{
				FProgressBarStyle ProgressBarStyle;
				ProgressBarStyle.BackgroundImage.TintColor = FLinearColor(1.f, 1.f, 1.f, 0.f);
				ProgressBarStyle.FillImage.DrawAs = ESlateBrushDrawType::RoundedBox;
				ProgressBarStyle.FillImage.TintColor = FLinearColor::Red;
				ProgressBarStyle.FillImage.OutlineSettings.Width = 1.f;
				ProgressBarStyle.FillImage.OutlineSettings.Color = FLinearColor::Black;

				CurrentProgressBar->SetPercent(100.f);
				CurrentProgressBar->SetWidgetStyle(ProgressBarStyle);

				UGridSlot* CurrentSlot = HealthGrid->AddChildToGrid(CurrentProgressBar, 0, i);

				if (ensureAlways(CurrentSlot))
				{
					CurrentSlot->SetPadding(FMargin(1.f, 0.f, 1.f, 0.f));
				}

				HealthGrid->ColumnFill.Add(1.f);

				ProgressBars.Add(CurrentProgressBar);
			}
		}
	}
}*/