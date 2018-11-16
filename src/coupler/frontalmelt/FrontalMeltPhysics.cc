/* Copyright (C) 2018 PISM Authors
 *
 * This file is part of PISM.
 *
 * PISM is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 *
 * PISM is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PISM; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include <cmath> // pow

#include "FrontalMeltPhysics.hh"

#include "pism/util/ConfigInterface.hh"

namespace pism {
namespace frontalmelt {

FrontalMeltPhysics::FrontalMeltPhysics(const Config &config) {
  m_alpha = config.get_double("frontal_melt.power_alpha");
  m_beta  = config.get_double("frontal_melt.power_beta");
  m_A     = config.get_double("frontal_melt.parameter_a");
  m_B     = config.get_double("frontal_melt.parameter_b");
}

/*!
 * Parameterization of the frontal melt rate.
 *
 * This function implements equation 1 from [@ref Rignotetal2016].
 *
 * q_m = (A * h * Q_sg ^{\alpha} + B) * TF^{\beta}
 *
 * where A, B, alpha, beta are tuning parameters. Note that Rignot (2016) is an update on
 * Xu 2013 with slightly different parameter values.
 *
 * @param[in] h water depth, meters
 * @param[in] q_sg subglacial water flux, m / day
 * @param[in] TF thermal forcing, Celsius
 *
 * @returns frontal melt rate, m / day.
 */
double FrontalMeltPhysics::frontal_melt_from_undercutting(double h, double q_sg, double TF) const {
  return (m_A * h * pow(q_sg, m_alpha) + m_B) * pow(TF, m_beta);
}


} // end of namespace frontalmeltmodel
} // end of namespace pism
