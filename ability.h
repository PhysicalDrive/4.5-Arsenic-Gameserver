#pragma once
#include "framework.h"

static char (*Internaltryactivateability)(UAbilitySystemComponent* a1, FGameplayAbilitySpecHandle a2, FPredictionKey a3, UGameplayAbility** a4, void* a5, FGameplayEventData* a6) = decltype(Internaltryactivateability)(uintptr_t(GetModuleHandle(0)) + 0x581590);