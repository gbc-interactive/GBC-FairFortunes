// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


enum LogMessageSeverity
{
	Debug,
	Warning,
	Error
};


/**
 * 
 */
static class MYCROWD_V3_API FFLogger
{

public:
	static void LogMessage(LogMessageSeverity severity, FString message);
};
