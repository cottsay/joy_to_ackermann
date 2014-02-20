#include "joy_to_ackermann/joy_to_ackermann.hpp"

#include <ros/ros.h>
#include <ackermann_msgs/AckermannDrive.h>

namespace joy_to_ackermann
{
joy_to_ackermann::joy_to_ackermann( const ros::NodeHandle &_nh, const ros::NodeHandle &_nh_priv ) :
	nh( _nh ),
	nh_priv( _nh_priv ),
	pub_callback( boost::bind(&joy_to_ackermann::pub_cb, this) ),
	linear_scale( 0.20 ),
	angular_scale( M_PI / 4 )
{
}

joy_to_ackermann::~joy_to_ackermann( )
{
}

bool joy_to_ackermann::start( )
{
	if( !( ackermann_pub = nh.advertise<ackermann_msgs::AckermannDrive>( "ackermann_cmd", 1, pub_callback, pub_callback, ros::VoidConstPtr( ), false ) ) )
		return false;

	pub_cb( );

	return true;
}

void joy_to_ackermann::stop( )
{
	if( joy_sub )
		joy_sub.shutdown( );

	if( ackermann_pub )
		ackermann_pub.shutdown( );
}

bool joy_to_ackermann::stat( )
{
	return ackermann_pub;
}

void joy_to_ackermann::pub_cb( )
{
	if( ackermann_pub.getNumSubscribers( ) > 0 )
	{
		if( !joy_sub && !( joy_sub = nh.subscribe( "joy", 1, &joy_to_ackermann::joy_cb, this ) ) )
			ROS_ERROR( "Failed to start twist subscription" );
	}
	else if( joy_sub )
		joy_sub.shutdown( );
}

void joy_to_ackermann::joy_cb( const sensor_msgs::JoyConstPtr &msg )
{
	ackermann_msgs::AckermannDrivePtr new_msg( new ackermann_msgs::AckermannDrive );

	new_msg->speed = msg->axes[1] * linear_scale;
	new_msg->steering_angle = msg->axes[2] * angular_scale;

	ackermann_pub.publish( new_msg );
}

void joy_to_ackermann::set_linear_scale( const float _linear_scale )
{
	linear_scale = _linear_scale;
}

void joy_to_ackermann::set_angular_scale( const float _angular_scale )
{
	angular_scale = _angular_scale;
}

}
