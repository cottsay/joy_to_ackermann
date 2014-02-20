#include "joy_to_ackermann/joy_to_ackermann_nodelet.hpp"

#include <pluginlib/class_list_macros.h>

PLUGINLIB_DECLARE_CLASS( joy_to_ackermann, joy_to_ackermann_nodelet, joy_to_ackermann::joy_to_ackermann_nodelet, nodelet::Nodelet )

namespace joy_to_ackermann
{

joy_to_ackermann_nodelet::joy_to_ackermann_nodelet( const bool _autostart ) :
	controller( NULL ),
	autostart( _autostart )
{
}

joy_to_ackermann_nodelet::~joy_to_ackermann_nodelet( )
{
	delete controller;
}

void joy_to_ackermann_nodelet::onInit( )
{
	controller = new joy_to_ackermann( getNodeHandle( ), getPrivateNodeHandle( ) );

	if( autostart && !start( ) )
		ROS_ERROR( "Failed to start controller" );
}

bool joy_to_ackermann_nodelet::start( )
{
	return ( NULL != controller ) && controller->start( );
}

void joy_to_ackermann_nodelet::stop( )
{
	if( NULL != controller )
		controller->stop( );
}

bool joy_to_ackermann_nodelet::stat( )
{
	return ( NULL != controller ) && controller->stat( );
}

void joy_to_ackermann_nodelet::set_linear_scale( const float _linear_scale )
{
	if( controller )
		controller->set_linear_scale( _linear_scale );
}

void joy_to_ackermann_nodelet::set_angular_scale( const float _angular_scale )
{
	if( controller )
		controller->set_angular_scale( _angular_scale );
}

}
