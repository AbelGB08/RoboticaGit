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
#include <eigen3/Eigen/Dense>
struct Target
{
    float x; float y;
    mutable std::mutex my_mutex;
    bool activate = false;
    int variable = 0;

    void put(float x_,float y_)
    {
        std::lock_guard<std::mutex> guard(my_mutex);
        x=x_;y=y_;   // generic type must be copy-constructable
        activate = true;
        variable = 0;
        
    }
    std::optional<std::tuple<float,float>> get()
    {
        std::lock_guard<std::mutex> guard(my_mutex);
        if(activate)
            return std::make_tuple(x,y);
        else
            return {};
    }
    void set_task_finished()
    {
        std::lock_guard<std::mutex> guard(my_mutex);
        activate = false;
    }
}buffer;

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(TuplePrx tprx, bool startup_check) : GenericWorker(tprx)
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
	RoboCompGenericBase::TBaseState state;
	const ::Ice::Context& context = ::Ice::noExplicitContext;
	differentialrobot_proxy->getBaseState(state, context);
	if (auto t = buffer.get();t.has_value())
	{ //std::min(dist*(1/1000),1);
		auto tw = t.value();
		Eigen::Vector2f rw(state.x,state.z);
		Eigen::Matrix2f rot;
		Eigen::Vector2f ty(get<0>(tw),get<1>(tw));
		rot<<cos(state.alpha),-sin(state.alpha),sin(state.alpha),cos(state.alpha);
		auto tr = rot*(ty-rw);
		auto beta = atan2(tr[0],tr[1]);	
		auto dist = tr.norm();
		auto hola = std::min(dist/1000,(float)1);
		std::cout << buffer.variable << std::endl;
		switch(buffer.variable){
			case 0:
			differentialrobot_proxy->setSpeedBase(1000*hola*buffer.variable, beta);
			if(beta > 0.09 || beta < -0.09){
			buffer.variable = 0;
			}else{buffer.variable = 1;}break;
			case 1:
			differentialrobot_proxy->setSpeedBase(1000*hola*buffer.variable, beta);
			if(hola<0.05){
				buffer.variable = 2;
			}
			break;
			case 2:
			differentialrobot_proxy->setSpeedBase(0, 0);
			buffer.set_task_finished();
			break;
		}
		
		
	}
}


int SpecificWorker::startup_check()
{
	std::cout << "Startup check" << std::endl;
	QTimer::singleShot(200, qApp, SLOT(quit()));
	return 0;
}


//SUBSCRIPTION to setPick method from RCISMousePicker interface
void SpecificWorker::RCISMousePicker_setPick(RoboCompRCISMousePicker::Pick myPick)
{
    //subscribesToCODE
    qDebug() << myPick.x << myPick.y << myPick.z;
    buffer.put(myPick.x,myPick.z);
    
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

/**************************************/
// From the RoboCompRCISMousePicker you can use this types:
// RoboCompRCISMousePicker::Pick

