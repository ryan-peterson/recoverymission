#pragma once

class Waypoint
{
    public:
        Waypoint(double lzLat, double lzLong, double bearing, double windSpeed, double windDir, double lzElev, double recoveryAlt, double recoverySpeed=65);
        double getWpLat();
        double getWpLong();
        double getAirspeed();
        double getHeight();
        void setChuteWP();
        void setEngineWP(double chuteLat, double chuteLong);
        void setApproachWP(double engineLat, double engineLong);
        void setRunOutWP(double chuteLat, double chuteLong);
    private:
        double wpLat;
        double wpLong;
        double airspeed;
        double height;
        double landingLat;
        double landingLong;
        double approachBearing;
        double wspeed;
        double wdir;
        double landingElev;
};