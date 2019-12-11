// Fill out your copyright notice in the Description page of Project Settings.


#include "RGameInstance.h"
#include "MoviePlayer/Public/MoviePlayer.h"


URGameInstance::URGameInstance() {

}

void URGameInstance::Init() {
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &URGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &URGameInstance::EndLoadingScreen);
}

void URGameInstance::BeginLoadingScreen(const FString& InMapName) {
	
	if (!IsRunningDedicatedServer()) {
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.bWaitForManualStop = true;
		LoadingScreen.bMoviesAreSkippable = true;
		LoadingScreen.MoviePaths.Add(TEXT("TestMovie"));

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
		GetMoviePlayer()->PlayMovie();
	}
}

void URGameInstance::EndLoadingScreen(UWorld* InLoadedWorld) {

}