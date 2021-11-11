//
// Created by mikolaj on 10.11.2021.
//

#pragma once

#include "Arduino.h"
#include "Streaming.h"

void assert(bool iff){
    if (iff == false){
        Serial<<"Assertion fault\n";
        Serial.flush();
        while (true){
            delay(1);
        }
    }
}