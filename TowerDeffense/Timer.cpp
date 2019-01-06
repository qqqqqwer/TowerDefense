#include "Timer.h"

Timer::Timer() {
	bPaused = false;
	runTime = 0;
	mC.restart();
}

void Timer::Reset() {
	this->mC.restart();
	this->runTime = 0;
	this->bPaused = false;
}

void Timer::Start() {
	if (this->bPaused) {
		this->mC.restart();
	}
	this->bPaused = false;
}

void Timer::Pause() {
	if (!this->bPaused) {
		this->runTime += this->mC.getElapsedTime().asSeconds();
	}
	bPaused = true;
}

float Timer::GetElapsedSeconds() {
	if (!this->bPaused) {
		return this->runTime + this->mC.getElapsedTime().asSeconds();
	}
	return this->runTime;
}