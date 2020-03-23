#pragma once

double latitudeAlongBearing(double startLat, double bearing, double distance);

double longitudeAlongBearing(double startLat, double startLong, double bearing, double distance);

double calcBearing(double startLat, double startLong, double endLat, double endLong);

double calcDistance(double startLat, double startLong, double endLat, double endLong);

int calcEwOffset(double startLat, double endLat, double startLong, double endLong);

int calcNwOffset(double startLat, double endLat, double startLong, double endLong);