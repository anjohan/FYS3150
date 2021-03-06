#ifndef PLANET_H
#define PLANET_H
#include <cmath>
#include <cstdio>
using namespace std;

class Planet{
    public:
        Planet(char* name_in, double mass_relative_to_sun, double x_in, double y_in, double z_in, double vx_in, double vy_in, double vz_in){
            name = name_in;
            mass_ratio = mass_relative_to_sun;
            mass_ratio_4pi2  = 4 * M_PI * M_PI * mass_relative_to_sun;
            x = x_in;
            y = y_in;
            z = z_in;
            vx = vx_in;
            vy = vy_in;
            vz = vz_in;
        }
        virtual ~Planet(){;}
        void reset_acceleration(){
            ax = 0; ay = 0; az = 0;
            ax_old = 0; ay_old = 0; az_old = 0;
        }
        void euler_update_position();
        void euler_update_velocity();
        virtual void verlet_update_position();
        void verlet_update_velocity();
        virtual void calculate_acceleration(Planet* other);
        void move_acceleration();
        void set_dt(double dt_in){
            dt = dt_in;
            halfdt = 0.5*dt;
            halfdt2 = 0.5*dt*dt;
        }
        double x, y, z, vx, vy, vz, ax, ay, az, ax_old, ay_old, az_old;
        double mass_ratio, mass_ratio_4pi2;
    protected:
        char* name;
        double dt, halfdt, halfdt2;
};

class StationaryPlanet : public Planet{
    public:
        StationaryPlanet(char* name_in, double mass_relative_to_sun, double x_in, double y_in, double z_in, double vx_in, double vy_in, double vz_in) : Planet(name_in, mass_relative_to_sun, x_in, y_in, z_in, vx_in, vy_in, vz_in){;}
        virtual ~StationaryPlanet(){;}
        virtual void calculate_acceleration(Planet* other){;}
};

class PerihelionFinder : public Planet{
    public:
        PerihelionFinder(char* name_in, double mass_relative_to_sun, double x_in, double y_in, double z_in, double vx_in, double vy_in, double vz_in) : Planet(name_in, mass_relative_to_sun, x_in, y_in, z_in, vx_in, vy_in, vz_in){
            i = 0;
            filename = new char[100];
            sprintf(filename,"%sperihelion.dat",name);
            perihelionfile = fopen(filename,"w");
            r = 0; r_old = 1; r_reallyold = 0;
        }
        void verlet_update_position();
        virtual void calculate_acceleration(Planet* other){
            Planet::calculate_acceleration(other);
        }
        virtual ~PerihelionFinder(){
            fclose(perihelionfile);
            delete [] filename;
        }
    protected:
        double r, r_old, r_reallyold;
        int i;
        FILE* perihelionfile;
        char* filename;
};

class RelativisticPlanet : public PerihelionFinder{
    public:
        RelativisticPlanet(char* name_in, double mass_relative_to_sun, double x_in, double y_in, double z_in, double vx_in, double vy_in, double vz_in) : PerihelionFinder(name_in, mass_relative_to_sun, x_in, y_in, z_in, vx_in, vy_in, vz_in){
            c = 63239.7263; // ua/yr
        }
        void calculate_acceleration(Planet* other);
    private:
        double c;
};


#endif
