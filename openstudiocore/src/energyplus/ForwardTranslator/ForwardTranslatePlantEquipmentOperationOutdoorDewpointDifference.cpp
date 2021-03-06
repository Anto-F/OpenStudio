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

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"
#include "../../model/PlantEquipmentOperationOutdoorDewpointDifference.hpp"
#include "../../model/PlantEquipmentOperationOutdoorDewpointDifference_Impl.hpp"
#include "../../utilities/core/Logger.hpp"
#include "../../utilities/core/Assert.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/PlantEquipmentOperation_OutdoorDewpointDifference_FieldEnums.hxx>
#include <utilities/idd/PlantEquipmentList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

using namespace openstudio::model;

using namespace std;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translatePlantEquipmentOperationOutdoorDewpointDifference( PlantEquipmentOperationOutdoorDewpointDifference & modelObject )
{
  IdfObject idfObject(IddObjectType::PlantEquipmentOperation_OutdoorDewpointDifference);
  m_idfObjects.push_back(idfObject);

  // Name
  auto name = modelObject.name().get();
  idfObject.setName(name);

  // ReferenceTemperatureNodeName
  if( const auto & node = modelObject.referenceTemperatureNode() ) {
    idfObject.setString(PlantEquipmentOperation_OutdoorDewpointDifferenceFields::ReferenceTemperatureNodeName,node->name().get());
  }

  double lowerLimit = modelObject.minimumLowerLimit();
  int i = 1;
  for( auto upperLimit : modelObject.loadRangeUpperLimits() ) {
    auto equipment = modelObject.equipment(upperLimit);
    if( ! equipment.empty() ) {
      auto eg = idfObject.pushExtensibleGroup();
      eg.setDouble(PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields::DewpointTemperatureDifferenceRangeLowerLimit,lowerLimit);
      eg.setDouble(PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields::DewpointTemperatureDifferenceRangeUpperLimit,upperLimit);

      IdfObject equipmentList(IddObjectType::PlantEquipmentList);
      m_idfObjects.push_back(equipmentList);
      auto equipmentListName = name + " equipment list " + std::to_string(i);
      equipmentList.setName(equipmentListName);
      eg.setString(PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields::RangeEquipmentListName,equipmentListName);

      for( auto component : equipment ) {
        auto eg2 = equipmentList.pushExtensibleGroup();
        auto idf_component = translateAndMapModelObject(component);
        OS_ASSERT(idf_component);
        eg2.setString(PlantEquipmentListExtensibleFields::EquipmentObjectType,idf_component->iddObject().name());
        eg2.setString(PlantEquipmentListExtensibleFields::EquipmentName,idf_component->name().get());
      }
    }

    lowerLimit = upperLimit;
    ++i;
  }

  return idfObject;
}

} // energyplus

} // openstudio

