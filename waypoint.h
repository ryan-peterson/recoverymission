#pragma once

class Waypoint
{
    public:
        Waypoint();
        Waypoint(double lzLat, double lzLong, double bearing, double windSpeed, double windDir, double lzElev, double recoveryAlt, double recoverySpeed=65);
        double getWpLat();
        double getWpLong();
        double getAirspeed();
        double getHeight();
        int getEwOffset();
        int getNsOffset();
        double getLzLat();
        double getLzLong();
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
        int ewOffset;
        int nsOffset;
};