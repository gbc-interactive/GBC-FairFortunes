#include "FFLogger.h"

void FFLogger::LogMessage(LogMessageSeverity severity, FString message)
{


	switch (severity)
	{
		case LogMessageSeverity::Debug:
			UE_LOG(LogTemp, Log, TEXT("%s"), *message);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, *message);
			break;
		case LogMessageSeverity::Warning:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *message);
			break;
		case LogMessageSeverity::Error:
			UE_LOG(LogTemp, Error, TEXT("%s"), *message);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *message);
			break;
	}
}
