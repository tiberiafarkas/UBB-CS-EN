#pragma once
#include "Service.h"

typedef struct {
	Service* service;
} UI;

void start(UI* ui);
UI* createUI(Service* service);