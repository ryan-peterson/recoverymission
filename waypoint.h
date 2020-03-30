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
        int getDrift();
        double getLzLat();
        double getLzLong();
        double getBearing();
        double getLzElev();
        double getWindDir();
        double getWindSpeed();
        void setChuteWP();
        void setEngineWP(double chuteLat, double chuteLong);
        void setApproachWP(double engineLat, double engineLong);
        void setRunOutWP(double chuteLat, double chuteLong);
        void setLzLat(double lzLat);
        void setLzLong(double lzLong);
        void setLzElev(double lzElev);
        void setBearing(double bearing);
        void setRecAlt(double recAlt);
        void setRecSpeed(double recSpeed);
        void setWindDir(double windDir);
        void setWindSpeed(double windSpeed);
        
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