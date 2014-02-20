#ifndef _joy_to_ackermann_nodelet_hpp
#define _joy_to_ackermann_nodelet_hpp

#include "joy_to_ackermann/joy_to_ackermann.hpp"

#include <nodelet/nodelet.h>

namespace joy_to_ackermann
{
	class joy_to_ackermann_nodelet : public nodelet::Nodelet
	{
	public:
		joy_to_ackermann_nodelet( const bool _autostart = true );
		~joy_to_ackermann_nodelet( );
		bool start( );
		void stop( );
		bool stat( );
		void set_linear_scale( const float _linear_scale );
		void set_angular_scale( const float _angular_scale );

	private:
		virtual void onInit( );
		joy_to_ackermann *controller;
		const bool autostart;
	};
}

#endif /* _joy_to_ackermann_nodelet_hpp */
