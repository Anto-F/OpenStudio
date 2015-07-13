/**********************************************************************
 *  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#ifndef MODEL_COILSYSTEMCOOLINGWATERHEATEXCHANGERASSISTED_IMPL_HPP
#define MODEL_COILSYSTEMCOOLINGWATERHEATEXCHANGERASSISTED_IMPL_HPP

#include <model/ModelAPI.hpp>
#include <model/StraightComponent_Impl.hpp>

namespace openstudio {
namespace model {

class AirToAirComponent;
class WaterToAirComponent;

namespace detail {

  /** CoilSystemCoolingWaterHeatExchangerAssisted_Impl is a StraightComponent_Impl that is the implementation class for CoilSystemCoolingWaterHeatExchangerAssisted.*/
  class MODEL_API CoilSystemCoolingWaterHeatExchangerAssisted_Impl : public StraightComponent_Impl {
   public:
    /** @name Constructors and Destructors */
    //@{

    CoilSystemCoolingWaterHeatExchangerAssisted_Impl(const IdfObject& idfObject,
                                                     Model_Impl* model,
                                                     bool keepHandle);

    CoilSystemCoolingWaterHeatExchangerAssisted_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                     Model_Impl* model,
                                                     bool keepHandle);

    CoilSystemCoolingWaterHeatExchangerAssisted_Impl(const CoilSystemCoolingWaterHeatExchangerAssisted_Impl& other,
                                                     Model_Impl* model,
                                                     bool keepHandle);

    virtual ~CoilSystemCoolingWaterHeatExchangerAssisted_Impl() {}

    //@}
    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const;

    virtual IddObjectType iddObjectType() const;

    //@}
    /** @name Getters */
    //@{

    AirToAirComponent heatExchanger() const;

    WaterToAirComponent coolingCoil() const;

    //@}
    /** @name Setters */
    //@{

    bool setHeatExchanger(const AirToAirComponent& heatExchanger);

    bool setCoolingCoil(const WaterToAirComponent& coolingCoil);

    //@}
    /** @name Other */
    //@{

    unsigned inletPort();

    unsigned outletPort();

    bool addToNode(Node & node);

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.CoilSystemCoolingWaterHeatExchangerAssisted");

    boost::optional<AirToAirComponent> optionalHeatExchanger() const;
    boost::optional<WaterToAirComponent> optionalCoolingCoil() const;
  };

} // detail

} // model
} // openstudio

#endif // MODEL_COILSYSTEMCOOLINGWATERHEATEXCHANGERASSISTED_IMPL_HPP

