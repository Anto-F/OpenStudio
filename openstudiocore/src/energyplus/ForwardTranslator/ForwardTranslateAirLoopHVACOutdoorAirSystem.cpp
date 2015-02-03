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

#include <boost/optional/optional.hpp>
#include <utilities/idd/AirLoopHVAC_ControllerList_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/AvailabilityManagerAssignmentList_FieldEnums.hxx>
#include <utilities/idd/AvailabilityManager_Scheduled_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>
#include <memory>
#include <string>
#include <vector>

#include "../../model/AirLoopHVACOutdoorAirSystem.hpp"
#include "../../model/AirToAirComponent.hpp"
#include "../../model/CoilCoolingWater.hpp"
#include "../../model/CoilHeatingWater.hpp"
#include "../../model/ControllerOutdoorAir.hpp"
#include "../../model/ControllerWaterCoil.hpp"
#include "../../model/Node.hpp"
#include "../../model/Schedule.hpp"
#include "../../utilities/core/Assert.hpp"
#include "../../utilities/idd/IddEnums.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../ForwardTranslator.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idd/../core/Optional.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idd/IddObject.hpp"
#include "energyplus/ForwardTranslator/../../model/../utilities/idf/IdfObject.hpp"
#include "energyplus/ForwardTranslator/../../model/Model.hpp"
#include "energyplus/ForwardTranslator/../../model/ModelObject.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateAirLoopHVACOutdoorAirSystem( AirLoopHVACOutdoorAirSystem & modelObject )
{
  OptionalString s;
  IdfObject idfObject(IddObjectType::AirLoopHVAC_OutdoorAirSystem);

  m_idfObjects.push_back(idfObject);

  // Name
  std::string name = modelObject.name().get();
  idfObject.setString(openstudio::AirLoopHVAC_OutdoorAirSystemFields::Name,name);
 

  // Controller List
  IdfObject _controllerList(IddObjectType::AirLoopHVAC_ControllerList);
  _controllerList.setName(name + " Controller List");
  _controllerList.clearExtensibleGroups();
  m_idfObjects.push_back(_controllerList);

  ControllerOutdoorAir controllerOutdoorAir = modelObject.getControllerOutdoorAir();
  boost::optional<IdfObject> _controllerOutdoorAir = translateAndMapModelObject(controllerOutdoorAir);
  OS_ASSERT(_controllerOutdoorAir);

  idfObject.setString(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName,_controllerList.name().get());

  IdfExtensibleGroup eg = _controllerList.pushExtensibleGroup();
  eg.setString(AirLoopHVAC_ControllerListExtensibleFields::ControllerObjectType,_controllerOutdoorAir->iddObject().name());
  eg.setString(AirLoopHVAC_ControllerListExtensibleFields::ControllerName,_controllerOutdoorAir->name().get());

  std::vector<ModelObject> controllers;
  auto components = modelObject.components();
  for( const auto & component : components ) {
    boost::optional<ControllerWaterCoil> controller;

    if( auto coil = component.optionalCast<CoilCoolingWater>() ) {
      controller = coil->controllerWaterCoil();
    } else if ( auto coil = component.optionalCast<CoilHeatingWater>() ) {
      controller = coil->controllerWaterCoil();
    }

    if( controller ) {
      controllers.push_back(controller.get());
    }
  } 
  
  for( auto & controller: controllers ) {
    auto _controller = translateAndMapModelObject(controller);
    if( _controller ) {
      IdfExtensibleGroup eg = _controllerList.pushExtensibleGroup();
      eg.setString(AirLoopHVAC_ControllerListExtensibleFields::ControllerObjectType,_controller->iddObject().name());
      eg.setString(AirLoopHVAC_ControllerListExtensibleFields::ControllerName,_controller->name().get());
    }
  }

  // Field: Availability Manager List Name //////////////////////////////////
  IdfObject availabilityManagerListIdf(IddObjectType::AvailabilityManagerAssignmentList);
  availabilityManagerListIdf.setName(name + " Availability Manager List");
  m_idfObjects.push_back(availabilityManagerListIdf);

  IdfObject availabilityManagerScheduledIdf = IdfObject(openstudio::IddObjectType::AvailabilityManager_Scheduled);
  availabilityManagerScheduledIdf.setName(name + " Availability Manager");
  m_idfObjects.push_back(availabilityManagerScheduledIdf);

  Schedule alwaysOn = modelObject.model().alwaysOnDiscreteSchedule();
  IdfObject alwaysOnIdf = translateAndMapModelObject(alwaysOn).get();

  s = availabilityManagerListIdf.getString(openstudio::AvailabilityManagerAssignmentListFields::Name);
  if(s)
  {
    idfObject.setString(openstudio::AirLoopHVAC_OutdoorAirSystemFields::AvailabilityManagerListName,*s);
  }

  availabilityManagerListIdf.setString(1 + openstudio::AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerObjectType,
                                       availabilityManagerScheduledIdf.iddObject().name());
  availabilityManagerListIdf.setString(1 + openstudio::AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerName,
                                       availabilityManagerScheduledIdf.name().get());
  availabilityManagerScheduledIdf.setString(openstudio::AvailabilityManager_ScheduledFields::ScheduleName,alwaysOnIdf.name().get());

  // OA Node List
  s = modelObject.outboardOANode()->name();
  IdfObject oaNodeListIdf(openstudio::IddObjectType::OutdoorAir_NodeList);
  if(s)
  {
    oaNodeListIdf.setString(0,*s);
  }
  m_idfObjects.push_back(oaNodeListIdf);

  ///////////////////////////////////////////////////////////////////////////
  // Field: Outdoor Air Equipment List Name /////////////////////////////////
  IdfObject equipmentListIdf(IddObjectType::AirLoopHVAC_OutdoorAirSystem_EquipmentList);
  equipmentListIdf.setName(name + " Equipment List");

  m_idfObjects.push_back(equipmentListIdf);

  IdfObject outdoorAirMixerIdf(IddObjectType::OutdoorAir_Mixer);
  outdoorAirMixerIdf.setName(name + " Outdoor Air Mixer");
  m_idfObjects.push_back(outdoorAirMixerIdf);

  s = modelObject.mixedAirModelObject()->name();
  if(s)
  {
    outdoorAirMixerIdf.setString(OutdoorAir_MixerFields::MixedAirNodeName,*s);
  }
  s = modelObject.outdoorAirModelObject()->name();
  if(s)
  {
    outdoorAirMixerIdf.setString(OutdoorAir_MixerFields::OutdoorAirStreamNodeName,*s);
  }

  s = modelObject.reliefAirModelObject()->name();
  if(s)
  {
    outdoorAirMixerIdf.setString(OutdoorAir_MixerFields::ReliefAirStreamNodeName,*s);
  }

  s = modelObject.returnAirModelObject()->name();
  if(s)
  {
    outdoorAirMixerIdf.setString(OutdoorAir_MixerFields::ReturnAirStreamNodeName,*s);
  }

  s = outdoorAirMixerIdf.iddObject().name();
  equipmentListIdf.setString(1,*s);
  s = outdoorAirMixerIdf.name();
  equipmentListIdf.setString(2,*s);

  unsigned i = 3;
  ModelObjectVector oaModelObjects = modelObject.oaComponents();
  for( ModelObjectVector::iterator oaIt = oaModelObjects.begin();
       oaIt != oaModelObjects.end();
       ++oaIt )
  {
    if( ! oaIt->optionalCast<Node>() )
    {
      if( boost::optional<IdfObject> idfObject = translateAndMapModelObject(*oaIt) )
      {
        equipmentListIdf.setString(i,idfObject->iddObject().name());
        i++;
        equipmentListIdf.setString(i,idfObject->name().get());
        i++;
      }
    }
  }

  ModelObjectVector reliefModelObjects = modelObject.reliefComponents();
  for( ModelObjectVector::iterator reliefIt = reliefModelObjects.begin();
       reliefIt != reliefModelObjects.end();
       ++reliefIt )
  {
    if( (! reliefIt->optionalCast<Node>()) && (! reliefIt->optionalCast<AirToAirComponent>()) )
    {
      if( boost::optional<IdfObject> idfObject = translateAndMapModelObject(*reliefIt) )
      {
        equipmentListIdf.setString(i,idfObject->iddObject().name());
        i++;
        equipmentListIdf.setString(i,idfObject->name().get());
        i++;
      }
    }
  }

  s = equipmentListIdf.name();
  if(s)
  {
    idfObject.setString(openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName,*s);
  }

  return boost::optional<IdfObject>(idfObject);
}

} // energyplus

} // openstudio

