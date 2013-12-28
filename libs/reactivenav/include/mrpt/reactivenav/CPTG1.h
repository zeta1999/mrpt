/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2014, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */
#ifndef CPTG1_H
#define CPTG1_H

#include <mrpt/reactivenav/CParameterizedTrajectoryGenerator.h>

namespace mrpt
{
  namespace reactivenav
  {

	/** A PTG for circular paths ("C" type PTG in papers). 
	 * 
	 * Accepted parameters in the constructor:
	 * - params["ref_distance"]: Maximum trayectory distance (meters).
	 * - params["v_max"]: Maximum linear velocity (m/s)
	 * - params["w_max"]: Maximum angular velocity (rad/s)
	 * - params["K"]: Can be "+1" for forward paths, or "-1" for backward paths.
	 * 
	 * This PT generator functions are: 
	 *
	 * \f[ v(\alpha) = V_MAX \sign(K) \f]
	 * \f[ \omega(\alpha) = \dfrac{\alpha}{\pi} W_MAX \sign(K) \f]
	 *
	 * So, the radius of curvature of each trajectory is constant for each "alpha" value (the trajectory parameter):
	 *
	 *  \f[ R(\alpha) = \dfrac{v}{\omega} = \dfrac{V_MAX}{W_MAX} \dfrac{\pi}{\alpha} \f]
	 *
	 * from which a minimum radius of curvature can be set by selecting the appropriate values of V_MAX and W_MAX, 
	 * knowning that \f$ \alpha \in (-\pi,\pi) \f$.
	 *
	 *  ![C-PTG path examples](PTG1_paths.png)
	 *
	 *  \ingroup mrpt_reactivenav_grp
	 */
	class REACTIVENAV_IMPEXP CPTG1 : public CParameterizedTrajectoryGenerator
	{
	 public:
			/** Constructor: possible values in "params", those of CParameterizedTrajectoryGenerator plus:
			 *   - K: Direction, +1 or -1
			 */
			CPTG1(const TParameters<double> &params );

			/** The lambda function. */
			void lambdaFunction( float x, float y, int &out_k, float &out_d );

			/** Gets a short textual description of the PTG and its parameters. */
			std::string getDescription() const;


			bool PTG_IsIntoDomain( float x, float y );
			void PTG_Generator( float alpha, float t,float x, float y, float phi, float &v, float &w );

	 protected:
			/** A generation parameter */
			float	K;
	};
  }
}


#endif

