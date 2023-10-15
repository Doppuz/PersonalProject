// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootInterface.h"
#include "../Components/GeneralComponents/ShooterComponent.h"

// Add default functionality here for any IShootInterface functions that are not pure virtual.

bool IShootInterface::Shoot()
{
    if (GetShooterComponent())
    {
        return GetShooterComponent()->Shoot();
    }

    return false;
}
