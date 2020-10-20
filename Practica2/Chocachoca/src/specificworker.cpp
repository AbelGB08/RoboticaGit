/*
 *    Copyright (C) 2020 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "specificworker.h"

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx, bool startup_check) : GenericWorker(mprx)
{
	this->startup_check_flag = startup_check;
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	std::cout << "Destroying SpecificWorker" << std::endl;
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
//	THE FOLLOWING IS JUST AN EXAMPLE
//	To use innerModelPath parameter you should uncomment specificmonitor.cpp readConfig method content
//	try
//	{
//		RoboCompCommonBehavior::Parameter par = params.at("InnerModelPath");
//		std::string innermodel_path = par.value;
//		innerModel = std::make_shared(innermodel_path);
//	}
//	catch(const std::exception &e) { qFatal("Error reading config params"); }






	return true;
}

void SpecificWorker::initialize(int period)
{
	std::cout << "Initialize worker" << std::endl;
	this->Period = period;
	if(this->startup_check_flag)
	{
		this->startup_check();
	}
	else
	{
		timer.start(Period);
	}

}

void SpecificWorker::compute()
{
    const float threshold = 200; // millimeters
    float rot = 2;  // rads per second
    RoboCompGenericBase::TBaseState state;
    const ::Ice::Context& context = ::Ice::noExplicitContext;
    bool map[11][11]; //mapa de posiciones

    //obtener la posicion inicial
    differentialrobot_proxy->getBaseState(state, context);
    int x = floor((abs((state.x/400) + 5)));
    int z = floor((abs((state.z/400) - 5)));

    try
    {
        // read laser data
        RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();
        //sort laser data from small to large distances using a lambda function.
        std::sort( ldata.begin(), ldata.end(), [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return     a.dist < b.dist; });

        //girar cuando encuentre una pared o antes de pasar por una posicion ya visitada
        if( ldata.front().dist < threshold)
        {
            //girar a izquierda o derecha al chocar con las paredes
            if (ldata.front().angle <= 0)
            {
                differentialrobot_proxy->setSpeedBase(0, rot);
            }
            else
            {
                differentialrobot_proxy->setSpeedBase(0, -rot);
            }

            //evitar que se quede atascado en las esquinas
            if((x==0 && z==0)||(x==0 && z==10)||(x==10 && z==0)||(x==10 && z==10))
            {
                differentialrobot_proxy->setSpeedBase(0, -rot);

            }
        }
        else
        {
            //evitar que pase por la misma zona
            if (map[x+1][z] && map[x-1][z])
            {
                if (ldata.front().angle <= 0)
                {
                    differentialrobot_proxy->setSpeedBase(0, rot);
                }
                else
                {
                    differentialrobot_proxy->setSpeedBase(0, -rot);
                }
                usleep(250000);
                map[x+1][z] = false;
                map[x-1][z] = false;
            }

            if (map[x][z-1] && map[x][z+1])
            {
                if (ldata.front().angle <= 0)
                {
                    differentialrobot_proxy->setSpeedBase(0, rot);
                }
                else
                {
                    differentialrobot_proxy->setSpeedBase(0, -rot);
                }
                usleep(250000);
                map[x][z-1] = false;
                map[x][z+1] = false;
            }

            //calcular posicion en el mundo
            differentialrobot_proxy->getBaseState(state, context);

            //calcular la posicion de la celda que corresponda dentro del mapa
            x = floor((abs((state.x/400) + 5)));
            z = floor((abs((state.z/400) - 5)));

            std::cout << "Posicion x: " << x << endl;
            std::cout << "Posicion z: " << z << endl;

            //poner posicion del mapa a true
            if (!map[x][z])
            {
                map[x][z] = true;
                std::cout << "Valor de la posicion [" << x << "][" << z << "]: " << map[x][z]<<endl;
            }

            differentialrobot_proxy->setSpeedBase(1000, 0);
        }
    }
    catch(const Ice::Exception &ex)
    {
        std::cout << ex << std::endl;
    }
}

int SpecificWorker::startup_check()
{
	std::cout << "Startup check" << std::endl;
	QTimer::singleShot(200, qApp, SLOT(quit()));
	return 0;
}




/**************************************/
// From the RoboCompDifferentialRobot you can call this methods:
// this->differentialrobot_proxy->correctOdometer(...)
// this->differentialrobot_proxy->getBasePose(...)
// this->differentialrobot_proxy->getBaseState(...)
// this->differentialrobot_proxy->resetOdometer(...)
// this->differentialrobot_proxy->setOdometer(...)
// this->differentialrobot_proxy->setOdometerPose(...)
// this->differentialrobot_proxy->setSpeedBase(...)
// this->differentialrobot_proxy->stopBase(...)

/**************************************/
// From the RoboCompDifferentialRobot you can use this types:
// RoboCompDifferentialRobot::TMechParams

/**************************************/
// From the RoboCompLaser you can call this methods:
// this->laser_proxy->getLaserAndBStateData(...)
// this->laser_proxy->getLaserConfData(...)
// this->laser_proxy->getLaserData(...)

/**************************************/
// From the RoboCompLaser you can use this types:
// RoboCompLaser::LaserConfData
// RoboCompLaser::TData

