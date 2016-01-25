/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
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

#ifndef MODEL_PLANTEQUIPMENTOPERATIONOUTDOORRELATIVEHUMIDITY_IMPL_HPP
#define MODEL_PLANTEQUIPMENTOPERATIONOUTDOORRELATIVEHUMIDITY_IMPL_HPP

#include "ModelAPI.hpp"
#include "PlantEquipmentOperationRangeBasedScheme_Impl.hpp"

namespace openstudio {
namespace model {

namespace detail {

  /** PlantEquipmentOperationOutdoorRelativeHumidity_Impl is a PlantEquipmentOperationRangeBasedScheme_Impl that is the implementation class for PlantEquipmentOperationOutdoorRelativeHumidity.*/
  class MODEL_API PlantEquipmentOperationOutdoorRelativeHumidity_Impl : public PlantEquipmentOperationRangeBasedScheme_Impl {
   public:
    /** @name Constructors and Destructors */
    //@{

    PlantEquipmentOperationOutdoorRelativeHumidity_Impl(const IdfObject& idfObject,
                                               Model_Impl* model,
                                               bool keepHandle);

    PlantEquipmentOperationOutdoorRelativeHumidity_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                               Model_Impl* model,
                                               bool keepHandle);

    PlantEquipmentOperationOutdoorRelativeHumidity_Impl(const PlantEquipmentOperationOutdoorRelativeHumidity_Impl& other,
                                               Model_Impl* model,
                                               bool keepHandle);

    virtual ~PlantEquipmentOperationOutdoorRelativeHumidity_Impl() {}

    //@}
    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    //@}
    /** @name Getters */
    //@{


    //@}
    /** @name Setters */
    //@{


    //@}
    /** @name Other */
    //@{

    double maximumUpperLimit() const override;

    double minimumLowerLimit() const override;


    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.PlantEquipmentOperationOutdoorRelativeHumidity");
  };

} // detail

} // model
} // openstudio

#endif // MODEL_PLANTEQUIPMENTOPERATIONOUTDOORRELATIVEHUMIDITY_IMPL_HPP

