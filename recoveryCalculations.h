#pragma once

double getParachuteLat(double lzLat, double lzElev, double recoveryAlt, double windSpeed, double windDir);

double getParachuteLong(double lzLat, double lzLong, double lzElev, double recoveryAlt, double windSpeed, double windDir);

double getEngineLat(double chuteLat, double bearing, double speed);

double getEngineLong(double chuteLat, double chuteLong, double bearing, double speed);

double getApproachLat(double engineLat, double bearing);

double getApproachLong(double engineLat, double engineLong, double bearing);

double getRunOutLat(double chuteLat, double bearing);

double getRunOutLong(double chuteLat, double chutLong, double bearing);